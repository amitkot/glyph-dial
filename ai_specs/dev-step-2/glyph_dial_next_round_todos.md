# Glyph Dial Next-Round TODOs

## Purpose

This document is the **implementation brief for the next coding round** of `Glyph Dial`.

It is intended to be used directly by a coding agent and should drive the next pass of polish before final design sign-off, store assets, and contest submission.

The objective of this round is **not** to add features.
The objective is to make the current concept feel **intentional, premium, and screenshot-ready**.

---

## Round Status

This round has been superseded by the Round 4 lock.

Locked v1 decisions:
- no date
- no seconds
- monochrome default
- Noto Sans Hebrew Bold
- tapered baton hands
- small outlined hub, fill radius 2, outline width 1
- Emery `E11_hub2`: center `(99,100)`, hour `46`, minute `68`
- Gabbro `G9_hub2`: center `(131,128)`, hour `50`, minute `74`
- brass remains a future optional variant, not a v1 setting

## Round Goal

Ship a visibly improved version of the current Hebrew watchface by focusing on:

- correctness
- optical polish
- spacing
- hand design
- one strong visual identity

At the end of this round, we should have:
- a clean black-theme hero face
- a signed-off Hebrew pack
- a strong hand design
- a spacing-tuned layout on both devices
- side-by-side screenshots for visual decision making

---

## Priority Order

1. **Correctness and rendering stability**
2. **Layout and spacing polish**
3. **Hand redesign**
4. **Color/accent experiments**
5. **Theme verification**
6. **Screenshot automation and visual comparison**
7. **Preparation for second pack architecture**

---

## P0 — Correctness and Rendering Stability

### 1. Lock Hebrew 11 and 12 permanently

Problem:
- `יא` and `יב` must always render in the correct order.

Tasks:
- audit the source of the marker assets or generated glyph rendering
- verify whether any shaping, bidirectional handling, or asset-generation step is reversing glyph order
- if needed, switch `יא` and `יב` to manually composed assets
- add a tiny regression script or check that validates all 12 Hebrew hour markers before packaging assets

Deliverable:
- one verified source of truth for the 12 Hebrew markers

Success criteria:
- 11 always renders as `יא`
- 12 always renders as `יב`
- screenshots and runtime output match

### 2. Add marker-pack validation hooks

Tasks:
- define a pack data structure with 12 explicit marker entries
- validate marker count at startup or build time
- fail loudly if any asset or label is missing
- separate pack content from pack layout tuning

Success criteria:
- packs are deterministic and cannot silently degrade

---

## P1 — Layout and Spacing Polish

### 3. Finalize hand-to-marker tension

Status:
- resolved by Round 4 longer-hand matrices and Emery micro-round.

Locked variants:
- Emery `E11_hub2`
- Gabbro `G9_hub2`

Success criteria:
- the hands feel intentional, watch-like, and close to the glyph ring without collision

### 4. Clean up the lower zone

Status:
- date removed from v1, so the lower zone is intentionally simplified.

Tasks:
- test tiny inward/outward nudges for the 5, 6, 7 positions
- verify the 6 marker is visually part of the ring and not floating too low

Recommended visual rule:
- the bottom half should feel calmer than it does now

Success criteria:
- the lower half looks intentionally spaced

### 5. Add per-marker optical offsets

Problem:
- pure radial placement is not enough for typographic glyphs

Tasks:
- support per-position x/y offset tuning for each device
- support per-pack overrides
- allow minor manual corrections per marker position
- tune especially:
  - 10
  - 11
  - 12
  - 1
  - 5
  - 6
  - 7

Suggested data model:
- base polar anchor points
- per-position x/y nudge
- optional per-marker box width/height metadata if using images

Success criteria:
- the dial looks centered by eye, not only by math

---

## P2 — Hand Redesign

### 6. Replace simple strokes with intentional hand geometry

Problem:
- the current hands work, but still feel draft-like

Tasks:
- implement hands as polygons rather than thick lines
- create at least 3 hand variants:
  - **A. simple baton**
  - **B. tapered baton**
  - **C. tapered with subtle pointed tip**
- keep the minute hand longer and slimmer
- keep the hour hand slightly heavier
- compare all variants in screenshots

Recommended direction:
- tapered baton is the most promising default

Success criteria:
- the hands feel designed
- the hands support the glyphs instead of competing with them

### 7. Revisit the center hub

Status:
- resolved for v1.

Locked hub:
- fill radius 2
- outline width 1

Success criteria:
- the center feels finished, not heavy

---

## P3 — Typography and Marker Rendering

### 8. Run a Hebrew marker bakeoff

Problem:
- the current Hebrew font may be correct enough but not yet ideal

Tasks:
- test 2 to 4 Hebrew font candidates at real target sizes
- compare on-device or emulator screenshots only
- evaluate especially:
  - `א`
  - `ו`
  - `ז`
  - `ט`
  - `י`
  - `יא`
  - `יב`

Suggested candidate families from earlier research:
- Alef Bold
- Heebo Medium
- Assistant SemiBold
- optional premium image-based experiment from a more expressive Hebrew face

Success criteria:
- one clear winner for actual runtime use
- beauty and clarity both acceptable

### 9. Decide font vs image markers for the Hebrew pack

Tasks:
- compare:
  - live subsetted font markers
  - pre-rendered image markers
- judge the tradeoff across:
  - beauty
  - crispness
  - implementation complexity
  - resource size
  - scaling across Emery and Gabbro

Decision rule:
- choose images if they look materially better
- choose fonts if the visual quality is already excellent and the system stays cleaner

Success criteria:
- one marker-rendering approach is chosen for Hebrew v1

---

## P4 — Color and Accent Experiments

### 10. Test one restrained accent system

Problem:
- the face currently risks feeling too draft-like in pure black and white, but color must remain disciplined

Tasks:
- keep glyphs neutral
- color only the hour hand in experiments
- optionally color a very small center-cap ring to match the hour hand
- produce three comparison screenshots:
  - monochrome
  - brass hour hand

Decision rule:
- do not expose accent as a user setting in this round
- choose the single strongest result for release direction
- if neither accent is clearly better than monochrome, stay monochrome

Success criteria:
- one visual identity is chosen
- the face remains elegant and not gimmicky

### 11. Define implementation structure for accent support without exposing it yet

Tasks:
- centralize theme colors in one file or one table
- support a single accent color parameter internally
- keep release behavior simple even if the code is flexible

Success criteria:
- easy future expansion without UI complexity now

---

## P5 — Theme Verification

### 12. Verify the paper theme properly

Problem:
- inversion alone is not enough

Tasks:
- confirm marker contrast and edge quality on white
- confirm the hub still feels intentional
- verify hand contrast and legibility
- confirm no ugly asset inversion artifacts
- capture both devices

Decision rule:
- black theme is still the hero
- paper theme only ships if it feels designed, not automatic

Success criteria:
- paper theme passes a visual quality bar
- otherwise postpone it

---

## P6 — Screenshot and Visual Review Workflow

### 13. Create reproducible screenshot capture tasks

Tasks:
- create a repeatable script or documented process to capture screenshots from QEMU
- standardize the shown time for comparisons
- generate comparison sheets for:
  - hand variants
  - marker ring spacing
  - font candidates
  - color variants

Recommended fixed times:
- one asymmetrical time such as 8:07
- one near-top-heavy time such as 10:10
- one lower-half stress test such as 5:30

Success criteria:
- visual comparison becomes fast and objective

### 14. Define the hero screenshot target

Recommended hero target for this round:
- black theme
- no seconds
- no date
- strongest hand set
- strongest Hebrew marker rendering
- monochrome

Tasks:
- capture at least 3 hero candidates
- choose the strongest one by pure visual impact

Success criteria:
- we know what the product’s lead image wants to be

---

## P7 — Architecture for Expansion

### 15. Prepare clean pack architecture for Arabic-Indic later

This is not a polish-first task, but the code should not hardcode the Hebrew pack in a way that makes later expansion messy.

Tasks:
- separate pack content, pack metadata, and pack-specific optical offsets
- ensure a second pack can reuse the same drawing/layout logic
- do not yet spend time polishing Arabic-Indic until Hebrew is signed off

Success criteria:
- adding Arabic-Indic later is straightforward

---

## Out of Scope for This Round

Do not spend time on:
- seconds hand
- weather/battery complications
- mystical or Kabbalistic symbolism
- advanced configuration UI
- too many themes
- additional packs beyond minimal architectural prep
- store copy finalization

---

## Visual Quality Gate

Before calling this round done, verify:

- Hebrew markers render correctly
- the top arc feels balanced
- the bottom zone feels calm
- the chosen hands look intentional
- the chosen center hub looks intentional
- monochrome treatment is signed off
- the face looks strong in a no-date hero screenshot

---

## Recommended Execution Order

1. fix `יא` / `יב`
2. add marker-pack validation
3. adjust hand lengths and lower-zone spacing
4. implement per-marker optical offsets
5. implement 3 hand variants
6. test hub variants
7. run Hebrew font bakeoff
8. choose font vs image rendering
9. run monochrome vs muted gold vs muted red comparisons
10. verify paper theme
11. automate screenshot comparisons
12. lock one hero presentation

---

## Definition of Success for This Round

This round is successful if the next screenshots make the watchface feel:

- calmer
- more intentional
- more premium
- more contest-ready

The concept is already good enough.
This round is about making it look like a finished product.
