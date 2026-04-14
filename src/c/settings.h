#pragma once

#include <pebble.h>

typedef enum {
  SCRIPT_PACK_HEBREW = 0,
  SCRIPT_PACK_ARABIC_INDIC = 1,
  SCRIPT_PACK_COUNT = 2,
} ScriptPack;

typedef enum {
  THEME_NIGHT = 0,
  THEME_PAPER = 1,
  THEME_COUNT = 2,
} ThemeMode;

typedef struct {
  ScriptPack pack;
  ThemeMode theme;
  bool show_date;
} AppSettings;

void settings_init_defaults(AppSettings *settings);
void settings_load(AppSettings *settings);
void settings_save(const AppSettings *settings);
