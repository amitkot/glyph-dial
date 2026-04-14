#include <pebble.h>

#include "draw.h"
#include "layout.h"
#include "markers.h"
#include "settings.h"

typedef struct {
  Window *window;
  Layer *canvas_layer;
  AppSettings settings;
  struct tm current_time;
  GBitmap *marker_bitmaps[12];
  ScriptPack loaded_pack;
  bool obstructed;
  bool first_frame_logged;
} AppState;

static AppState s_app;

static void unload_marker_bitmaps(void) {
  for (int i = 0; i < 12; ++i) {
    if (s_app.marker_bitmaps[i]) {
      gbitmap_destroy(s_app.marker_bitmaps[i]);
      s_app.marker_bitmaps[i] = NULL;
    }
  }
}

static void load_marker_bitmaps(ScriptPack pack) {
  unload_marker_bitmaps();
  const MarkerPack *marker_pack = markers_get_pack(pack);
  if (!markers_validate_pack(marker_pack)) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Marker pack validation failed for %d", (int)pack);
    return;
  }
  for (int i = 0; i < MARKER_COUNT; ++i) {
    s_app.marker_bitmaps[i] = gbitmap_create_with_resource(marker_pack->markers[i].resource_id);
  }
  s_app.loaded_pack = pack;
}

static void update_time(void) {
  time_t now = time(NULL);
  struct tm *local = localtime(&now);
  if (local) {
    s_app.current_time = *local;
  }
}

static void inbox_received_handler(DictionaryIterator *iter, void *context) {
  (void)context;

  bool should_save = false;
  bool should_reload_markers = false;

  Tuple *pack = dict_find(iter, MESSAGE_KEY_PACK);
  if (pack) {
    int32_t next_pack = pack->value->int32;
    if (next_pack >= 0 && next_pack < SCRIPT_PACK_COUNT && next_pack != s_app.settings.pack) {
      s_app.settings.pack = (ScriptPack)next_pack;
      should_save = true;
      should_reload_markers = true;
    }
  }

  Tuple *theme = dict_find(iter, MESSAGE_KEY_THEME);
  if (theme) {
    int32_t next_theme = theme->value->int32;
    if (next_theme >= 0 && next_theme < THEME_COUNT && next_theme != s_app.settings.theme) {
      s_app.settings.theme = (ThemeMode)next_theme;
      should_save = true;
    }
  }

  Tuple *show_date = dict_find(iter, MESSAGE_KEY_SHOW_DATE);
  if (show_date) {
    bool next_show_date = show_date->value->int32 == 1;
    if (next_show_date != s_app.settings.show_date) {
      s_app.settings.show_date = next_show_date;
      should_save = true;
    }
  }

  if (should_save) {
    settings_save(&s_app.settings);
  }
  if (should_reload_markers) {
    load_marker_bitmaps(s_app.settings.pack);
  }

  layer_mark_dirty(s_app.canvas_layer);
}

static void unobstructed_change_handler(AnimationProgress progress, void *context) {
  (void)progress;
  (void)context;
#ifdef PBL_RECT
  Layer *root = window_get_root_layer(s_app.window);
  GRect full_bounds = layer_get_bounds(root);
  GRect unobstructed_bounds = layer_get_unobstructed_bounds(root);
  s_app.obstructed = unobstructed_bounds.size.h < full_bounds.size.h;
#else
  s_app.obstructed = false;
#endif
  layer_mark_dirty(s_app.canvas_layer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  (void)units_changed;
  s_app.current_time = *tick_time;
  layer_mark_dirty(s_app.canvas_layer);
}

static void canvas_update_proc(Layer *layer, GContext *ctx) {
  const LayoutSpec *layout = layout_get(s_app.obstructed);
  const MarkerPack *marker_pack = markers_get_pack(s_app.settings.pack);
  draw_face(layer, ctx, &s_app.current_time, layout, &s_app.settings, marker_pack, s_app.marker_bitmaps,
            s_app.obstructed);

  if (!s_app.first_frame_logged) {
    APP_LOG(APP_LOG_LEVEL_INFO, "GLYPH_DIAL_FRAME_READY");
    s_app.first_frame_logged = true;
  }
}

static void window_load(Window *window) {
  Layer *root = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(root);

  s_app.canvas_layer = layer_create(bounds);
  layer_set_update_proc(s_app.canvas_layer, canvas_update_proc);
  layer_add_child(root, s_app.canvas_layer);

  unobstructed_change_handler(ANIMATION_NORMALIZED_MAX, NULL);
}

static void window_unload(Window *window) {
  (void)window;
  layer_destroy(s_app.canvas_layer);
  s_app.canvas_layer = NULL;
}

static void init(void) {
  settings_load(&s_app.settings);
  update_time();
  load_marker_bitmaps(s_app.settings.pack);
  s_app.first_frame_logged = false;

  s_app.window = window_create();
  window_set_background_color(s_app.window, GColorBlack);
  window_set_window_handlers(s_app.window, (WindowHandlers){
    .load = window_load,
    .unload = window_unload,
  });

  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  unobstructed_area_service_subscribe((UnobstructedAreaHandlers){
                                        .change = unobstructed_change_handler,
                                        .did_change = NULL,
                                        .will_change = NULL,
                                      },
                                      NULL);
  app_message_register_inbox_received(inbox_received_handler);
  app_message_open(128, 128);

  window_stack_push(s_app.window, true);
}

static void deinit(void) {
  app_message_deregister_callbacks();
  unobstructed_area_service_unsubscribe();
  tick_timer_service_unsubscribe();
  unload_marker_bitmaps();
  window_destroy(s_app.window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
