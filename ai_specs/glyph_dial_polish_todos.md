# Glyph Dial Polish TODOs

## Purpose

This document captures the current visual and design issues discovered during the first implementation pass of `Glyph Dial`.

The goal is to use this as the next-pass polish checklist before contest submission screenshots and store preparation.

## Locked V1 Decisions

- Hebrew-first.
- Noto Sans Hebrew Bold.
- Black theme primary.
- No seconds.
- No date.
- Monochrome default.
- Tapered baton hands.
- Small outlined hub with fill radius 2 and outline width 1.
- Emery locked at center `(99,100)`, hour `46`, minute `68`.
- Gabbro locked at center `(131,128)`, hour `50`, minute `74`.
- Brass is not in Settings for v1.

## Resolved Round 4 Items

- Hand reach is locked after the longer-hand and Emery micro-rounds.
- The center hub decision is locked to the smaller outlined hub.
- Date crowding is resolved by removing date from v1.
- Monochrome beat brass as the v1 identity.

## Remaining Visual Fixes

### 1. Verify final hand-to-glyph clearance

Status:
- final geometry is locked, but final canonical screenshots should still be checked before submission

Check:
- Emery `E11_hub2`
- Gabbro `G9_hub2`

Success criteria:
- hands create near-kiss tension without cutting through glyph pixels
- the watchface remains balanced on both Emery and Gabbro

### 2. Fix Hebrew 11 and 12 ordering in final screenshots

Problem:
- in screenshots, `11` and `12` still appear reversed
- this must be corrected before final presentation or submission

Potential fixes:
- verify the rendered asset source strings again
- inspect whether ImageMagick font shaping is reversing unexpectedly
- consider rendering `יא` and `יב` manually as custom composed assets
- if needed, switch those two glyphs to hand-tuned image compositions instead of generated text

Success criteria:
- `11` renders as `יא`
- `12` renders as `יב`
- both appear correctly in generated marker sheets and on-watch screenshots

## Typography Review

### 3. Reconsider the Hebrew font choice

Problem:
- the current Hebrew font may not be the strongest visual choice
- it is functional, but may not be the prettiest or most distinctive

Potential fixes:
- test 2 to 4 alternative Hebrew fonts
- compare elegance, clarity, and personality at Emery and Gabbro sizes
- pay special attention to:
  - `א`
  - `ו`
  - `ז`
  - `ט`
  - `י`
  - `יא`
  - `יב`

Evaluation criteria:
- beauty in screenshots
- consistency around the dial
- clarity at small size
- whether 11 and 12 remain readable and balanced

## Hands Design Review

### 4. Improve hand styling

Problem:
- the current hands work technically, but they may be too plain
- they do not yet fully match the intended premium typographic look

Potential fixes:
- use tapered polygon hands instead of simple thick lines
- slightly differentiate hour and minute hand shapes
- refine thickness and length balance
- consider a more intentional tip shape
- test whether thinner or more elegant hands improve the overall face

Success criteria:
- hands feel more refined
- hands support the glyphs without competing with them
- readability remains strong

### 5. Center point decision

Status:
- locked for v1 as a small outlined hub, fill radius 2 and outline width 1.

Future work:
- do not reopen before v1 unless final screenshots expose a concrete issue.

## Theme Support

### 6. Finish white-background support

Problem:
- white background support is desired, but needs visual verification and likely tuning

Needed work:
- confirm the paper theme renders correctly with all markers
- verify image inversion quality for glyphs
- ensure hands and center hub look intentional on white
- capture screenshots for the paper variant on both devices

Success criteria:
- the white theme looks designed, not merely inverted
- contrast and elegance remain strong

## Suggested Next Pass Order

1. Verify final canonical screenshots on both devices.
2. Fix Hebrew `11` and `12` ordering definitively if screenshots regress.
3. Compare Hebrew font alternatives only if Noto Sans Hebrew Bold fails final review.
4. Finalize and verify white-background support.

## Submission Readiness Gate

Before final contest screenshots, verify:
- Hebrew markers are ordered correctly
- hands create intentional near-kiss tension without cutting through markers
- chosen Hebrew font is signed off
- chosen hand style is signed off
- center cap decision is signed off
- black and white themes both look intentional
