# Glyph Dial Visual Design Spec v1

## Purpose

This document captures the **current intended visual design** of `Glyph Dial` for implementation and review.

It is not the final immutable design bible.
It is the working visual spec for the current Hebrew-first release direction.

The goal is to make the watchface feel like a **real designed object**, not just a clever script experiment.

---

## Product Summary

`Glyph Dial` is a minimalist analog watchface where the hour markers are replaced by carefully selected glyphs from a writing or numeral system.

The initial hero version is:
- **Hebrew-first**
- **black theme first**
- **analog**
- **calm**
- **high-contrast**
- **premium and restrained**

A future second pack such as Arabic-Indic may use the same underlying layout and design system.

---

## Product Intent

The face should feel:

- elegant
- calm
- literate
- modern
- slightly luxurious
- intentional
- wearable every day

The face should **not** feel:

- educational
- novelty-driven
- mystical
- overly technical
- playful
- busy
- like a developer draft

---

## Core Composition

### Primary elements

The face is made of:

1. hour glyph ring
2. hour hand
3. minute hand
4. center hub
5. optional date

### Visual hierarchy

The intended hierarchy is:

1. **glyph ring**
2. **hands**
3. **center hub**
4. **date**

The date must always stay secondary.
The hands must support the glyphs, not dominate them.

---

## Theme Direction

### Hero theme: Night

Primary visual language:
- black background
- white glyphs
- white date
- white or neutral minute hand
- white or accent hour hand depending on chosen direction

This is the default and hero presentation.

### Secondary theme: Paper

Secondary visual language:
- white background
- black glyphs
- black date
- black or neutral minute hand
- black or accent hour hand depending on chosen direction

This theme is optional and only ships if it looks intentional.

---

## Accent Color Strategy

The face is fundamentally monochrome.

If color is used, it is used only as a **single restrained accent**.

### Allowed accent usage

The accent may be used on:
- hour hand
- optionally a tiny center-hub ring

### Forbidden accent usage in v1

Do not use accent color on:
- glyphs
- date
- background
- multiple competing elements

### Candidate accents

1. muted gold
2. deep muted red

### Accent decision rule

A color accent should only survive if it makes the face feel:
- more premium
- more intentional
- more memorable

If it makes the face feel loud, gimmicky, or less timeless, remove it.

---

## Geometry Guidance

## Gabbro

Nominal screen size:
- 260 × 260

Working center:
- (130, 130)

Current target geometry:
- marker ring radius: about 90
- hour hand length: about 56
- minute hand length: about 82
- center clear radius: about 18
- date baseline: about y 188

### Marker size guidance
- primary target around 28 px
- allow optical exceptions for wider glyphs

## Emery

Nominal screen size:
- 200 × 228

Working visual center:
- (100, 108)

Current target geometry:
- marker ring radius: about 68
- hour hand length: about 44
- minute hand length: about 64
- center clear radius: about 16
- date baseline: about y 166

### Marker size guidance
- primary target around 22 px
- allow optical exceptions for wider glyphs

---

## Marker Ring Design

### Principle

The marker ring is the product identity.
It needs optical tuning, not just polar math.

### Placement rules

- start from evenly spaced analog positions
- apply per-position optical offsets
- prioritize visual balance over mathematical purity
- keep 12, 3, 6, and 9 especially convincing
- pay extra attention to the 10, 11, 12, 1 cluster and the 5, 6, 7 cluster

### Marker rendering options

The Hebrew pack may be rendered via:
- subsetted font glyphs
- pre-rendered image markers

The final choice should be based on visual quality first.

### Hebrew-specific note

`יא` and `יב` must be treated as first-class dial markers, not as an afterthought.
If they need hand-tuned assets, that is acceptable.

---

## Hands Design

### General intent

The hands should feel:
- clean
- refined
- not mechanical for the sake of it
- not ornamental
- clearly designed

### Shape direction

Preferred direction:
- tapered baton hands

Variants worth testing:
- simple baton
- tapered baton
- tapered baton with subtle pointed tip

### Relative hierarchy

- hour hand slightly heavier
- minute hand longer and slimmer
- both should stay clear of the marker ring

### Anti-goal

The hands must not feel like generic thick canvas lines.

---

## Center Hub

The center hub should solve the analog composition without becoming a visual lump.

### Candidate hub types

- none
- tiny filled dot
- filled circle with subtle outline
- thin ring cap

### Preferred behavior

The hub should be:
- small
- calm
- slightly refined
- visually tied to the hands

A heavy hub is not acceptable.

---

## Date Design

### Role

The date is optional support information, not a headline.

### Rules

- it must sit below the hand system
- it must not visually merge with the 5, 6, 7 markers
- it should stay quiet
- the hero screenshot may omit it

### Formats

Candidate formats:
- `14 Apr`
- numeric only
- pack-specific digits with minimal complexity

### Current design direction

- black theme first
- no seconds
- date likely enabled in product, but not necessarily shown in the hero shot

---

## Typography Direction

### Desired qualities

The typography should be:
- beautiful
- small-size legible
- compact
- distinctive
- clean in silhouette

### Strong Hebrew candidates to evaluate

- Alef Bold
- Heebo Medium
- Assistant SemiBold

### Evaluation criteria

Judge each candidate on:
- beauty on wrist
- beauty in screenshot
- clarity at target sizes
- balance of `א`, `ו`, `ז`, `ט`, `י`, `יא`, `יב`
- ring harmony as a whole

---

## Visual Tuning Priorities

The most important places to tune are:

### Top arc
- 10
- 11
- 12
- 1

This arc must feel elegant and stable.

### Lower half
- 5
- 6
- 7
- date

This area currently has the highest risk of crowding and must become calmer.

### Hands vs ring
The hands must stop just short of tension.
The minute hand especially should feel purposeful but not invasive.

---

## Hero Presentation Target

The current hero-image target should be:

- Hebrew pack
- black theme
- no seconds
- strongest hand set
- strongest hub option
- date off unless it clearly improves the screenshot
- one accent treatment at most

This is the benchmark for whether the face is visually “there.”

---

## Non-Goals for v1

Do not optimize v1 around:
- maximal configurability
- multiple accent settings
- mystical symbolism
- educational overlays
- many packs at once
- decorative textures
- busy complications

v1 should win through restraint.

---

## Final Visual Standard

The watchface should ultimately feel less like:

- “a cool hack”
- “a Hebrew gimmick”
- “a prototype analog dial”

and more like:

- “a real premium watchface”
- “a typographic object”
- “something I would actually wear”

That is the standard all design decisions should serve.
