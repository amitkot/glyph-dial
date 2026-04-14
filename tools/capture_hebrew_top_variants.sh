#!/bin/bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
OUT_DIR="$ROOT_DIR/ai_docs/screenshots/hebrew_top_variants"

mkdir -p "$OUT_DIR"

VARIANTS=(
  "tight_ltr|אי|בי"
  "semantic_rtl|יא|יב"
  "mixed_typo_control|אי|יב"
  "reverse_control|יא|בי"
)

for variant in "${VARIANTS[@]}"; do
  IFS='|' read -r name label11 label12 <<<"$variant"
  echo "Capturing $name (11=$label11 12=$label12)"
  HEBREW_11_LABEL="$label11" HEBREW_12_LABEL="$label12" "$ROOT_DIR/tools/generate_marker_assets.sh"
  pebble build
  "$ROOT_DIR/tools/capture_emulator_screenshot.sh" \
    emery "$OUT_DIR/${name}_emery.png" "$ROOT_DIR/build/pebble-watchface.pbw"
  "$ROOT_DIR/tools/capture_emulator_screenshot.sh" \
    gabbro "$OUT_DIR/${name}_gabbro.png" "$ROOT_DIR/build/pebble-watchface.pbw"
done
