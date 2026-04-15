#!/bin/bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
OUT_DIR="$ROOT_DIR/ai_docs/screenshots/round3"
OVERRIDES="$ROOT_DIR/src/c/round3_matrix_overrides.h"

mkdir -p "$OUT_DIR"

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
    echo "/* Generated temporarily by tools/capture_round3_matrix.sh. */"
  } >"$OVERRIDES"
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

  echo "Capturing $shot"
  write_overrides "$platform" "$center_x" "$center_y" "$hour_len" "$minute_len" "$hub_fill" "$hub_outline" "$show_date" "$date_y" "$accent"
  pebble build >/tmp/glyph-dial-round3-build.log
  for attempt in 1 2; do
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
    if "$ROOT_DIR/tools/capture_emulator_screenshot.sh" "$platform" "$OUT_DIR/${shot}.png" "$ROOT_DIR/build/pebble-watchface.pbw"; then
      return
    fi
    echo "Capture failed for $shot on attempt $attempt" >&2
    sleep 1
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

run_matrix_a() {
  build_and_capture emery_A1 emery 99 101 30 46 4 1 0 184
  build_and_capture emery_A2 emery 99 101 30 42 4 1 0 184
  build_and_capture emery_A3 emery 99 103 32 44 3 1 0 184
  build_and_capture emery_A4 emery 99 103 30 42 3 0 0 184

  build_and_capture gabbro_A1 gabbro 130 126 40 67 4 1 0 189
  build_and_capture gabbro_A2 gabbro 130 126 40 63 4 1 0 189
  build_and_capture gabbro_A3 gabbro 130 128 42 65 3 1 0 189
  build_and_capture gabbro_A4 gabbro 130 128 40 63 3 0 0 189

  make_sheet matrix_A_geometry \
    emery_A1 emery_A2 emery_A3 emery_A4 \
    gabbro_A1 gabbro_A2 gabbro_A3 gabbro_A4
}

run_matrix_b() {
  build_and_capture emery_B0 emery 99 103 32 44 3 1 0 184
  build_and_capture emery_B1 emery 99 103 32 44 3 1 1 184
  build_and_capture emery_B2 emery 99 103 32 44 3 1 1 188
  build_and_capture emery_B3 emery 99 103 32 44 3 1 1 192

  build_and_capture gabbro_B0 gabbro 130 128 42 65 3 1 0 189
  build_and_capture gabbro_B1 gabbro 130 128 42 65 3 1 1 189
  build_and_capture gabbro_B2 gabbro 130 128 42 65 3 1 1 193
  build_and_capture gabbro_B3 gabbro 130 128 42 65 3 1 1 197

  make_sheet matrix_B_date \
    emery_B0 emery_B1 emery_B2 emery_B3 \
    gabbro_B0 gabbro_B1 gabbro_B2 gabbro_B3
}

run_matrix_c() {
  build_and_capture emery_C_mono emery 99 103 32 44 3 1 1 184 0
  build_and_capture emery_C_gold_brass emery 99 103 32 44 3 1 1 184 1
  build_and_capture emery_C_gold_windsor emery 99 103 32 44 3 1 1 184 2
  build_and_capture emery_C_red_dark_candy emery 99 103 32 44 3 1 1 184 3
  build_and_capture emery_C_red_bulgarian emery 99 103 32 44 3 1 1 184 4

  build_and_capture gabbro_C_mono gabbro 130 128 42 65 3 1 1 189 0
  build_and_capture gabbro_C_gold_brass gabbro 130 128 42 65 3 1 1 189 1
  build_and_capture gabbro_C_gold_windsor gabbro 130 128 42 65 3 1 1 189 2
  build_and_capture gabbro_C_red_dark_candy gabbro 130 128 42 65 3 1 1 189 3
  build_and_capture gabbro_C_red_bulgarian gabbro 130 128 42 65 3 1 1 189 4

  make_sheet matrix_C_color \
    emery_C_mono emery_C_gold_brass emery_C_gold_windsor emery_C_red_dark_candy emery_C_red_bulgarian \
    gabbro_C_mono gabbro_C_gold_brass gabbro_C_gold_windsor gabbro_C_red_dark_candy gabbro_C_red_bulgarian
}

case "${1:-A}" in
  A)
    trap reset_overrides EXIT
    run_matrix_a
    ;;
  B)
    trap reset_overrides EXIT
    run_matrix_b
    ;;
  C)
    trap reset_overrides EXIT
    run_matrix_c
    ;;
  reset)
    reset_overrides
    ;;
  *)
    echo "Usage: $0 [A|B|C|reset]" >&2
    exit 1
    ;;
esac
