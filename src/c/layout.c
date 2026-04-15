#include "layout.h"

#include "round3_config.h"

#ifdef PBL_ROUND
static const LayoutSpec s_layout_normal = {
  .center = {GLYPH_GABBRO_CENTER_X, GLYPH_GABBRO_CENTER_Y},
  .marker_radius = GLYPH_GABBRO_MARKER_RADIUS,
  .marker_box = 28,
  .hour_hand_length = GLYPH_GABBRO_HOUR_LEN,
  .minute_hand_length = GLYPH_GABBRO_MINUTE_LEN,
  .hour_hand_width = 6,
  .minute_hand_width = 4,
  .center_radius = 5,
  .date_frame = {{88, GLYPH_GABBRO_DATE_Y}, {84, 16}},
  .date_font_key = FONT_KEY_GOTHIC_14,
};

const LayoutSpec *layout_get(bool obstructed) {
  (void)obstructed;
  return &s_layout_normal;
}
#else
static const LayoutSpec s_layout_normal = {
  .center = {GLYPH_EMERY_CENTER_X, GLYPH_EMERY_CENTER_Y},
  .marker_radius = GLYPH_EMERY_MARKER_RADIUS,
  .marker_box = 23,
  .hour_hand_length = GLYPH_EMERY_HOUR_LEN,
  .minute_hand_length = GLYPH_EMERY_MINUTE_LEN,
  .hour_hand_width = 5,
  .minute_hand_width = 3,
  .center_radius = 5,
  .date_frame = {{66, GLYPH_EMERY_DATE_Y}, {68, 12}},
  .date_font_key = FONT_KEY_GOTHIC_14,
};

static const LayoutSpec s_layout_obstructed = {
  .center = {GLYPH_EMERY_OBS_CENTER_X, GLYPH_EMERY_OBS_CENTER_Y},
  .marker_radius = GLYPH_EMERY_OBS_MARKER_RADIUS,
  .marker_box = 22,
  .hour_hand_length = GLYPH_EMERY_OBS_HOUR_LEN,
  .minute_hand_length = GLYPH_EMERY_OBS_MINUTE_LEN,
  .hour_hand_width = 5,
  .minute_hand_width = 3,
  .center_radius = 5,
  .date_frame = {{66, GLYPH_EMERY_OBS_DATE_Y}, {68, 12}},
  .date_font_key = FONT_KEY_GOTHIC_14,
};

const LayoutSpec *layout_get(bool obstructed) {
  return obstructed ? &s_layout_obstructed : &s_layout_normal;
}
#endif
