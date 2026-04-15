#pragma once

#include <pebble.h>

typedef struct {
  GPoint center;
  uint16_t marker_radius;
  uint16_t marker_box;
  uint16_t hour_hand_length;
  uint16_t minute_hand_length;
  uint8_t hour_hand_width;
  uint8_t minute_hand_width;
  uint8_t center_radius;
} LayoutSpec;

const LayoutSpec *layout_get(bool obstructed);
