# Glyph Dial Polish TODOs

## Purpose

This document captures the current visual and design issues discovered during the first implementation pass of `Glyph Dial`.

The goal is to use this as the next-pass polish checklist before contest submission screenshots and store preparation.

## High-Priority Visual Fixes

### 1. Increase hand-to-glyph clearance

Problem:
- the hour and minute hands get too close to the glyph ring
- this weakens readability and makes the composition feel cramped

Potential fixes:
- shorten the minute hand slightly
- shorten the hour hand slightly
- move the glyph ring outward where possible
- reduce marker size on crowded positions
- use more tapered or narrower hand geometry

Success criteria:
- hands no longer feel like they crash into the glyphs
- the watchface remains balanced on both Emery and Gabbro

### 2. Add more date clearance

Problem:
- the date almost overlaps the lower glyphs, especially on Emery

Potential fixes:
- move the date lower
- move the dial center slightly higher
- reduce date font size
- reduce lower marker radius slightly
- hide date in tighter layouts or when space is compromised

Success criteria:
- the date feels quiet and clearly separated from the markers
- lower dial positions remain visually clean

### 3. Fix Hebrew 11 and 12 ordering in final screenshots

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

### 4. Reconsider the Hebrew font choice

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

### 5. Improve hand styling

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

### 6. Decide whether the center point belongs in the design

Question:
- do we want the middle point with the hands in this design?

Considerations:
- a center cap can make the analog hands feel more complete and realistic
- it can also add visual clutter in a design that wants extreme restraint
- it may be worth testing:
  - no center cap
  - small filled cap
  - ring cap
  - subtle cap only on one theme

Decision criteria:
- does the center feel finished without it?
- does removing it make the dial calmer?
- does it help or hurt the typographic focus?

## Theme Support

### 7. Finish white-background support

Problem:
- white background support is desired, but needs visual verification and likely tuning

Needed work:
- confirm the paper theme renders correctly with all markers
- verify image inversion quality for glyphs
- ensure hands, date, and any center cap look intentional on white
- capture screenshots for the paper variant on both devices

Success criteria:
- the white theme looks designed, not merely inverted
- contrast and elegance remain strong

## Suggested Next Pass Order

1. Fix Hebrew `11` and `12` ordering definitively.
2. Improve date and hand clearance on Emery.
3. Tune hand styling.
4. Decide on center cap behavior.
5. Compare Hebrew font alternatives.
6. Finalize and verify white-background support.
7. Re-capture screenshots on both devices.

## Submission Readiness Gate

Before final contest screenshots, verify:
- Hebrew markers are ordered correctly
- hands do not crowd markers
- date does not crowd markers
- chosen Hebrew font is signed off
- chosen hand style is signed off
- center cap decision is signed off
- black and white themes both look intentional
