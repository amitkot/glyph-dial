#pragma once

#include <pebble.h>
#include "settings.h"

typedef struct {
  uint32_t resource_id;
  int8_t dx_rect;
  int8_t dy_rect;
  int8_t dx_round;
  int8_t dy_round;
} MarkerSpec;

const MarkerSpec *markers_get_specs(ScriptPack pack);
