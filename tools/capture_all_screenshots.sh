#!/bin/bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
PBW_PATH="${1:-$ROOT_DIR/build/pebble-watchface.pbw}"

"$ROOT_DIR/tools/capture_emulator_screenshot.sh" emery "$ROOT_DIR/ai_docs/screenshots/emery.png" "$PBW_PATH" &
EMERY_PID=$!

"$ROOT_DIR/tools/capture_emulator_screenshot.sh" gabbro "$ROOT_DIR/ai_docs/screenshots/gabbro.png" "$PBW_PATH" &
GABBRO_PID=$!

wait "$EMERY_PID"
wait "$GABBRO_PID"
