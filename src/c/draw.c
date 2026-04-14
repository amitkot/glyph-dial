#include "draw.h"

#include "date_format.h"

static GPoint point_from_angle(GPoint center, uint16_t radius, int32_t angle) {
  return GPoint(
      center.x + (int16_t)(sin_lookup(angle) * (int32_t)radius / TRIG_MAX_RATIO),
      center.y - (int16_t)(cos_lookup(angle) * (int32_t)radius / TRIG_MAX_RATIO));
}

ThemeSpec draw_theme_spec(ThemeMode theme) {
  if (theme == THEME_PAPER) {
    return (ThemeSpec){
      .background = GColorWhite,
      .foreground = GColorBlack,
      .accent = GColorWhite,
    };
  }

  return (ThemeSpec){
    .background = GColorBlack,
    .foreground = GColorWhite,
    .accent = GColorBlack,
  };
}

static void draw_marker_ring(GContext *ctx,
                             const LayoutSpec *layout,
                             const MarkerPack *marker_pack,
                             GBitmap *const *bitmaps,
                             ThemeSpec theme) {
  for (int i = 0; i < MARKER_COUNT; ++i) {
    int hour = i + 1;
    int32_t angle = TRIG_MAX_ANGLE * hour / 12;
    GPoint anchor = point_from_angle(layout->center, layout->marker_radius, angle);

#ifdef PBL_ROUND
    const int16_t dx = marker_pack->markers[i].dx_round;
    const int16_t dy = marker_pack->markers[i].dy_round;
#else
    const int16_t dx = marker_pack->markers[i].dx_rect;
    const int16_t dy = marker_pack->markers[i].dy_rect;
#endif

    GRect bitmap_bounds = gbitmap_get_bounds(bitmaps[i]);
    GRect frame = GRect(anchor.x - bitmap_bounds.size.w / 2 + dx,
                        anchor.y - bitmap_bounds.size.h / 2 + dy, bitmap_bounds.size.w,
                        bitmap_bounds.size.h);

    graphics_context_set_compositing_mode(
        ctx, theme.foreground.argb == GColorWhite.argb ? GCompOpAssign : GCompOpAssignInverted);
    graphics_draw_bitmap_in_rect(ctx, bitmaps[i], frame);
  }
}

static void draw_hand_polygon(GContext *ctx,
                              GPoint center,
                              int32_t angle,
                              uint16_t length,
                              uint8_t base_half_width,
                              uint8_t neck_half_width,
                              uint8_t tail_length,
                              GColor fill_color) {
  GPoint points[] = {
      GPoint(-base_half_width, tail_length),
      GPoint(-neck_half_width, -length / 3),
      GPoint(0, -(int16_t)length),
      GPoint(neck_half_width, -length / 3),
      GPoint(base_half_width, tail_length),
  };

  GPathInfo info = {
      .num_points = ARRAY_LENGTH(points),
      .points = points,
  };
  GPath *path = gpath_create(&info);
  gpath_rotate_to(path, angle);
  gpath_move_to(path, center);

  graphics_context_set_fill_color(ctx, fill_color);
  gpath_draw_filled(ctx, path);
  gpath_destroy(path);
}

static void draw_hands(GContext *ctx, const LayoutSpec *layout, const struct tm *tick_time, ThemeSpec theme) {
  const int32_t minute_angle = TRIG_MAX_ANGLE * tick_time->tm_min / 60;
  const int32_t hour_angle =
      TRIG_MAX_ANGLE * (((tick_time->tm_hour % 12) * 60) + tick_time->tm_min) / (12 * 60);
  const uint8_t hour_neck_half_width =
      layout->hour_hand_width > 3 ? (uint8_t)(layout->hour_hand_width - 2) : 2;
  const uint8_t minute_neck_half_width =
      layout->minute_hand_width > 1 ? (uint8_t)(layout->minute_hand_width - 1) : 1;

  draw_hand_polygon(ctx, layout->center, hour_angle, layout->hour_hand_length, layout->hour_hand_width,
                    hour_neck_half_width, 4, theme.foreground);
  draw_hand_polygon(ctx, layout->center, minute_angle, layout->minute_hand_length,
                    layout->minute_hand_width, minute_neck_half_width, 5,
                    theme.foreground);

  graphics_context_set_fill_color(ctx, theme.foreground);
  graphics_fill_circle(ctx, layout->center, layout->center_radius - 1);
  graphics_context_set_stroke_color(ctx, theme.background);
  graphics_context_set_stroke_width(ctx, 1);
  graphics_draw_circle(ctx, layout->center, layout->center_radius);
  graphics_context_set_stroke_color(ctx, theme.foreground);
  graphics_draw_circle(ctx, layout->center, layout->center_radius + 1);
}

static void draw_date(GContext *ctx,
                      Layer *layer,
                      const LayoutSpec *layout,
                      const struct tm *tick_time,
                      ThemeSpec theme,
                      bool show_date) {
  if (!show_date) {
    return;
  }

  char buffer[16];
  date_format_day_month(tick_time, buffer, sizeof(buffer));

  graphics_context_set_text_color(ctx, theme.foreground);
  graphics_draw_text(ctx, buffer, fonts_get_system_font(layout->date_font_key), layout->date_frame,
                     GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, NULL);
  (void)layer;
}

void draw_face(Layer *layer,
               GContext *ctx,
               const struct tm *tick_time,
               const LayoutSpec *layout,
               const AppSettings *settings,
               const MarkerPack *marker_pack,
               GBitmap *const *bitmaps,
               bool obstructed) {
  ThemeSpec theme = draw_theme_spec(settings->theme);
  graphics_context_set_fill_color(ctx, theme.background);
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);

  draw_marker_ring(ctx, layout, marker_pack, bitmaps, theme);
  draw_hands(ctx, layout, tick_time, theme);
  draw_date(ctx, layer, layout, tick_time, theme, settings->show_date && !obstructed);
}
