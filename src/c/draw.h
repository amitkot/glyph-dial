#pragma once

#include <pebble.h>

#include "layout.h"
#include "markers.h"
#include "settings.h"

typedef struct {
  GColor background;
  GColor foreground;
  GColor accent;
} ThemeSpec;

ThemeSpec draw_theme_spec(ThemeMode theme);
void draw_face(Layer *layer,
               GContext *ctx,
               const struct tm *tick_time,
               const LayoutSpec *layout,
               const AppSettings *settings,
               const MarkerPack *marker_pack,
               GBitmap *const *bitmaps,
               bool obstructed);
