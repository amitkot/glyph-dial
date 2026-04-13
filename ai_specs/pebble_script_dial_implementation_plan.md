# Glyph Dial Implementation Plan

## Scope

Build one configurable Pebble watchface in C that targets:
- `emery`
- `gabbro`

The product scope for v1 is:
- analog watchface only
- Hebrew hero pack
- Arabic-Indic secondary pack
- night and paper themes
- optional date
- no seconds by default

This plan follows the Pebble watchface skill's implementation constraints:
- build in C
- use `MINUTE_UNIT` updates
- validate on-device layouts with emulator screenshots
- develop for Emery and Gabbro from the start
- treat Emery as the visual reference layout during tuning

## Current Interpretation

These decisions appear stable enough to plan around:
- Working name: `Glyph Dial`
- App architecture: one app, multiple script packs
- Hebrew markers: `א ב ג ד ה ו ז ח ט י יא יב`
- Hebrew marker semantics: keep the exact sequence, allow visual tuning only
- Marker placement: programmatic polar anchors plus per-pack optical nudges
- Hands: custom-drawn baton hands
- Theme system: black default, white inverted
- Date behavior: configurable, but included in the first implementation pass
- Hebrew default date format: `12 Apr`
- Arabic-Indic default date format: Latin Gregorian date, matching the quiet `12 Apr` style in v1
- Platform scope: Emery and Gabbro both in the day-one release
- Platform workflow: both built in parallel, with Emery used as the reference when tradeoffs are needed
- Marker rendering bias: use image-based markers in v1 unless a font spike clearly outperforms them
- Release scope: first public submission includes both Hebrew and Arabic-Indic packs
- Stretch scope: additional packs may be added only if the two-pack release is already polished
- Contest-reference visual direction: sparse black dial, quiet centered date, contained Emery composition

## Open Product Questions

These are the main unresolved issues that will affect implementation details, asset production, and test criteria:

1. What is the rendering source for markers in v1?
   Working assumption is now:
   - image assets in v1

   Font-based markers remain a fallback only if they prove clearly better in practice.

2. What should the date format be in each pack?
   Working assumption is now:
   - Hebrew pack: `12 Apr`
   - Arabic-Indic pack: Latin Gregorian date in the same quiet style for v1

3. What counts as success for "wearable enough" versus "contest distinctive"?
   Working assumption is now:
   - marker legibility and typographic personality should be solved together through consistent shape language, sizing, and spacing
   - non-marker tradeoffs, such as hand thickness, may use a beautiful default and only gain a more legible variant if testing shows a real need

## Problem Areas To Resolve Early

### 1. Hebrew markers are defined, but two-character markers need deliberate tuning
The Hebrew pack is now defined as:
- `א ב ג ד ה ו ז ח ט י יא יב`

This resolves the semantic ambiguity, but `יא` and `יב` still create a practical spacing and balancing challenge.

Recommendation:
- keep the symbols fixed
- solve fit and beauty with per-marker nudges, scale, and tracking adjustments

### 2. Font vs image assets changes the entire resource pipeline
The plan now biases toward image assets for v1, but implementation structure still differs materially:
- image assets give better per-marker control and screenshot quality
- font glyphs scale better to future packs and reduce placement boilerplate

Recommendation:
- implement data structures that support either path
- proceed assuming image assets unless a font spike produces materially better fit, clarity, or resource behavior

### 3. Date may destabilize Emery composition
The proposed Emery center and date baseline are plausible, but the margin is not generous once unobstructed-area behavior is included.

Recommendation:
- treat date as a feature that must re-earn its place after first renders
- define an explicit fallback policy:
  - normal mode: show date if it clears the dial visually
  - obstructed mode: hide date first, shift dial only if still needed

### 4. Cross-pack date conventions are defined for v1
The date policy is now intentionally quiet across packs:
- Hebrew pack: `12 Apr`
- Arabic-Indic pack: Latin Gregorian date in the same style

Recommendation:
- keep the date visually secondary to the dial markers
- defer localized numeral/date experiments until after the base watchface is stable

### 5. "Multiple packs" can bloat early work
The plan is directionally right, but adding Arabic-Indic too early will slow the visual tuning loop.

Recommendation:
- finish one polished Hebrew path first, using Emery as the reference layout
- keep Gabbro in continuous validation while tuning the shared system
- add Arabic-Indic after the layout, hands, settings, and marker engine are stable, but before the first public submission
- do not add any third pack unless the two-pack release is already visually signed off

### 6. Legibility versus personality should mostly be resolved in the marker system itself
For this watchface, the primary reading is that marker beauty and readability should move together rather than compete.

Recommendation:
- enforce consistent marker drawing style within each pack
- keep marker sizing and visual weight coherent around the dial
- treat hand-weight adjustments as a separate concern
- use a beautiful hand style by default, with an optional higher-legibility hand variant only if emulator testing justifies it

## Proposed Technical Approach

## 1. Project structure

Create a structured C watchface project with:
- `src/c/main.c`
- `src/c/app_state.h`
- `src/c/app_state.c`
- `src/c/layout.h`
- `src/c/layout.c`
- `src/c/markers.h`
- `src/c/markers.c`
- `src/c/draw.h`
- `src/c/draw.c`
- `src/c/settings.h`
- `src/c/settings.c`
- `src/c/date_format.h`
- `src/c/date_format.c`
- `src/pkjs/index.js`
- `resources/`
- `resources/config/`

Reasoning:
- isolates geometry, rendering, marker data, and persisted settings
- keeps the font/image decision localized to marker modules
- avoids overloading `main.c`

## 2. Data model

Define the app around a few explicit structures:
- `ThemeSpec`
- `LayoutSpec`
- `MarkerSpec`
- `MarkerPack`
- `AppSettings`

The watchface should compute hour positions programmatically, then apply:
- per-platform layout values
- per-pack marker box sizes
- per-marker x/y optical nudges

## 3. Layout system

Implement two layout presets:
- `LAYOUT_EMERY`
- `LAYOUT_GABBRO`

Each layout preset should define:
- center point
- marker radius
- outer safe radius
- hand lengths and widths
- center cap radius
- date baseline or date frame
- unobstructed-area adjustment policy

Emery should be treated as the reference geometry, with Gabbro validated in parallel throughout implementation.

## 4. Rendering pipeline

Recommended render order:
1. background
2. hour markers
3. hour hand
4. minute hand
5. center cap
6. date

Practical rendering rules:
- subscribe with `MINUTE_UNIT`
- redraw only on minute change, settings change, and unobstructed-area events
- keep hands programmatic and simple
- avoid anti-aliasing assumptions that do not hold consistently across Pebble targets

## 5. Marker engine

Build the marker system so it can support both images and fonts behind one API.

Suggested interface:
- load current pack
- fetch 12 marker specs
- draw marker at hour index and anchor point

Each marker spec should support:
- resource id or glyph codepoint
- nominal box size
- per-platform offset
- optional alternate scale

## 6. Settings and configuration

Use Clay for a minimal settings page with:
- script pack
- theme
- date on/off

Defer anything else until v1 is visually complete.

Possible later setting, only if testing proves the need:
- hand style or hand weight variant

## Delivery Phases

## Phase 0: Product lock

Decisions to lock before coding beyond the skeleton:
- none beyond implementation details discovered during rendering spikes

Output:
- approved design brief
- approved implementation assumptions

## Phase 1: Skeleton app on Emery and Gabbro

Tasks:
- create Pebble C project metadata
- enable Emery and Gabbro targets from the start
- implement base window lifecycle
- subscribe to `MINUTE_UNIT`
- render black background
- draw placeholder hands only

Success criteria:
- emulator build runs cleanly on Emery and Gabbro
- minute updates are correct
- base redraw path is stable

## Phase 2: Core analog renderer

Tasks:
- add platform layout abstraction
- draw hour and minute hands
- draw center cap
- validate clearances against marker ring and date zone

Success criteria:
- analog face feels balanced before markers are added
- hand lengths do not crowd the planned marker ring

## Phase 3: Hebrew marker spike

Tasks:
- implement marker engine abstraction
- prototype Hebrew pack with first-pass markers
- test one rendering route first
- capture screenshots and review centering at all 12 positions

Success criteria:
- Hebrew dial is visually coherent on Emery
- weak positions are identified and corrected with optical nudges
- marker rendering method is locked

## Phase 4: Date and unobstructed-area behavior

Tasks:
- add date formatter
- add date placement and style
- add unobstructed-area callbacks on Emery
- hide or reflow date under obstruction

Success criteria:
- unobstructed-area behavior never causes cramped composition
- date can be disabled without breaking layout

## Phase 5: Settings and persistence

Tasks:
- add Clay config UI
- persist selected pack, theme, and date toggle
- trigger redraw on settings changes

Success criteria:
- configuration is minimal and reliable
- state survives app relaunches

## Phase 6: Arabic-Indic pack

Tasks:
- add second pack data
- tune marker scale and offsets independently
- decide date numeral behavior for this pack

Success criteria:
- Arabic-Indic pack feels intentionally designed, not mechanically swapped in
- first public submission includes both Hebrew and Arabic-Indic

## Phase 7: Gabbro refinement

Tasks:
- tune round layout constants
- retest marker spacing, hand lengths, and date placement

Success criteria:
- round composition feels native to the device
- no rectangular-layout artifacts remain

## Phase 8: Validation and release assets

Tasks:
- build PBW artifact
- run both targets in emulator
- capture final screenshots
- check theme, date, and pack combinations
- prepare store metadata draft

Success criteria:
- PBW builds cleanly
- screenshots are contest-quality
- v1 combinations are visually signed off

## Test Plan

Minimum validation matrix:
- Emery, night, Hebrew, date off
- Emery, night, Hebrew, date on
- Emery, paper, Hebrew, date on
- Emery, night, Arabic-Indic, date on
- Gabbro, night, Hebrew, date off
- Gabbro, night, Hebrew, date on
- Gabbro, paper, Arabic-Indic, date on

Functional checks:
- minute update rollover
- noon and midnight hand positions
- persisted settings
- unobstructed-area reaction on Emery
- no clipped markers
- no hand/marker collisions at dense angles

## Recommended Interview Questions For Next Pass

1. Should the first implementation lock onto Emery first for visual approval, then tune Gabbro immediately after?
2. What app name should we use for the first submission?

## Plan Status

This implementation plan is ready for architecture work, but it should be revised once the marker semantics and date policy are answered. Those two decisions are the main determinants of asset strategy, visual QA criteria, and schedule risk.
