# Glyph Dial Round-3 Comparison Matrix

This file defines the exact screenshot matrix the coding agent should generate.

## Fixed items for all matrix shots

Unless the matrix row explicitly changes them, keep these fixed:
- font: `Noto Sans Hebrew Bold`
- glyph shapes: unchanged
- hand family: tapered baton
- seconds: off
- glyph color: white
- date color: white
- minute hand color: white
- background: black

---

## Matrix A — monochrome geometry lock

### Emery
Create these shots:

1. `emery_A1`
   - pivot `(99,101)`
   - date `off`
   - hand lengths `hour=30 minute=46`
   - hub `fill4_outline1`

2. `emery_A2`
   - pivot `(99,101)`
   - date `off`
   - hand lengths `hour=30 minute=42`
   - hub `fill4_outline1`

3. `emery_A3`
   - pivot `(99,103)`
   - date `off`
   - hand lengths `hour=32 minute=44`
   - hub `fill3_outline1`

4. `emery_A4`
   - pivot `(99,103)`
   - date `off`
   - hand lengths `hour=30 minute=42`
   - hub `fill3_no_outline`

### Gabbro
Create these shots:

5. `gabbro_A1`
   - pivot `(130,126)`
   - date `off`
   - hand lengths `hour=40 minute=67`
   - hub `fill4_outline1`

6. `gabbro_A2`
   - pivot `(130,126)`
   - date `off`
   - hand lengths `hour=40 minute=63`
   - hub `fill4_outline1`

7. `gabbro_A3`
   - pivot `(130,128)`
   - date `off`
   - hand lengths `hour=42 minute=65`
   - hub `fill3_outline1`

8. `gabbro_A4`
   - pivot `(130,128)`
   - date `off`
   - hand lengths `hour=40 minute=63`
   - hub `fill3_no_outline`

Choose one winner per platform.

---

## Matrix B — date placement

Use the winning geometry from Matrix A.

### Emery date comparison
Create:

1. `emery_B0`
   - date `off`

2. `emery_B1`
   - date `on`
   - text top y `184`

3. `emery_B2`
   - date `on`
   - text top y `188`

4. `emery_B3`
   - date `on`
   - text top y `192`

### Gabbro date comparison
Create:

5. `gabbro_B0`
   - date `off`

6. `gabbro_B1`
   - date `on`
   - text top y `189`

7. `gabbro_B2`
   - date `on`
   - text top y `193`

8. `gabbro_B3`
   - date `on`
   - text top y `197`

Choose:
- one hero mode per platform: almost certainly `date off`
- one product date position per platform

---

## Matrix C — accent comparison

Use the winning geometry from Matrix A and the winning product date position from Matrix B.

Accent applies to:
- hour hand only
- optional hub outline only

Create for each platform:

1. `mono`
   - hour hand `GColorWhite`

2. `gold_brass`
   - hour hand `GColorBrass`

3. `gold_windsor`
   - hour hand `GColorWindsorTan`

4. `red_dark_candy`
   - hour hand `GColorDarkCandyAppleRed`

5. `red_bulgarian_rose`
   - hour hand `GColorBulgarianRose`

If no accent clearly improves the design, lock `mono`.

---

## Matrix D — optional micro-offset comparison

Only run this if, after Matrices A to C, the glyph ring still looks slightly tense.

### Offset set current
- no change

### Offset set B — Emery
- 10 `(-1,-1)`
- 11 `(-1,-1)`
- 12 `(0,-1)`
- 1 `(1,-1)`
- 5 `(1,0)`
- 6 `(0,1)`
- 7 `(-1,0)`

### Offset set B — Gabbro
- 10 `(-1,-1)`
- 11 `(-1,-2)`
- 12 `(0,-2)`
- 1 `(1,-1)`
- 5 `(1,1)`
- 6 `(0,1)`
- 7 `(-1,1)`

Create:
- current offsets
- offset set B

Choose only if visibly better.

---

## Settings implementation target after matrix selection

### Expose now
- `Show date` toggle
- `Theme` selector (`Night`, `Paper` only if approved)

### Do not expose yet
- accent color
- seconds
- script pack until at least two polished packs exist

---

## Naming convention for output files

Use filenames like:

- `emery_A1.png`
- `emery_B2.png`
- `gabbro_C_gold_brass.png`
- `gabbro_D_offsetsB.png`

Also generate one contact sheet per matrix:
- `matrix_A_geometry.png`
- `matrix_B_date.png`
- `matrix_C_color.png`
- `matrix_D_offsets.png`
