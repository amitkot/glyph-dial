# Glyph Dial Round 4 Brief

## Final Round 4 Lock

Round 4 is complete.

Locked v1 direction:
- Hebrew-first
- `Noto Sans Hebrew Bold`
- tapered baton hands
- small outlined hub
- no seconds
- no date
- black theme primary
- monochrome default
- no brass setting in v1

Locked geometry:
- Emery `E11_hub2`: center `(99,100)`, hour `46`, minute `68`, hub fill `2`, outline `1`
- Gabbro `G9_hub2`: center `(131,128)`, hour `50`, minute `74`, hub fill `2`, outline `1`

Brass remains acceptable as a future optional variant, but monochrome is the v1
identity.

## Goal

Round 4 is a focused design decision round about exactly two things:

- **drop the date entirely for v1**
- **push the hands closer to the glyph ring**
- **re-test only restrained metallic hour-hand accents**

This round is not about adding features.
It is about deciding whether the watch becomes stronger as a purer object.

---

## Locked assumptions for this round

Keep these fixed unless a comparison clearly disproves them:

- Hebrew-first
- `Noto Sans Hebrew Bold`
- tapered baton hands
- black theme as the primary theme
- no seconds
- glyph shapes untouched
- glyph color stays white
- minute hand stays white
- background stays black
- accent, if any, applies only to the **hour hand**
- optional matching accent on the hub outline only

---

## What changes in Round 4

### 1. Remove the date from the comparison shots
Do not render the date in this round.

We are testing whether the watch becomes materially stronger as a pure dial.

### 2. Push the hands closer to the glyphs
We are specifically testing a more watch-like composition:
- less empty space
- stronger reach
- minute hand near-kiss distance from the glyph ring
- hour hand longer than before, but still clearly secondary to the minute hand in reach

### 3. Reduce the color comparison to metallic accents only
Do not test red anymore.

Only compare:
- monochrome
- `GColorBrass`
- `GColorWindsorTan`

---

## Measurements taken from the latest screenshots

These values were measured from the uploaded screenshots with code.

## Emery current screenshot

Image size:
- `200 × 228`

Non-black content bbox:
- `x = 24..172`
- `y = 23..199`

Estimated hub center:
- `x = 99`
- `y = 100`

Hand component bbox:
- `x = 63..106`
- `y = 70..130`

Measured hand tips:
- minute tip at `(63, 130)`
- hour tip at `(95, 70)`

Measured hand radii from hub center:
- minute radius: `46.86 px`
- hour radius: `30.27 px`

Nearest glyph distance from current minute tip:
- `19.0 px`

Nearest glyph distance from current hour tip:
- `37.0 px`

Measured minimum inner glyph radius:
- `60.42 px`

Interpretation:
- Emery still has **too much air** between the hands and the glyph ring
- this is the main reason it feels less “watch-like” than Gabbro

## Gabbro current screenshot

Image size:
- `260 × 260`

Non-black content bbox:
- `x = 30..225`
- `y = 31..229`

Estimated hub center:
- `x = 131`
- `y = 126`

Hand component bbox:
- `x = 124..195`
- `y = 88..136`

Measured hand tips:
- minute tip at `(195, 110)`
- hour tip at `(134, 88)`

Measured hand radii from hub center:
- minute radius: `65.97 px`
- hour radius: `38.12 px`

Nearest glyph distance from current minute tip:
- `1.41 px`

Nearest glyph distance from current hour tip:
- `47.10 px`

Measured minimum inner glyph radius with the date excluded:
- `80.13 px`

Interpretation:
- Gabbro already has a near-kiss minute-hand composition
- it needs only **small** changes, if any
- the main question on Gabbro is whether a slightly longer hour hand improves the balance

---

## Design rule for Round 4

### Date
For this round:
- remove the date from all comparison shots
- do not include a Settings toggle for the date in the comparison build

If the no-date version clearly wins:
- ship v1 without date
- remove date from the design spec and from Settings for v1

If the no-date version does **not** clearly win:
- revisit date later, not during this round

### Hands
Hands should:
- almost reach the glyphs
- not visually cut through glyph pixels
- feel like a deliberate analog design, not a sparse UI skeleton

### Color
Color should:
- remain optional
- be tested only after the no-date geometry is compared
- survive only if it clearly improves the design

---

## Exact implementation instructions

## Common instructions
Use the existing tapered baton hand family.
Do not reopen the hand-family question in this round.

Use the existing Hebrew glyphs unchanged.

Use the small outlined hub, not the heavy hub and not the outline-free hub.

### Hub spec
Use:
- fill radius: `3 px`
- outline width: `1 px`

Keep this fixed through the geometry matrix so the comparison focuses on hand reach.

---

## Emery Round 4 geometry matrix

Base center:
- `(99, 100)`

Optional alternate center:
- `(99, 102)`

Current measured hand radii:
- hour `30.27`
- minute `46.86`

Target direction:
- increase both
- especially the minute hand
- aim for a much smaller visual gap to the glyph ring

### Compare these 6 variants

#### `E1`
- center `(99, 100)`
- hour length `34`
- minute length `54`

#### `E2`
- center `(99, 100)`
- hour length `36`
- minute length `56`

#### `E3`
- center `(99, 100)`
- hour length `38`
- minute length `58`

#### `E4`
- center `(99, 102)`
- hour length `34`
- minute length `54`

#### `E5`
- center `(99, 102)`
- hour length `36`
- minute length `56`

#### `E6`
- center `(99, 102)`
- hour length `38`
- minute length `58`

### Emery success rule
Pick the version where:
- the minute hand feels close to the glyph ring
- the face stops feeling airy
- the hour hand is longer and more watch-like
- nothing feels crowded or clipped

---

## Gabbro Round 4 geometry matrix

Base center:
- `(131, 126)`

Optional alternate center:
- `(131, 128)`

Current measured hand radii:
- hour `38.12`
- minute `65.97`

Target direction:
- preserve the successful near-kiss minute hand
- compare very small minute changes
- compare a slightly longer hour hand

### Compare these 6 variants

#### `G1`
- center `(131, 126)`
- hour length `40`
- minute length `64`

#### `G2`
- center `(131, 126)`
- hour length `42`
- minute length `66`

#### `G3`
- center `(131, 126)`
- hour length `44`
- minute length `68`

#### `G4`
- center `(131, 128)`
- hour length `40`
- minute length `64`

#### `G5`
- center `(131, 128)`
- hour length `42`
- minute length `66`

#### `G6`
- center `(131, 128)`
- hour length `44`
- minute length `68`

### Gabbro success rule
Pick the version where:
- the minute hand still feels elegant and near the glyph ring
- the hour hand looks more complete
- the center balance remains premium
- no new collision or awkward crowding appears

---

## Exact color matrix for Round 4

Run the color matrix only **after** one geometry winner is chosen per platform.

Keep everything else fixed.

### Compare exactly these 3 variants per platform

#### `C1_mono`
- hour hand: `GColorWhite`
- minute hand: `GColorWhite`
- hub outline: `GColorWhite`

#### `C2_brass`
- hour hand: `GColorBrass`
- minute hand: `GColorWhite`
- hub outline: `GColorBrass`

#### `C3_windsor`
- hour hand: `GColorWindsorTan`
- minute hand: `GColorWhite`
- hub outline: `GColorWindsorTan`

### Color success rule
A color survives only if it makes the face feel:
- more premium
- more memorable
- not louder
- not less timeless

If neither color clearly beats monochrome:
- ship monochrome

---

## Matrix output requirements

Generate:

### Geometry sheets
- `round4_emery_geometry.png`
- `round4_gabbro_geometry.png`

### Color sheets
- `round4_emery_color.png`
- `round4_gabbro_color.png`

### Final 2×2 summary sheet
- `round4_final_summary.png`

Summary sheet contents:
1. Emery geometry winner, monochrome
2. Emery geometry winner, best color
3. Gabbro geometry winner, monochrome
4. Gabbro geometry winner, best color

---

## Recommendation going into the matrix

Most likely outcome:

### Emery
- longer hands will help a lot
- one of `E3`, `E5`, or `E6` is the most likely winner

### Gabbro
- smaller adjustments are enough
- one of `G2` or `G5` is the most likely winner

### Color
- monochrome is still the baseline favorite
- `GColorBrass` is the only likely challenger
- `GColorWindsorTan` is worth checking once, but is less likely to win

---

## Definition of success for Round 4

Round 4 succeeds if the watchface becomes:

- purer
- more watch-like
- more iconic
- more premium
- clearly stronger without the date
