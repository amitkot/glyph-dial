# Pebble Script Dial Plan

## TL;DR

We will build **one Pebble watchface app** with **multiple script packs**, led by a **Hebrew hero pack** and launched first on **Emery (Pebble Time 2)** and **Gabbro (Pebble Round 2)**.

The product position is:
- **A refined typographic analog watchface**
- **Distinctive enough to stand out in the Pebble contest**
- **Wearable enough to actually use every day**
- **Flexible enough to expand into Arabic-Indic, Persian, and future numeral systems without changing the core app**

The v1 app should prioritize:
- strong visual identity
- very high readability
- low implementation risk
- clean screenshots for contest and store

The recommended build path is:
1. **Implement in C**, not Alloy, for lower risk and fuller control
2. Build the **Hebrew pack first**
3. Add **Arabic-Indic** as the second pack
4. Keep **seconds off by default**
5. Keep **date optional, on by default in v1 if it looks clean**
6. Use **a black default theme** and an optional inverted theme
7. Ship as **one configurable app**, not separate apps per language

---

## Product Vision

### Product name direction
Working product names:
- **Script Dial**
- **Glyph Dial**
- **Hour Glyphs**
- **Script Hours**

Recommended working title for development:
**Script Dial**

Reason:
- broad enough to support multiple script packs
- elegant and descriptive
- does not falsely imply only abjad systems
- works for Hebrew-first positioning while leaving room for Arabic-Indic and Persian

### Core idea
A minimalist analog watchface where the twelve hour markers are replaced by visually curated glyphs from a selected writing or numeral system.

This is not meant to be a novelty “educational script sampler.”
It should feel like:
- a premium typographic object
- culturally grounded
- immediately striking in screenshots
- calm and wearable on the wrist

### Contest positioning
This app should aim for both:
- **judge appeal**, through originality, elegance, restraint, and platform-aware execution
- **hearts appeal**, through beautiful screenshots, a clear concept, and a memorable visual identity

### Positioning statement
**Script Dial is a refined analog watchface for Pebble Time 2 and Pebble Round 2 that expresses time through historic and modern writing systems, starting with a distinctive Hebrew-led design and optional Arabic-Indic and Persian numeral packs.**

---

## Strategic Scope

### Why one configurable app instead of separate apps
Use **one watchface app with selectable packs**.

Reasons:
- one codebase
- one store listing
- easier maintenance
- easier contest marketing
- cleaner upgrade path
- stronger product identity
- avoids splitting hearts and attention between variants

### Why Hebrew-first
Lead with **Hebrew** as the hero pack.

Reasons:
- less crowded than generic Arabic-dial aesthetics
- more distinctive in the Pebble ecosystem
- more personal and memorable
- stronger contest-story angle

Arabic-Indic should still be included as a strong secondary pack because:
- it is elegant
- it is highly legible when drawn well
- it broadens appeal
- it shows the concept is a family, not just one niche skin

### Packs to include in scope

#### v1 must-have
- **Hebrew pack**
- **Arabic-Indic pack**

#### v1 stretch
- **Persian pack**

#### post-v1 exploration
- Maya numerals
- Korean pack
- Chinese pack
- binary pack
- quipu-inspired or abacus-inspired concept as a separate face family

### What is explicitly out of scope for v1
- Kabbalistic or mystical symbolism
- religious framing
- mixed-script experimental face layouts
- music integration
- seconds-heavy animation
- weather, health, battery, or Bluetooth complications
- educational overlays beyond a simple optional legend or onboarding note

---

## Product Rules

The face should obey these rules:
- the glyphs are the star
- the hands support the glyphs, not compete with them
- the face must look good in static screenshots
- the face must remain readable after quick habituation
- every optional feature must serve calmness and polish, not novelty

If a feature harms elegance or readability, it gets removed.

---

## Platform and Technical Direction

### Target platforms
Only target:
- **Emery**
- **Gabbro**

This keeps the geometry, constraints, and art direction focused on the new devices.

### Framework choice
Recommended implementation: **C SDK**

Reasoning:
- lowest implementation risk
- broadest mature API coverage
- easier to control custom drawing precisely
- easiest path for analog hands, fonts, images, configuration, and unobstructed area support
- less uncertainty than Alloy for a contest delivery

### Build system and project structure
Create a clean Pebble watchface project in C.

Recommended high-level structure:
- `src/c/main.c`
- `src/c/layout.h`
- `src/c/layout.c`
- `src/c/state.h`
- `src/c/state.c`
- `src/c/draw.h`
- `src/c/draw.c`
- `src/c/settings.h`
- `src/c/settings.c`
- `resources/fonts/`
- `resources/images/`
- `resources/config/`

This is slightly more structured than strictly necessary, but it keeps the project easy to evolve.

### Rendering strategy
Recommended v1 rendering model:
- draw hands programmatically
- render markers using either **custom font glyphs** or **individual placed image assets**
- render date with text
- avoid unnecessary animation

### Fonts vs images decision
Current recommendation:
- prototype both quickly
- **likely final choice**:
  - hour markers as **image assets** for Hebrew if visual tuning matters most
  - date and supporting text with system fonts or small custom font if needed

If the visual language becomes more systematic across multiple packs, move markers to custom fonts.

### Resource strategy
Keep the resource budget conservative.

Even though the newer devices allow much more, the project should stay lean.
Use:
- minimal image assets
- subsetted fonts only
- no decorative backgrounds in v1
- no full-screen bitmap art in v1

---

## Design System

### Overall look
Primary aesthetic:
- black background
- white glyphs
- white hands
- restrained high-contrast dial
- premium minimalist analog feel

Secondary theme:
- white background
- black glyphs
- black hands

No faux gradients, no photorealistic texture, no ornamental rings in v1.

### Character of the face
The face should feel:
- modern
- calm
- literate
- slightly luxurious
- not playful
- not mystical
- not dense

### Visual hierarchy
1. hour glyph markers
2. hour and minute hands
3. center cap
4. date
5. optional secondary settings items

### Symmetry and rhythm
- use even radial spacing
- allow slight optical correction for glyphs that are visually unbalanced
- prioritize visual centering over purely mathematical centering
- keep 12, 3, 6, 9 especially strong and aligned

---

## Detailed Layout Spec

## Gabbro layout
Screen: **260 × 260**
Center: **(130, 130)**

### Dial geometry
- outer safe dial radius: **102**
- marker center radius: **90**
- visual inner hand-safe radius: about **84**
- center clear radius: about **18**

### Hands
- hour hand length: **56**
- hour hand width: **6**
- minute hand length: **82**
- minute hand width: **4**
- center cap radius: **5**

### Marker sizing
Initial candidate sizes:
- compact: **24 px box / approx 24 px font size**
- default: **28 px box / approx 28 px font size**
- bold: **32 px box / approx 32 px font size**

Recommended first pass:
- **28 px nominal marker size**
- allow optically wider glyph boxes for certain symbols

### Date
- centered horizontally
- baseline around **y = 188**
- target size: **18 px**
- keep it narrow and quiet

### Composition note
The face on Gabbro should look like a premium round analog watch, not like a digital layout forced into a circle.

---

## Emery layout
Screen: **200 × 228**
Visual dial center: **(100, 108)**

### Dial geometry
- outer safe dial radius: **78**
- marker center radius: **68**
- visual inner hand-safe radius: about **62**
- center clear radius: about **16**

### Hands
- hour hand length: **44**
- hour hand width: **5**
- minute hand length: **64**
- minute hand width: **3**
- center cap radius: **4**

### Marker sizing
Initial candidate sizes:
- compact: **20 px**
- default: **22 px**
- bold: **24 px**

Recommended first pass:
- **22 px nominal marker size**

### Date
- centered horizontally
- baseline around **y = 166**
- target size: **16 px**

### Composition note
The face on Emery must stay a little higher and more compact, leaving room for a clean date and graceful unobstructed-area adaptation.

---

## Marker Placement Rules

### General rules
- markers should be placed around the radial ring, not in a text layer
- use individual anchor points or polar placement
- apply per-glyph optical offsets if needed
- keep vertical and diagonal glyphs from appearing tilted or off-center by using manual per-position adjustments

### Hour positions
Use the traditional 12 analog positions.

The final implementation should support:
- exact polar anchor generation
- per-pack adjustment table
- optional per-glyph x/y nudges

This means we should compute the 12 positions programmatically and then allow per-pack overrides.

---

## Hands Design

### Style
Use clean baton hands.

Do not use:
- ornate hands
- skeleton hands
- thick decorative hands
- second-hand circles or aggressive tips in v1

### Color
- black theme: white hands
- inverted theme: black hands

### Rendering
Programmatically draw hands from center.
Use anti-aliased or crisp line/filled-shape strategy appropriate to Pebble rendering.

### Design principle
The hands should never visually crash into the glyphs.

If necessary:
- shorten the minute hand slightly
- lighten the hour hand taper
- adjust marker ring radius outward by 2 to 4 px

---

## Seconds Policy

### Recommendation
**No seconds in v1 default behavior.**

Reasons:
- calmer face
- cleaner screenshots
- lower battery use
- fewer redraws
- stronger premium feel
- keeps attention on the glyph concept

### Optional future setting
Possible future options:
- seconds off
- subtle seconds dot on perimeter
- ultra-thin seconds hand

Do not implement this unless the core face is already excellent.

---

## Date Policy

### Recommendation
**Date is optional and likely on by default if it looks clean.**

### Best v1 version
- one centered line below the center
- numeric day plus short month or simple numeric date depending on pack
- visually quiet
- never larger than necessary

### Candidate date formats
- `12 Apr`
- `12/04`
- pack-specific digits with Latin month abbreviation
- pack-specific digits only

### Recommended v1
- Hebrew hero pack: start with **simple Latin month + Arabic numerals** or just numeric date
- Arabic-Indic pack: date in **Arabic-Indic digits**
- Persian pack: Persian digits if included

If the date weakens the design, turn it off by default and make it configurable.

---

## Font Recommendations

## Primary typography goal
Find typefaces that feel elegant and high-contrast at small sizes, not quirky or decorative.

### For watch markers
Desired qualities:
- excellent small-size clarity
- strong black-white silhouette
- compact width
- distinct shapes for the twelve selected symbols
- low visual noise

### For supporting text
Desired qualities:
- unobtrusive
- highly legible
- modern sans-serif tone

### Recommended approach
Test two parallel routes:

#### Route A: Curated marker images
Best for:
- Hebrew hero pack
- maximum visual control
- contest screenshots

#### Route B: Custom font-based markers
Best for:
- consistent cross-pack system
- reusable date and legend support
- easier pack expansion

### Specific font selection process
For each script pack, shortlist 2 to 3 candidates and score them on:
- readability at 22 px and 28 px
- distinctiveness
- elegance
- balance around the dial
- resource size after subsetting

### Pebble font usage rules
- subset aggressively
- one font resource per needed size
- avoid excess glyphs
- keep total font resources small

### Practical initial font-size targets
- Gabbro marker font test sizes: **24, 28, 32**
- Emery marker font test sizes: **20, 22, 24**
- Supporting date font sizes: **16, 18**

### Supporting text font recommendation
Use Pebble system fonts for date in the first implementation unless the custom date typography is clearly better.

This reduces risk and resource usage.

---

## Color and Theme System

### Theme 1: Night
- background: black
- glyphs: white
- hands: white
- date: white
- center cap: white outline or white fill depending on render quality

### Theme 2: Paper
- background: white
- glyphs: black
- hands: black
- date: black

### Future theme option
- warm paper variant
- cool graphite variant

Only if supported cleanly by Pebble color capabilities and without undermining clarity.

### v1 rule
Ship with only the two strongest themes.

---

## Interaction and Configuration

### User settings to support in v1
Recommended settings:
- script pack
- theme: night or paper
- date: on or off
- maybe 12h/24h behavior inherited from system rather than explicit setting

### Optional setting for later
- seconds display mode
- marker weight variant
- compact vs spacious layout

### Configuration framework
Use **Clay** for configuration.

### Configuration philosophy
Keep the settings page short and premium.
The app should not feel like a dashboard of knobs.

---

## Quick View and Layout Adaptation

### Emery requirement
Support unobstructed area behavior so the face adapts cleanly when the lower area is obstructed.

### Behavior recommendation
When obstructed:
- keep background full-screen
- keep hands and glyphs stable if possible
- hide or raise the date
- slightly compress vertical composition if needed

### Gabbro note
Round behavior is simpler here. Keep the round face clean and centered.

---

## Implementation Plan

## Phase 1: Product skeleton
Deliverables:
- project created in C
- watchface metadata configured
- target platforms limited to Emery and Gabbro
- empty window and base draw loop
- minute tick subscription only

### Success criteria
A black watchface runs on both targets and updates time correctly.

## Phase 2: Core analog rendering
Deliverables:
- hour hand
- minute hand
- center cap
- device-specific layout constants

### Success criteria
Both devices show a clean analog skeleton.

## Phase 3: Marker system
Deliverables:
- marker placement table or polar placement helper
- Hebrew pack integrated
- ability to swap marker set data

### Success criteria
Hebrew version looks intentional and centered on both platforms.

## Phase 4: Date and unobstructed-area support
Deliverables:
- optional date
- date hide/reflow on obstruction for Emery

### Success criteria
The face remains elegant with and without date.

## Phase 5: Configuration
Deliverables:
- Clay configuration page
- script pack selection
- theme selection
- date toggle

### Success criteria
Config persists and renders correctly.

## Phase 6: Arabic-Indic pack
Deliverables:
- second pack added
- optical tuning per marker if needed

### Success criteria
Second pack feels equally premium, not like a quick skin.

## Phase 7: Polishing and appstore prep
Deliverables:
- screenshots on both devices
- store copy
- banner concept
- release notes
- contest submission timing plan

### Success criteria
The product feels complete and marketable.

---

## Technical Risks and Mitigations

### Risk 1: glyph readability at small sizes
Mitigation:
- prototype multiple sizes early
- use image markers if fonts do not hold up
- simplify the hero pack rather than forcing a weak font

### Risk 2: visual imbalance between the 12 glyphs
Mitigation:
- allow manual optical offsets per marker
- use curated asset variants if needed

### Risk 3: Emery layout feels cramped with date
Mitigation:
- raise dial center slightly
- make date optional
- hide date under obstruction

### Risk 4: too many packs dilute quality
Mitigation:
- ship only two strong packs first

### Risk 5: the concept feels too niche
Mitigation:
- use strong, clean screenshots
- keep copy focused on beauty and typography, not on scholarship

---

## App Metadata Plan

### App kind
- watchface

### Platforms
- emery
- gabbro

### Capabilities
- configurable

### Basic metadata to prepare
- display name
- UUID
- version
- author
- source URL
- support email
- website URL if available

### Naming direction for listing
Shortlist:
- Script Dial
- Glyph Dial
- Script Hours

Recommended current choice:
**Script Dial**

---

## Appstore and Marketing Asset Plan

## Store positioning
The store page should sell three things immediately:
- this is beautiful
- this is original
- this is still wearable

### Store description strategy
The description should lead with:
- analog elegance
- configurable script packs
- support for Time 2 and Round 2
- optional date and themes

It should not lead with:
- religion
- mysticism
- obscure terminology
- scholarly explanation

### Required store materials to prepare
Per supported platform asset collection:
- description
- screenshots
- optional marketing banner

### Watchface screenshot strategy
Need screenshots for:
- Gabbro hero shot, no date
- Gabbro with date
- Emery hero shot, no date
- Emery with date
- pack comparison or theme comparison if needed

### Screenshot rule
Use actual app screenshots only for the screenshot slots.
Do not use product mockups in screenshot slots.

### Marketing banner strategy
The banner can use a watch mockup plus title and one-line headline.

### One-line headline candidates
- **Analog time in a new script**
- **A typographic analog face for Pebble**
- **Historic glyphs, modern watchface**
- **An elegant analog dial in Hebrew and beyond**

### Release notes strategy
Version 1.0 release notes should be concise and polished.

Candidate:
- **Initial release for Pebble Time 2 and Pebble Round 2. Includes Hebrew and Arabic-Indic script packs, optional date, and light/dark themes.**

---

## Contest and Launch Plan

### Launch goal
Ship in time to:
- publish publicly
- collect hearts
- share direct store links
- promote on Pebble channels

### Promotion checklist
Prepare:
- appstore public link
- deep link for mobile app
- 1 to 2 clean promo images using watch mockups
- short post for Discord
- short post for Reddit if appropriate
- optional short post for Bluesky or Mastodon

### Messaging angle
Lead with:
- new watchface for Time 2 and Round 2
- elegant script-driven analog concept
- Hebrew-first with Arabic-Indic support

Avoid overexplaining.

---

## Recommended Next Build Decisions

These should be locked next:

1. final working name
2. Hebrew font or marker-art direction
3. whether Hebrew markers are letters, numeration-inspired markers, or a curated symbolic set
4. date default on or off
5. whether Arabic-Indic is included in first public release or very shortly after

---

## Recommended Immediate Action Plan

### Right now
1. Choose app working name: **Script Dial**
2. Choose implementation: **C**
3. Build analog skeleton for both platforms
4. Create first Hebrew marker set
5. Render first round of emulator screenshots

### Right after first render
6. Compare font-based vs image-based markers
7. Tune marker size and optical offsets
8. Decide whether date improves or harms the face
9. Add Arabic-Indic pack
10. Prepare store copy and screenshots

---

## Decision Summary

### Locked recommendations
- one configurable app
- Hebrew-first hero pack
- Arabic-Indic secondary pack
- C implementation
- no seconds in v1 default
- date optional
- black theme default
- focus only on Emery and Gabbro

### Open questions
- final app name
- marker rendering method: font vs images
- exact Hebrew marker style
- whether Persian is in v1 or v1.1

---

## Final Intent

This should become a Pebble watchface that people can understand in one glance:
- beautiful
- original
- culturally distinct
- technically polished
- obviously made with care

It should feel less like “a clever watchface idea” and more like “a real watch I wish existed.”

