#include "settings.h"

enum {
  PERSIST_KEY_SETTINGS = 1,
};

void settings_init_defaults(AppSettings *settings) {
  settings->pack = SCRIPT_PACK_HEBREW;
  settings->theme = THEME_NIGHT;
  settings->show_date = true;
}

void settings_load(AppSettings *settings) {
  settings_init_defaults(settings);
  if (persist_exists(PERSIST_KEY_SETTINGS)) {
    persist_read_data(PERSIST_KEY_SETTINGS, settings, sizeof(*settings));
  }

  if (settings->pack >= SCRIPT_PACK_COUNT) {
    settings->pack = SCRIPT_PACK_HEBREW;
  }
  if (settings->theme >= THEME_COUNT) {
    settings->theme = THEME_NIGHT;
  }
}

void settings_save(const AppSettings *settings) {
  persist_write_data(PERSIST_KEY_SETTINGS, settings, sizeof(*settings));
}
