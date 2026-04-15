#!/bin/bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
OUT_DIR="$ROOT_DIR/ai_docs/screenshots/round4"
FINAL_DIR="$OUT_DIR/final_candidates"
OVERRIDES="$ROOT_DIR/src/c/glyph_layout_overrides.h"
MANIFEST_JSONL="$OUT_DIR/manifest.jsonl"
MEASUREMENTS_JSONL="$OUT_DIR/measurements.jsonl"
CAPTURE_HOUR=10
CAPTURE_MINUTE=10

mkdir -p "$OUT_DIR" "$FINAL_DIR"

write_overrides() {
  local platform="$1"
  local center_x="$2"
  local center_y="$3"
  local hour_len="$4"
  local minute_len="$5"
  local hub_fill="$6"
  local hub_outline="$7"
  local show_date="$8"
  local date_y="$9"
  local accent="${10:-0}"

  {
    echo "#pragma once"
    echo
    echo "#define GLYPH_FORCE_SHOW_DATE $show_date"
    echo "#define GLYPH_HUB_FILL_RADIUS $hub_fill"
    echo "#define GLYPH_HUB_OUTLINE_WIDTH $hub_outline"
    echo "#define GLYPH_ACCENT_MODE $accent"
    echo "#define GLYPH_FORCE_HOUR $CAPTURE_HOUR"
    echo "#define GLYPH_FORCE_MINUTE $CAPTURE_MINUTE"
    if [[ "$platform" == "emery" ]]; then
      echo "#define GLYPH_EMERY_CENTER_X $center_x"
      echo "#define GLYPH_EMERY_CENTER_Y $center_y"
      echo "#define GLYPH_EMERY_HOUR_LEN $hour_len"
      echo "#define GLYPH_EMERY_MINUTE_LEN $minute_len"
      echo "#define GLYPH_EMERY_DATE_Y $date_y"
    else
      echo "#define GLYPH_GABBRO_CENTER_X $center_x"
      echo "#define GLYPH_GABBRO_CENTER_Y $center_y"
      echo "#define GLYPH_GABBRO_HOUR_LEN $hour_len"
      echo "#define GLYPH_GABBRO_MINUTE_LEN $minute_len"
      echo "#define GLYPH_GABBRO_DATE_Y $date_y"
    fi
  } >"$OVERRIDES"
}

reset_overrides() {
  {
    echo "#pragma once"
    echo
    echo "/* Generated temporarily by tools/capture_design_matrix.sh. */"
  } >"$OVERRIDES"
}

reset_emulator_state() {
  pebble kill >/dev/null 2>&1 || true
  python3 - <<'PY'
import os
import tempfile

path = os.path.join(tempfile.gettempdir(), "pb-emulator.json")
try:
    os.remove(path)
except FileNotFoundError:
    pass
PY
}

append_manifest() {
  local shot="$1"
  local platform="$2"
  local center_x="$3"
  local center_y="$4"
  local hour_len="$5"
  local minute_len="$6"
  local hub_fill="$7"
  local hub_outline="$8"
  local show_date="$9"
  local accent="${10}"
  local output="$11"

  python3 - "$MANIFEST_JSONL" "$shot" "$platform" "$center_x" "$center_y" "$hour_len" \
    "$minute_len" "$hub_fill" "$hub_outline" "$show_date" "$accent" \
    "$CAPTURE_HOUR" "$CAPTURE_MINUTE" "$output" <<'PY'
import json
import sys

path = sys.argv[1]
entry = {
    "variant": sys.argv[2],
    "platform": sys.argv[3],
    "center": [int(sys.argv[4]), int(sys.argv[5])],
    "hour_length": int(sys.argv[6]),
    "minute_length": int(sys.argv[7]),
    "hub_fill_radius": int(sys.argv[8]),
    "hub_outline_width": int(sys.argv[9]),
    "forced_show_date": int(sys.argv[10]),
    "accent_mode": int(sys.argv[11]),
    "capture_time": f"{int(sys.argv[12]):02d}:{int(sys.argv[13]):02d}",
    "output": sys.argv[14],
}
with open(path, "a", encoding="utf-8") as f:
    f.write(json.dumps(entry, sort_keys=True) + "\n")
PY
}

append_measurement() {
  local shot="$1"
  local platform="$2"
  local center_x="$3"
  local center_y="$4"
  local hour_len="$5"
  local minute_len="$6"
  local output="$7"

  python3 "$ROOT_DIR/tools/measure_watchface_render.py" \
    --image "$output" \
    --platform "$platform" \
    --variant "$shot" \
    --center-x "$center_x" \
    --center-y "$center_y" \
    --hour-length "$hour_len" \
    --minute-length "$minute_len" \
    --capture-hour "$CAPTURE_HOUR" \
    --capture-minute "$CAPTURE_MINUTE" >>"$MEASUREMENTS_JSONL"
}

finalize_json() {
  local jsonl="$1"
  local json="$2"
  python3 - "$jsonl" "$json" <<'PY'
import json
import sys

with open(sys.argv[1], encoding="utf-8") as f:
    rows = [json.loads(line) for line in f if line.strip()]
with open(sys.argv[2], "w", encoding="utf-8") as f:
    json.dump(rows, f, indent=2, sort_keys=True)
    f.write("\n")
PY
}

build_and_capture() {
  local shot="$1"
  local platform="$2"
  local center_x="$3"
  local center_y="$4"
  local hour_len="$5"
  local minute_len="$6"
  local hub_fill="$7"
  local hub_outline="$8"
  local show_date="$9"
  local date_y="${10}"
  local accent="${11:-0}"
  local output="$OUT_DIR/${shot}.png"

  echo "Capturing $shot"
  write_overrides "$platform" "$center_x" "$center_y" "$hour_len" "$minute_len" \
    "$hub_fill" "$hub_outline" "$show_date" "$date_y" "$accent"
  pebble build >/tmp/glyph-dial-design-matrix-build.log

  for attempt in 1 2 3; do
    reset_emulator_state
    sleep 0.5
    if "$ROOT_DIR/tools/capture_emulator_screenshot.sh" "$platform" "$output" "$ROOT_DIR/build/pebble-watchface.pbw"; then
      append_manifest "$shot" "$platform" "$center_x" "$center_y" "$hour_len" "$minute_len" \
        "$hub_fill" "$hub_outline" "$show_date" "$accent" "$output"
      append_measurement "$shot" "$platform" "$center_x" "$center_y" "$hour_len" "$minute_len" "$output"
      return
    fi
    echo "Capture failed for $shot on attempt $attempt" >&2
    sleep 2
  done

  echo "Capture failed for $shot after retries" >&2
  exit 1
}

make_sheet() {
  local sheet="$1"
  shift
  local images=()
  for name in "$@"; do
    images+=("$OUT_DIR/${name}.png")
  done
  magick montage "${images[@]}" -background black -fill white -label '%t' -geometry +16+16 "$OUT_DIR/${sheet}.png"
}

geometry_params() {
  case "$1" in
    E1) echo "emery 99 100 34 54" ;;
    E2) echo "emery 99 100 36 56" ;;
    E3) echo "emery 99 100 38 58" ;;
    E4) echo "emery 99 102 34 54" ;;
    E5) echo "emery 99 102 36 56" ;;
    E6) echo "emery 99 102 38 58" ;;
    G1) echo "gabbro 131 126 40 64" ;;
    G2) echo "gabbro 131 126 42 66" ;;
    G3) echo "gabbro 131 126 44 68" ;;
    G4) echo "gabbro 131 128 40 64" ;;
    G5) echo "gabbro 131 128 42 66" ;;
    G6) echo "gabbro 131 128 44 68" ;;
    E7) echo "emery 99 100 40 60" ;;
    E8) echo "emery 99 100 42 62" ;;
    E9) echo "emery 99 100 44 64" ;;
    E10) echo "emery 99 100 46 66" ;;
    E11) echo "emery 99 100 46 68" ;;
    E12) echo "emery 99 100 48 68" ;;
    G7) echo "gabbro 131 128 46 70" ;;
    G8) echo "gabbro 131 128 48 72" ;;
    G9) echo "gabbro 131 128 50 74" ;;
    *) echo "Unknown geometry variant: $1" >&2; exit 1 ;;
  esac
}

run_round4_emery_micro_geometry() {
  : >"$MANIFEST_JSONL"
  : >"$MEASUREMENTS_JSONL"

  for variant in E10 E11 E12; do
    capture_geometry_variant "$variant" 2 "_hub2"
  done
  make_sheet round4_emery_micro_geometry \
    emery_E10_hub2 emery_E11_hub2 emery_E12_hub2

  finalize_json "$MANIFEST_JSONL" "$OUT_DIR/manifest.json"
  finalize_json "$MEASUREMENTS_JSONL" "$OUT_DIR/measurements.json"
}

capture_geometry_variant() {
  local name="$1"
  local hub_fill="${2:-3}"
  local shot_suffix="${3:-}"
  read -r platform center_x center_y hour_len minute_len <<<"$(geometry_params "$name")"
  build_and_capture "${platform}_${name}${shot_suffix}" "$platform" "$center_x" "$center_y" "$hour_len" "$minute_len" "$hub_fill" 1 0 184 0
}

run_round4_geometry() {
  : >"$MANIFEST_JSONL"
  : >"$MEASUREMENTS_JSONL"

  for variant in E1 E2 E3 E4 E5 E6; do
    capture_geometry_variant "$variant"
  done
  make_sheet round4_emery_geometry emery_E1 emery_E2 emery_E3 emery_E4 emery_E5 emery_E6

  for variant in G1 G2 G3 G4 G5 G6; do
    capture_geometry_variant "$variant"
  done
  make_sheet round4_gabbro_geometry gabbro_G1 gabbro_G2 gabbro_G3 gabbro_G4 gabbro_G5 gabbro_G6

  finalize_json "$MANIFEST_JSONL" "$OUT_DIR/manifest.json"
  finalize_json "$MEASUREMENTS_JSONL" "$OUT_DIR/measurements.json"
}

run_round4_longer_geometry() {
  : >"$MANIFEST_JSONL"
  : >"$MEASUREMENTS_JSONL"

  for variant in E7 E8 E9; do
    capture_geometry_variant "$variant" 3 "_hub3"
    capture_geometry_variant "$variant" 2 "_hub2"
  done
  make_sheet round4_emery_longer_geometry \
    emery_E7_hub3 emery_E7_hub2 \
    emery_E8_hub3 emery_E8_hub2 \
    emery_E9_hub3 emery_E9_hub2

  for variant in G7 G8 G9; do
    capture_geometry_variant "$variant" 3 "_hub3"
    capture_geometry_variant "$variant" 2 "_hub2"
  done
  make_sheet round4_gabbro_longer_geometry \
    gabbro_G7_hub3 gabbro_G7_hub2 \
    gabbro_G8_hub3 gabbro_G8_hub2 \
    gabbro_G9_hub3 gabbro_G9_hub2

  finalize_json "$MANIFEST_JSONL" "$OUT_DIR/manifest.json"
  finalize_json "$MEASUREMENTS_JSONL" "$OUT_DIR/measurements.json"
}

capture_color_variant() {
  local geometry="$1"
  local color="$2"
  local accent="$3"
  read -r platform center_x center_y hour_len minute_len <<<"$(geometry_params "$geometry")"
  build_and_capture "${platform}_${geometry}_${color}" "$platform" "$center_x" "$center_y" \
    "$hour_len" "$minute_len" 2 1 0 184 "$accent"
}

run_round4_color() {
  if [[ $# -ne 2 ]]; then
    echo "Usage: $0 round4-color <emery-variant> <gabbro-variant>" >&2
    exit 1
  fi

  local emery_variant="$1"
  local gabbro_variant="$2"

  capture_color_variant "$emery_variant" C1_mono 0
  capture_color_variant "$emery_variant" C2_brass 1
  capture_color_variant "$emery_variant" C3_windsor 2
  make_sheet round4_emery_color \
    "emery_${emery_variant}_C1_mono" \
    "emery_${emery_variant}_C2_brass" \
    "emery_${emery_variant}_C3_windsor"

  capture_color_variant "$gabbro_variant" C1_mono 0
  capture_color_variant "$gabbro_variant" C2_brass 1
  capture_color_variant "$gabbro_variant" C3_windsor 2
  make_sheet round4_gabbro_color \
    "gabbro_${gabbro_variant}_C1_mono" \
    "gabbro_${gabbro_variant}_C2_brass" \
    "gabbro_${gabbro_variant}_C3_windsor"

  finalize_json "$MANIFEST_JSONL" "$OUT_DIR/manifest.json"
  finalize_json "$MEASUREMENTS_JSONL" "$OUT_DIR/measurements.json"
}

run_round4_summary() {
  if [[ $# -ne 4 ]]; then
    echo "Usage: $0 round4-summary <emery-variant> <emery-best-color> <gabbro-variant> <gabbro-best-color>" >&2
    exit 1
  fi

  local emery_variant="$1"
  local emery_color="$2"
  local gabbro_variant="$3"
  local gabbro_color="$4"

  cp "$OUT_DIR/emery_${emery_variant}_C1_mono.png" "$FINAL_DIR/emery_${emery_variant}_mono.png"
  cp "$OUT_DIR/emery_${emery_variant}_${emery_color}.png" "$FINAL_DIR/emery_${emery_variant}_${emery_color}.png"
  cp "$OUT_DIR/gabbro_${gabbro_variant}_C1_mono.png" "$FINAL_DIR/gabbro_${gabbro_variant}_mono.png"
  cp "$OUT_DIR/gabbro_${gabbro_variant}_${gabbro_color}.png" "$FINAL_DIR/gabbro_${gabbro_variant}_${gabbro_color}.png"

  magick montage \
    "$FINAL_DIR/emery_${emery_variant}_mono.png" \
    "$FINAL_DIR/emery_${emery_variant}_${emery_color}.png" \
    "$FINAL_DIR/gabbro_${gabbro_variant}_mono.png" \
    "$FINAL_DIR/gabbro_${gabbro_variant}_${gabbro_color}.png" \
    -background black -fill white -label '%t' -geometry +20+20 "$OUT_DIR/round4_final_summary.png"
}

capture_submission_shot() {
  local platform="$1"
  local hour="$2"
  local minute="$3"
  local output="$4"

  CAPTURE_HOUR="$hour"
  CAPTURE_MINUTE="$minute"

  if [[ "$platform" == "emery" ]]; then
    build_and_capture "$platform" "$platform" 99 100 46 68 2 1 0 184 0
  else
    build_and_capture "$platform" "$platform" 131 128 50 74 2 1 0 184 0
  fi
  mkdir -p "$(dirname "$output")"
  cp "$OUT_DIR/${platform}.png" "$output"
}

run_submission_set() {
  local submission_dir="$ROOT_DIR/ai_docs/screenshots/submission"
  mkdir -p "$submission_dir"
  : >"$MANIFEST_JSONL"
  : >"$MEASUREMENTS_JSONL"

  capture_submission_shot emery 10 10 "$submission_dir/emery_hero_1010.png"
  capture_submission_shot emery 8 7 "$submission_dir/emery_alt_0807.png"
  capture_submission_shot emery 2 50 "$submission_dir/emery_alt_0250.png"
  capture_submission_shot gabbro 10 10 "$submission_dir/gabbro_hero_1010.png"
  capture_submission_shot gabbro 8 7 "$submission_dir/gabbro_alt_0807.png"
  capture_submission_shot gabbro 2 50 "$submission_dir/gabbro_alt_0250.png"

  finalize_json "$MANIFEST_JSONL" "$submission_dir/manifest.json"
  finalize_json "$MEASUREMENTS_JSONL" "$submission_dir/measurements.json"
}

case "${1:-}" in
  round4-geometry)
    trap reset_overrides EXIT
    run_round4_geometry
    ;;
  round4-color)
    trap reset_overrides EXIT
    shift
    run_round4_color "$@"
    ;;
  round4-longer-geometry)
    trap reset_overrides EXIT
    run_round4_longer_geometry
    ;;
  round4-emery-micro)
    trap reset_overrides EXIT
    run_round4_emery_micro_geometry
    ;;
  round4-summary)
    shift
    run_round4_summary "$@"
    ;;
  submission)
    trap reset_overrides EXIT
    run_submission_set
    ;;
  reset)
    reset_overrides
    ;;
  *)
    echo "Usage: $0 {round4-geometry|round4-longer-geometry|round4-emery-micro|round4-color <E*> <G*>|round4-summary <E*> <E-color> <G*> <G-color>|submission|reset}" >&2
    exit 1
    ;;
esac
