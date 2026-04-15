#!/bin/bash
set -euo pipefail

if [[ $# -lt 2 || $# -gt 3 ]]; then
  echo "Usage: $0 <platform> <output-png> [pbw]" >&2
  exit 1
fi

PLATFORM="$1"
OUTPUT_PNG="$2"
PBW_PATH="${3:-build/pebble-watchface.pbw}"
ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
LOG_PATH="/tmp/glyph-dial-${PLATFORM}.log"

if [[ ! -f "$PBW_PATH" ]]; then
  echo "PBW not found: $PBW_PATH" >&2
  exit 1
fi

mkdir -p "$(dirname "$OUTPUT_PNG")"

cleanup() {
  if [[ -n "${INSTALL_PID:-}" ]]; then
    kill "$INSTALL_PID" 2>/dev/null || true
    wait "$INSTALL_PID" 2>/dev/null || true
  fi
}
trap cleanup EXIT

rm -f "$LOG_PATH"

cd "$ROOT_DIR"
pebble install --emulator "$PLATFORM" --logs --qemu_logs "$PBW_PATH" >"$LOG_PATH" 2>&1 &
INSTALL_PID=$!

PYPKJS_PORT=""
for _ in $(seq 1 100); do
  PYPKJS_PORT="$(python3 - "$PLATFORM" <<'PY'
import json
import os
import sys
import tempfile

platform = sys.argv[1]
path = os.path.join(tempfile.gettempdir(), "pb-emulator.json")
try:
    with open(path) as f:
        data = json.load(f)
except (OSError, ValueError, json.JSONDecodeError):
    print("")
    raise SystemExit(0)

for _, info in (data.get(platform) or {}).items():
    pypkjs = info.get("pypkjs") or {}
    port = pypkjs.get("port")
    if port:
        print(port)
        break
else:
    print("")
PY
)"
  if [[ -n "$PYPKJS_PORT" ]]; then
    break
  fi
  sleep 0.2
done

if [[ -z "$PYPKJS_PORT" ]]; then
  echo "Failed to discover pypkjs port for $PLATFORM" >&2
  cat "$LOG_PATH" >&2 || true
  exit 1
fi

READY=0
for _ in $(seq 1 100); do
  if [[ -f "$LOG_PATH" ]] && rg -q "GLYPH_DIAL_FRAME_READY" "$LOG_PATH"; then
    READY=1
    break
  fi
  sleep 0.2
done

if [[ "$READY" -ne 1 ]]; then
  echo "Timed out waiting for app frame readiness on $PLATFORM" >&2
  cat "$LOG_PATH" >&2 || true
  exit 1
fi

sleep 0.5
for attempt in $(seq 1 5); do
  if pebble screenshot --phone "127.0.0.1:${PYPKJS_PORT}" --no-open "$OUTPUT_PNG"; then
    exit 0
  fi
  echo "Screenshot connection failed for $PLATFORM on attempt $attempt" >&2
  sleep 0.5
done

echo "Failed to capture screenshot for $PLATFORM" >&2
exit 1
