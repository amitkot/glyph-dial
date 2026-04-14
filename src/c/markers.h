#pragma once

#include <pebble.h>
#include "settings.h"

#define MARKER_COUNT 12

typedef struct {
  uint32_t resource_id;
  int8_t dx_rect;
  int8_t dy_rect;
  int8_t dx_round;
  int8_t dy_round;
} MarkerSpec;

typedef struct {
  ScriptPack id;
  const char *name;
  const char *labels[MARKER_COUNT];
  MarkerSpec markers[MARKER_COUNT];
} MarkerPack;

const MarkerPack *markers_get_pack(ScriptPack pack);
bool markers_validate_pack(const MarkerPack *pack);
