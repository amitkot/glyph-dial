#include "layout.h"

#ifdef PBL_ROUND
static const LayoutSpec s_layout_normal = {
  .center = {130, 130},
  .marker_radius = 90,
  .marker_box = 28,
  .hour_hand_length = 56,
  .minute_hand_length = 82,
  .hour_hand_width = 6,
  .minute_hand_width = 4,
  .center_radius = 7,
  .date_frame = {{75, 186}, {110, 26}},
  .date_font_key = FONT_KEY_GOTHIC_24_BOLD,
};

const LayoutSpec *layout_get(bool obstructed) {
  (void)obstructed;
  return &s_layout_normal;
}
#else
static const LayoutSpec s_layout_normal = {
  .center = {100, 100},
  .marker_radius = 64,
  .marker_box = 23,
  .hour_hand_length = 44,
  .minute_hand_length = 61,
  .hour_hand_width = 5,
  .minute_hand_width = 3,
  .center_radius = 6,
  .date_frame = {{50, 150}, {100, 22}},
  .date_font_key = FONT_KEY_GOTHIC_18_BOLD,
};

static const LayoutSpec s_layout_obstructed = {
  .center = {100, 96},
  .marker_radius = 61,
  .marker_box = 22,
  .hour_hand_length = 40,
  .minute_hand_length = 58,
  .hour_hand_width = 5,
  .minute_hand_width = 3,
  .center_radius = 6,
  .date_frame = {{50, 143}, {100, 22}},
  .date_font_key = FONT_KEY_GOTHIC_18_BOLD,
};

const LayoutSpec *layout_get(bool obstructed) {
  return obstructed ? &s_layout_obstructed : &s_layout_normal;
}
#endif
