# Glyph Dial Round-3 Concrete Design & Implementation Brief

## Intent

This document is the concrete implementation brief for the next coding round.

It locks what is already signed off, defines what belongs in Settings, records pixel measurements from the latest screenshots, and gives exact comparison instructions for the next matrix of screenshots.

---

## Signed-off decisions

These are **done** for now and should not be reopened unless a comparison matrix clearly disproves them:

- Hebrew-first face
- black hero theme
- no seconds
- `Noto Sans Hebrew Bold`
- tapered baton hands
- no glyph recoloring
- no per-letter shape distortion or custom redrawing of Hebrew glyphs
- hero screenshots should be captured with **date off**
- date remains a product feature, but not part of the hero composition by default

---

## Important typography rule

Do **not** modify the shapes of individual Hebrew letters just to make narrow glyphs feel heavier.

Reason:
- Hebrew readers will notice shape tampering immediately
- the face should preserve the integrity of the letterforms
- if balance is imperfect, solve it by **font choice, global marker size, x/y placement, spacing, and composition**, not by “fixing” specific letters

Allowed:
- per-position x/y offsets
- pack-level font choice
- pack-level font size
- date placement changes
- dial-center changes
- hand geometry changes

Not allowed in this round:
- hand-editing one glyph differently from the rest
- scaling one Hebrew letter independently from the others
- replacing only one or two glyphs with artistically modified variants

---

## Settings screen rules

The Settings screen should stay minimal.

### Show in Settings now

#### 1. Date
Type:
- toggle

Label:
- `Show date`

Default:
- `On` for normal product use

Design rule:
- the setting exists
- the hero screenshots for store/contest should still be captured with the date **off**

#### 2. Theme
Type:
- segmented choice or select

Label:
- `Theme`

Options:
- `Night`
- `Paper` only if Paper passes the visual gate

Default:
- `Night`

### Do not show in Settings yet

#### Accent color
Do not expose accent color in Settings in this round.
Use it only as an internal comparison variable.

#### Seconds
Do not expose.
Seconds remain off.

#### Script pack
Only expose this once a second polished pack actually exists.
Do not show a one-option picker.

---

## Pixel measurements from the latest screenshots

These measurements were taken from the current screenshots.

They are not guesses.
They come from pixel analysis of the uploaded images.

## Emery

Image size:
- `200 × 228`

Visible non-black content bounding box:
- `x = 24..172`
- `y = 23..199`

Estimated pivot / dial center from pixel density:
- `x = 99`
- `y = 101`

Date bounding box:
- `x = 86..115`
- `y = 189..199`

Lower marker band bounding box:
- `x = 61..138`
- `y = 153..171`

Margins:
- top `23`
- bottom `28`
- left `24`
- right `27`

Interpretation:
- Emery is the looser / less-finished layout
- the date sits **too low and too detached**
- the overall face is good, but the vertical composition is not yet as convincing as Gabbro

## Gabbro

Image size:
- `260 × 260`

Visible non-black content bounding box:
- `x = 30..225`
- `y = 31..229`

Estimated pivot / dial center from pixel density:
- `x = 130`
- `y = 126`

Date bounding box:
- `x = 116..145`
- `y = 189..199`

Lower marker band bounding box:
- `x = 43..215`
- `y = 172..183`

Margins:
- top `31`
- bottom `30`
- left `30`
- right `34`

Interpretation:
- Gabbro is already the stronger composition
- the date is acceptable here
- the face is close to submission quality once hero/date rules are locked

---

## Concrete changes required

## 1. Keep glyph shapes untouched

Implementation instruction:
- keep `Noto Sans Hebrew Bold`
- keep the same glyph rendering path
- do not special-case `י` or `ו` by altering their letterforms
- do not introduce per-glyph scaling hacks in this round

What to adjust instead:
- x/y placement
- date placement
- hand geometry
- hub geometry
- theme/color treatment

## 2. Lock date policy

Implementation instruction:
- hero/store/contest screenshots: `date = off`
- product build: `date = on` by default
- settings toggle exists: `Show date`

### Date compare positions

Use **text top y** as the variable.

#### Emery date matrix
Compare:
- `date_off`
- `date_on_y184`
- `date_on_y188`
- `date_on_y192` (current is close to this)

Recommendation:
- Emery is most likely to benefit from `y184` or `y188`

#### Gabbro date matrix
Compare:
- `date_off`
- `date_on_y189` (current)
- `date_on_y193`
- `date_on_y197`

Recommendation:
- Gabbro is most likely to keep `y189` or `y193`

## 3. Tune each device independently

Do **not** just scale one layout into the other.

### Emery
Treat Emery as its own composition.

First-round tuning instruction:
- keep pivot around `x99`
- compare `pivot_y = 101` vs `pivot_y = 103`
- do not move it more than `+2` px in this round

Goal:
- slightly relax the vertical composition without creating new crowding

### Gabbro
Treat Gabbro as nearly locked.

First-round tuning instruction:
- keep pivot at `x130`
- compare `pivot_y = 126` vs `pivot_y = 128`
- do not move it more than `+2` px in this round

Goal:
- verify whether a tiny downward shift improves the hero version with date off

## 4. Hand geometry changes

Keep tapered baton as the only active hand family for the next round.

### Emery hand matrix
Estimated current minute reach from screenshot:
- about `46 px`

Compare:
- `hour_len = 30, minute_len = 46`
- `hour_len = 30, minute_len = 42`
- `hour_len = 32, minute_len = 44`

Use:
- hour width `5`
- minute width `3`
- tapered tip width `2`

### Gabbro hand matrix
Estimated current minute reach from screenshot:
- about `67 px`

Compare:
- `hour_len = 40, minute_len = 67`
- `hour_len = 40, minute_len = 63`
- `hour_len = 42, minute_len = 65`

Use:
- hour width `6`
- minute width `4`
- tapered tip width `2`

Goal:
- reduce visual tension with the glyph ring
- keep the hands elegant
- do not re-open hand family choice

## 5. Center hub changes

Only compare **subtle** hub variants.

### Hub matrix
Compare:
- `hub_a`: fill radius `4`, outline `1`
- `hub_b`: fill radius `3`, outline `1`
- `hub_c`: fill radius `3`, no outline`

Recommendation:
- start with `hub_b`
- `hub_c` is allowed only if the center still feels finished

---

## Position-only optical tuning

Because glyph shapes are locked, only use **position** changes.

### Optional micro-offset comparison set

Apply only if needed after the date and hand passes.

#### Emery offset set B
- 10: `(-1, -1)`
- 11: `(-1, -1)`
- 12: `(0, -1)`
- 1: `(1, -1)`
- 5: `(1, 0)`
- 6: `(0, 1)`
- 7: `(-1, 0)`

#### Gabbro offset set B
- 10: `(-1, -1)`
- 11: `(-1, -2)`
- 12: `(0, -2)`
- 1: `(1, -1)`
- 5: `(1, 1)`
- 6: `(0, 1)`
- 7: `(-1, 1)`

Use this as a comparison set only.
Do not apply blindly if the current placement already looks better.

---

## Color policy

### Important platform note

Official docs explicitly say Emery supports `64 colors`, and the Pebble SDK exposes a named 64-color palette through `GColor` constants. The official docs are much clearer about Emery than Gabbro, so treat Gabbro color as something to verify in `spalding_gabbro` QEMU before shipping color-based screenshots. The color constants below are the correct Pebble palette constants for color-capable platforms.

### Background and neutral colors
- black background: `GColorBlack` / `GColorBlackARGB8` = `0b11000000`
- white neutral: `GColorWhite` / `GColorWhiteARGB8` = `0b11111111`

### Gold candidates
- muted gold 1: `GColorBrass` / `GColorBrassARGB8` = `0b11101001`
- muted gold 2: `GColorWindsorTan` / `GColorWindsorTanARGB8` = `0b11100100`

### Red candidates
- deep red 1: `GColorDarkCandyAppleRed` / `GColorDarkCandyAppleRedARGB8` = `0b11100000`
- deep red 2: `GColorBulgarianRose` / `GColorBulgarianRoseARGB8` = `0b11010000`

### Accent usage rule
Only the **hour hand** may use the accent color in this round.
Optional:
- center-hub outline may match the hour-hand accent

Do not recolor:
- glyphs
- date
- minute hand
- background

Use `PBL_IF_COLOR_ELSE()` or `COLOR_FALLBACK()` so the face still renders cleanly in white if color is unavailable.

---

## Required screenshot matrices

Run these in order.

### Matrix A — hero composition
For each platform:
- date off
- hub_a / hub_b / hub_c
- current hand lengths vs shortened hand lengths

Goal:
- pick the strongest hero layout in monochrome

### Matrix B — date comparison
For each platform:
- chosen hub
- chosen hand lengths
- date off
- 3 date y positions from the lists above

Goal:
- choose product date placement
- keep hero screenshot date off even if product default is on

### Matrix C — color comparison
For each platform using the chosen geometry:
- monochrome
- `GColorBrass`
- `GColorWindsorTan`
- `GColorDarkCandyAppleRed`
- `GColorBulgarianRose`

Goal:
- decide whether color actually improves the face
- if not, stay monochrome

### Matrix D — optional micro-offset comparison
For each platform:
- chosen geometry
- chosen date behavior
- current offsets
- offset set B

Goal:
- decide whether the face benefits from micro-optical placement changes

---

## Release-direction recommendation

Most likely final direction:
- Hebrew
- black theme
- tapered baton
- `Noto Sans Hebrew Bold`
- date off in hero screenshots
- date on in product with a settings toggle
- monochrome or `GColorBrass` hour hand only if it clearly wins the matrix

If there is no obvious winner in the color matrix, ship **monochrome**.

---

## What not to do in this round

- do not redesign the glyphs
- do not add seconds
- do not expose accent color in Settings
- do not expose script pack until a second polished pack exists
- do not chase many variations at once

This round is about locking a premium final direction, not expanding features.
