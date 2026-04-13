# Pebble Spring 2026 Contest Details

Last verified: 2026-04-13

## Purpose
This document captures the official contest details, appstore submission requirements, and platform constraints that are directly relevant to the Script Dial watchface project.

## Contest Summary
- Contest name: **Spring 2026 Pebble App Contest**
- Contest announced: **April 2, 2026**
- Contest window: **April 2 to April 19, 2026 UTC**
- Eligible entries include both **apps and watchfaces**
- The contest is meant to celebrate new work for **Pebble Time 2** and **Pebble Round 2**

## How Developers Enter
There are two main developer entry paths:
1. **Import or claim** pre-2025 apps
2. **Publish a new app** for Time 2 and/or Round 2

For this project, the relevant path is:
- publish a **new watchface**
- created date must be **April 2, 2026 or later** for the main contest buckets that depend on newly published apps

## Prize Structure
There are **4 ways to win**:

### 1. Developer Draw
- **10 watch prizes**
- Claiming/importing pre-2025 apps gives **one draw entry**
- Publishing a new app created on or after **April 2, 2026** gives **one draw entry**
- Each developer can have **up to 2 entries** in the draw

### 2. Most Hearts
- **10 watch prizes**
- Only applies to **new apps** created on or after **April 2, 2026**
- Split into **two phases** to reduce the advantage of early submissions:
  - **5 watches** for the top 5 hearted apps created between **April 2 and April 12**
  - **5 watches** for the top 5 hearted apps created between **April 13 and April 20**

### 3. Pebble Team Judging
- **3 transparent Time 2 watches**
- Any app created since **January 1, 2026** is automatically entered
- Judging criteria:
  - **creativity**
  - **cleverness**
  - **good use of new platforms**
  - **design**

### 4. Heart an App Draw
- **2 watch prizes**
- Anyone who hearts an eligible app is entered into a separate draw

## Important Contest Rules
- Contest runs until **April 19, 2026 UTC**
- Results will be prepared **a few days after April 19**
- Fake, low-value, scam, trivial, or system-gaming submissions may be removed
- Republished old apps with no meaningful change may be removed
- Winners can choose **Time 2 or Round 2**

## SDK and Publishing Notes Relevant to This Project
The contest announcement also highlights several platform updates:
- SDK release mentioned: **Pebble SDK 4.9.148**
- CLI publishing is supported via **`pebble publish`**
- CloudPebble publishing is supported
- Publishing flow can generate and upload **screenshots and GIFs**
- Watchfaces should support **Quick View** where relevant
- Alloy is now out of developer preview, but many C APIs are still not yet available in Alloy

## Appstore Submission Requirements
A Pebble appstore listing requires:

### Basic Info
- app title
- website URL
- source code URL
- support email address
- category
- icons

### Asset Collection Per Supported Platform
An **asset collection** must be created for **each supported platform**.
For each platform collection, prepare:
- **description**
  - maximum **1600 characters**
- **screenshots**
  - maximum **5 per platform**
  - accepted formats: **PNG, GIF, Animated GIF**
- **marketing banner**
  - optional but useful for featured/promotional placement

### Releases
- At least one valid **`.pbw`** release build must be uploaded
- Release must have:
  - a valid UUID
  - a version greater than previously published versions

### Promotion
The official publishing guide explicitly recommends promotion on community channels such as:
- Discord
- Reddit
- Bluesky
- Mastodon

## Platform Constraints for This Project
This project is intentionally targeting only the new platforms:

### Emery
- Product: **Pebble Time 2**
- Display resolution: **200 × 228**
- Display shape: **rectangle**
- Display colors: **2-color (black/white)**

### Gabbro
- Product: **Pebble Round 2**
- Display resolution: **260 × 260**
- Display shape: **round**
- Display colors: **2-color (black/white)**

### Shared Limits Relevant to Emery and Gabbro
- **Max resource size:** **256k**
- **Max app size (code + heap):** **128k**

## What This Means for Script Dial
These official rules imply the following product decisions:
- We should support **Emery and Gabbro only** in v1
- We should optimize strongly for **judge criteria**:
  - originality
  - polish
  - platform-aware design
- We should also optimize for **hearts** with strong screenshots and a clear visual concept
- We should prepare **separate asset collections** for Emery and Gabbro
- We should capture **real watchface screenshots** for the store listing
- We should support **Quick View-aware layout behavior** on Emery
- We should prefer a conservative implementation path for a contest timeline

## Practical Submission Checklist
- [ ] Final app name selected
- [ ] UUID assigned
- [ ] Emery support confirmed
- [ ] Gabbro support confirmed
- [ ] Release `.pbw` built
- [ ] Basic info completed
- [ ] Icons prepared
- [ ] Emery description written
- [ ] Gabbro description written
- [ ] Emery screenshots captured
- [ ] Gabbro screenshots captured
- [ ] Optional marketing banner prepared
- [ ] Public publish flow tested
- [ ] Promotion copy drafted
- [ ] Contest submission timing chosen

## Recommended Positioning for This Project
To align with the contest structure, the best positioning is:
- **a refined typographic analog watchface**
- **Hebrew-led hero design**
- **Arabic-Indic as a secondary pack**
- **designed specifically for Time 2 and Round 2**
- **visually elegant enough to earn hearts**
- **distinctive enough to interest the Pebble judging team**

## Source Notes
This document was extracted from the official rePebble contest announcement and official Pebble/Rebble developer documentation covering publishing and hardware constraints.
