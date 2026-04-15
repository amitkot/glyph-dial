#!/usr/bin/env python3
import argparse
import json
import math
import subprocess
import sys
from collections import deque


def load_rgba(path):
    identify = subprocess.check_output(
        ["magick", "identify", "-format", "%w %h", path],
        text=True,
    )
    width, height = [int(part) for part in identify.split()]
    raw = subprocess.check_output(["magick", path, "-depth", "8", "rgba:-"])
    expected = width * height * 4
    if len(raw) != expected:
        raise RuntimeError(f"unexpected RGBA byte count: got {len(raw)}, expected {expected}")
    return width, height, raw


def is_content(raw, index):
    r = raw[index]
    g = raw[index + 1]
    b = raw[index + 2]
    a = raw[index + 3]
    return a > 0 and max(r, g, b) > 24


def content_mask(width, height, raw):
    mask = [False] * (width * height)
    points = []
    for y in range(height):
      for x in range(width):
        pixel = y * width + x
        if is_content(raw, pixel * 4):
            mask[pixel] = True
            points.append((x, y))
    return mask, points


def bbox(points):
    if not points:
        return None
    xs = [p[0] for p in points]
    ys = [p[1] for p in points]
    return [min(xs), min(ys), max(xs), max(ys)]


def hand_component(width, height, mask, cx, cy):
    seeds = []
    for y in range(max(0, cy - 8), min(height, cy + 9)):
        for x in range(max(0, cx - 8), min(width, cx + 9)):
            if mask[y * width + x]:
                seeds.append((x, y))

    seen = set()
    q = deque(seeds)
    while q:
        x, y = q.popleft()
        if (x, y) in seen:
            continue
        if not (0 <= x < width and 0 <= y < height):
            continue
        if not mask[y * width + x]:
            continue
        seen.add((x, y))
        for dy in (-1, 0, 1):
            for dx in (-1, 0, 1):
                if dx or dy:
                    q.append((x + dx, y + dy))
    return seen


def angle_unit(hour, minute, hand):
    if hand == "minute":
        angle = 2 * math.pi * minute / 60.0
    else:
        angle = 2 * math.pi * (((hour % 12) * 60 + minute) / 720.0)
    return math.sin(angle), -math.cos(angle)


def measure_tip(component, cx, cy, hour, minute, hand, expected_length):
    ux, uy = angle_unit(hour, minute, hand)
    best = None
    best_dot = -1e9
    for x, y in component:
        vx = x - cx
        vy = y - cy
        dot = vx * ux + vy * uy
        perp = abs(vx * uy - vy * ux)
        if dot < 0 or dot > expected_length + 10:
            continue
        if perp > 7:
            continue
        if dot > best_dot:
            best_dot = dot
            best = (x, y)

    if best is None:
        return None

    radius = math.hypot(best[0] - cx, best[1] - cy)
    return {
        "x": best[0],
        "y": best[1],
        "radius": round(radius, 2),
    }


def nearest_glyph_distance(points, component, tip):
    if tip is None:
        return None
    tx = tip["x"]
    ty = tip["y"]
    nearest = None
    for point in points:
        if point in component:
            continue
        dist = math.hypot(point[0] - tx, point[1] - ty)
        if nearest is None or dist < nearest:
            nearest = dist
    return None if nearest is None else round(nearest, 2)


def centroid(points):
    if not points:
        return None
    return [
        round(sum(p[0] for p in points) / len(points), 2),
        round(sum(p[1] for p in points) / len(points), 2),
    ]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--image", required=True)
    parser.add_argument("--platform", required=True)
    parser.add_argument("--variant", required=True)
    parser.add_argument("--center-x", required=True, type=int)
    parser.add_argument("--center-y", required=True, type=int)
    parser.add_argument("--hour-length", required=True, type=int)
    parser.add_argument("--minute-length", required=True, type=int)
    parser.add_argument("--capture-hour", required=True, type=int)
    parser.add_argument("--capture-minute", required=True, type=int)
    args = parser.parse_args()

    width, height, raw = load_rgba(args.image)
    mask, points = content_mask(width, height, raw)
    component = hand_component(width, height, mask, args.center_x, args.center_y)
    hub_points = [
        point for point in component
        if math.hypot(point[0] - args.center_x, point[1] - args.center_y) <= 6
    ]
    hour_tip = measure_tip(
        component,
        args.center_x,
        args.center_y,
        args.capture_hour,
        args.capture_minute,
        "hour",
        args.hour_length,
    )
    minute_tip = measure_tip(
        component,
        args.center_x,
        args.center_y,
        args.capture_hour,
        args.capture_minute,
        "minute",
        args.minute_length,
    )

    result = {
        "platform": args.platform,
        "variant": args.variant,
        "image": args.image,
        "content_bbox": bbox(points),
        "expected_hub_center": [args.center_x, args.center_y],
        "detected_hub_center": centroid(hub_points),
        "hour_tip": hour_tip,
        "minute_tip": minute_tip,
        "hour_tip_to_nearest_glyph_px": nearest_glyph_distance(points, component, hour_tip),
        "minute_tip_to_nearest_glyph_px": nearest_glyph_distance(points, component, minute_tip),
    }
    print(json.dumps(result, sort_keys=True))


if __name__ == "__main__":
    try:
        main()
    except Exception as exc:
        print(json.dumps({"error": str(exc)}), file=sys.stderr)
        raise
