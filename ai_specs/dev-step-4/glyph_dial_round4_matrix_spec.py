#!/usr/bin/env python3
# Glyph Dial Round 4 matrix spec
#
# This file exists to give the coding agent a machine-readable source of truth.
# Update only if the design brief changes.

import json
from pathlib import Path

spec = {
  "fixed": {
    "font": "Noto Sans Hebrew Bold",
    "glyph_shapes": "unchanged",
    "hand_family": "tapered_baton",
    "seconds": false,
    "date": false,
    "background": "GColorBlack",
    "glyph_color": "GColorWhite",
    "minute_hand_color": "GColorWhite",
    "hub_fill_radius": 3,
    "hub_outline_width": 1
  },
  "measurements": {
    "emery": {
      "image_size": [
        200,
        228
      ],
      "content_bbox": [
        24,
        23,
        172,
        199
      ],
      "hub_center": [
        99,
        100
      ],
      "minute_tip": [
        63,
        130
      ],
      "hour_tip": [
        95,
        70
      ],
      "minute_radius": 46.86,
      "hour_radius": 30.27,
      "minute_tip_to_nearest_glyph_px": 19.0,
      "hour_tip_to_nearest_glyph_px": 37.0,
      "min_inner_glyph_radius": 60.42
    },
    "gabbro": {
      "image_size": [
        260,
        260
      ],
      "content_bbox": [
        30,
        31,
        225,
        229
      ],
      "hub_center": [
        131,
        126
      ],
      "minute_tip": [
        195,
        110
      ],
      "hour_tip": [
        134,
        88
      ],
      "minute_radius": 65.97,
      "hour_radius": 38.12,
      "minute_tip_to_nearest_glyph_px": 1.41,
      "hour_tip_to_nearest_glyph_px": 47.1,
      "min_inner_glyph_radius_excluding_date": 80.13
    }
  },
  "geometry_matrix": {
    "emery": [
      {
        "name": "E1",
        "center": [
          99,
          100
        ],
        "hour_length": 34,
        "minute_length": 54
      },
      {
        "name": "E2",
        "center": [
          99,
          100
        ],
        "hour_length": 36,
        "minute_length": 56
      },
      {
        "name": "E3",
        "center": [
          99,
          100
        ],
        "hour_length": 38,
        "minute_length": 58
      },
      {
        "name": "E4",
        "center": [
          99,
          102
        ],
        "hour_length": 34,
        "minute_length": 54
      },
      {
        "name": "E5",
        "center": [
          99,
          102
        ],
        "hour_length": 36,
        "minute_length": 56
      },
      {
        "name": "E6",
        "center": [
          99,
          102
        ],
        "hour_length": 38,
        "minute_length": 58
      }
    ],
    "gabbro": [
      {
        "name": "G1",
        "center": [
          131,
          126
        ],
        "hour_length": 40,
        "minute_length": 64
      },
      {
        "name": "G2",
        "center": [
          131,
          126
        ],
        "hour_length": 42,
        "minute_length": 66
      },
      {
        "name": "G3",
        "center": [
          131,
          126
        ],
        "hour_length": 44,
        "minute_length": 68
      },
      {
        "name": "G4",
        "center": [
          131,
          128
        ],
        "hour_length": 40,
        "minute_length": 64
      },
      {
        "name": "G5",
        "center": [
          131,
          128
        ],
        "hour_length": 42,
        "minute_length": 66
      },
      {
        "name": "G6",
        "center": [
          131,
          128
        ],
        "hour_length": 44,
        "minute_length": 68
      }
    ]
  },
  "color_matrix": [
    {
      "name": "C1_mono",
      "hour_hand": "GColorWhite",
      "minute_hand": "GColorWhite",
      "hub_outline": "GColorWhite"
    },
    {
      "name": "C2_brass",
      "hour_hand": "GColorBrass",
      "minute_hand": "GColorWhite",
      "hub_outline": "GColorBrass"
    },
    {
      "name": "C3_windsor",
      "hour_hand": "GColorWindsorTan",
      "minute_hand": "GColorWhite",
      "hub_outline": "GColorWindsorTan"
    }
  ],
  "outputs": [
    "round4_emery_geometry.png",
    "round4_gabbro_geometry.png",
    "round4_emery_color.png",
    "round4_gabbro_color.png",
    "round4_final_summary.png"
  ]
}

Path("glyph_dial_round4_matrix.json").write_text(
    json.dumps(spec, indent=2, ensure_ascii=False),
    encoding="utf-8",
)

print("Wrote glyph_dial_round4_matrix.json")
