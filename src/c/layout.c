#include "layout.h"

#ifdef PBL_ROUND
static const LayoutSpec s_layout_normal = {
  .center = {130, 130},
  .marker_radius = 93,
  .marker_box = 28,
  .hour_hand_length = 50,
  .minute_hand_length = 76,
  .hour_hand_width = 7,
  .minute_hand_width = 4,
  .center_radius = 5,
  .date_frame = {{88, 184}, {84, 16}},
  .date_font_key = FONT_KEY_GOTHIC_14,
};

const LayoutSpec *layout_get(bool obstructed) {
  (void)obstructed;
  return &s_layout_normal;
}
#else
static const LayoutSpec s_layout_normal = {
  .center = {100, 97},
  .marker_radius = 69,
  .marker_box = 23,
  .hour_hand_length = 39,
  .minute_hand_length = 55,
  .hour_hand_width = 6,
  .minute_hand_width = 3,
  .center_radius = 5,
  .date_frame = {{66, 184}, {68, 12}},
  .date_font_key = FONT_KEY_GOTHIC_14,
};

static const LayoutSpec s_layout_obstructed = {
  .center = {100, 93},
  .marker_radius = 65,
  .marker_box = 22,
  .hour_hand_length = 36,
  .minute_hand_length = 52,
  .hour_hand_width = 6,
  .minute_hand_width = 3,
  .center_radius = 5,
  .date_frame = {{66, 170}, {68, 12}},
  .date_font_key = FONT_KEY_GOTHIC_14,
};

const LayoutSpec *layout_get(bool obstructed) {
  return obstructed ? &s_layout_obstructed : &s_layout_normal;
}
#endif
