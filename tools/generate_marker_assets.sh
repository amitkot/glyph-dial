#!/bin/bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
HEBREW_EMERY_DIR="$ROOT_DIR/resources/images/hebrew/emery"
HEBREW_GABBRO_DIR="$ROOT_DIR/resources/images/hebrew/gabbro"
ARABIC_EMERY_DIR="$ROOT_DIR/resources/images/arabic_indic/emery"
ARABIC_GABBRO_DIR="$ROOT_DIR/resources/images/arabic_indic/gabbro"
HEBREW_FONT_FILE="$ROOT_DIR/assets/fonts/NotoSansHebrew.ttf"
HEBREW_FONT_FACE="${HEBREW_FONT_FACE:-Noto-Sans-Hebrew-Bold}"
HEBREW_11_LABEL="${HEBREW_11_LABEL:-אי}"
HEBREW_12_LABEL="${HEBREW_12_LABEL:-בי}"

mkdir -p "$HEBREW_EMERY_DIR" "$HEBREW_GABBRO_DIR" "$ARABIC_EMERY_DIR" "$ARABIC_GABBRO_DIR"

if [[ ! -f "$HEBREW_FONT_FILE" ]]; then
  echo "Missing Hebrew font: $HEBREW_FONT_FILE" >&2
  exit 1
fi

hebrew_labels=(
  'א' 'ב' 'ג' 'ד' 'ה' 'ו' 'ז' 'ח' 'ט' 'י' 'אי' 'בי'
)
hebrew_names=(
  '01_aleph' '02_bet' '03_gimel' '04_dalet' '05_he' '06_vav'
  '07_zayin' '08_het' '09_tet' '10_yod' '11_yod_aleph' '12_yod_bet'
)
arabic_labels=(
  '١' '٢' '٣' '٤' '٥' '٦' '٧' '٨' '٩' '١٠' '١١' '١٢'
)
arabic_names=(
  '01_one' '02_two' '03_three' '04_four' '05_five' '06_six'
  '07_seven' '08_eight' '09_nine' '10_ten' '11_eleven' '12_twelve'
)

for i in "${!hebrew_labels[@]}"; do
  if [[ "$i" -eq 10 ]]; then
    magick -background black \
      -fill white \
      -font "$HEBREW_FONT_FACE" \
      -gravity center \
      -size 32x32 \
      label:"$HEBREW_11_LABEL" \
      "$HEBREW_EMERY_DIR/${hebrew_names[$i]}.png"
    magick -background black \
      -fill white \
      -font "$HEBREW_FONT_FACE" \
      -gravity center \
      -size 30x30 \
      label:"$HEBREW_11_LABEL" \
      "$HEBREW_GABBRO_DIR/${hebrew_names[$i]}.png"
  elif [[ "$i" -eq 11 ]]; then
    magick -background black \
      -fill white \
      -font "$HEBREW_FONT_FACE" \
      -gravity center \
      -size 32x32 \
      label:"$HEBREW_12_LABEL" \
      "$HEBREW_EMERY_DIR/${hebrew_names[$i]}.png"
    magick -background black \
      -fill white \
      -font "$HEBREW_FONT_FACE" \
      -gravity center \
      -size 30x30 \
      label:"$HEBREW_12_LABEL" \
      "$HEBREW_GABBRO_DIR/${hebrew_names[$i]}.png"
  else
    magick -background black \
      -fill white \
      -font "$HEBREW_FONT_FACE" \
      -gravity center \
      -size 32x32 \
      label:"${hebrew_labels[$i]}" \
      "$HEBREW_EMERY_DIR/${hebrew_names[$i]}.png"
    magick -background black \
      -fill white \
      -font "$HEBREW_FONT_FACE" \
      -gravity center \
      -size 30x30 \
      label:"${hebrew_labels[$i]}" \
      "$HEBREW_GABBRO_DIR/${hebrew_names[$i]}.png"
  fi
done

for i in "${!arabic_labels[@]}"; do
  magick -background black \
    -fill white \
    -font ".SF-Arabic-Bold" \
    -gravity center \
    -size 24x24 \
    label:"${arabic_labels[$i]}" \
    "$ARABIC_EMERY_DIR/${arabic_names[$i]}.png"
  magick -background black \
    -fill white \
    -font ".SF-Arabic-Bold" \
    -gravity center \
    -size 30x30 \
    label:"${arabic_labels[$i]}" \
    "$ARABIC_GABBRO_DIR/${arabic_names[$i]}.png"
done
