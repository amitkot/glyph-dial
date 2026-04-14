#include "markers.h"

static const MarkerPack s_hebrew_pack = {
  .id = SCRIPT_PACK_HEBREW,
  .name = "Hebrew",
  .labels = {"א", "ב", "ג", "ד", "ה", "ו", "ז", "ח", "ט", "י", "יא", "יב"},
  .markers = {
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_01,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_01,
#endif
      0, 0, 0, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_02,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_02,
#endif
      0, -1, 0, -1},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_03,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_03,
#endif
      0, 0, 0, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_04,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_04,
#endif
      1, 0, 1, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_05,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_05,
#endif
      0, 1, 0, 2},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_06,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_06,
#endif
      0, -1, 0, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_07,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_07,
#endif
      -1, 1, -1, 2},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_08,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_08,
#endif
      -1, 1, -1, 1},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_09,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_09,
#endif
      -1, 0, -1, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_10,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_10,
#endif
      -1, -1, -1, -1},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_11,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_11,
#endif
      -1, -1, -1, -2},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_12,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_12,
#endif
      1, -1, 1, -2},
  },
};

static const MarkerPack s_arabic_indic_pack = {
  .id = SCRIPT_PACK_ARABIC_INDIC,
  .name = "Arabic-Indic",
  .labels = {"١", "٢", "٣", "٤", "٥", "٦", "٧", "٨", "٩", "١٠", "١١", "١٢"},
  .markers = {
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_ARABIC_INDIC_GABBRO_01,
#else
      RESOURCE_ID_IMG_ARABIC_INDIC_EMERY_01,
#endif
      0, 0, 0, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_ARABIC_INDIC_GABBRO_02,
#else
      RESOURCE_ID_IMG_ARABIC_INDIC_EMERY_02,
#endif
      0, 0, 0, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_ARABIC_INDIC_GABBRO_03,
#else
      RESOURCE_ID_IMG_ARABIC_INDIC_EMERY_03,
#endif
      0, 0, 0, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_ARABIC_INDIC_GABBRO_04,
#else
      RESOURCE_ID_IMG_ARABIC_INDIC_EMERY_04,
#endif
      0, 0, 0, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_ARABIC_INDIC_GABBRO_05,
#else
      RESOURCE_ID_IMG_ARABIC_INDIC_EMERY_05,
#endif
      0, 1, 0, 1},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_ARABIC_INDIC_GABBRO_06,
#else
      RESOURCE_ID_IMG_ARABIC_INDIC_EMERY_06,
#endif
      0, 0, 0, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_ARABIC_INDIC_GABBRO_07,
#else
      RESOURCE_ID_IMG_ARABIC_INDIC_EMERY_07,
#endif
      0, 1, 0, 1},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_ARABIC_INDIC_GABBRO_08,
#else
      RESOURCE_ID_IMG_ARABIC_INDIC_EMERY_08,
#endif
      0, 0, 0, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_ARABIC_INDIC_GABBRO_09,
#else
      RESOURCE_ID_IMG_ARABIC_INDIC_EMERY_09,
#endif
      -1, 0, -1, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_ARABIC_INDIC_GABBRO_10,
#else
      RESOURCE_ID_IMG_ARABIC_INDIC_EMERY_10,
#endif
      -1, -1, -1, -1},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_ARABIC_INDIC_GABBRO_11,
#else
      RESOURCE_ID_IMG_ARABIC_INDIC_EMERY_11,
#endif
      0, -1, 0, -1},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_ARABIC_INDIC_GABBRO_12,
#else
      RESOURCE_ID_IMG_ARABIC_INDIC_EMERY_12,
#endif
      0, -1, 0, -1},
  },
};

const MarkerPack *markers_get_pack(ScriptPack pack) {
  switch (pack) {
    case SCRIPT_PACK_ARABIC_INDIC:
      return &s_arabic_indic_pack;
    case SCRIPT_PACK_HEBREW:
    default:
      return &s_hebrew_pack;
  }
}

bool markers_validate_pack(const MarkerPack *pack) {
  if (!pack) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Marker pack is null");
    return false;
  }

  for (int i = 0; i < MARKER_COUNT; ++i) {
    if (!pack->labels[i] || !pack->labels[i][0]) {
      APP_LOG(APP_LOG_LEVEL_ERROR, "Marker pack %s missing label at %d", pack->name, i);
      return false;
    }
    if (pack->markers[i].resource_id == 0) {
      APP_LOG(APP_LOG_LEVEL_ERROR, "Marker pack %s missing resource at %d", pack->name, i);
      return false;
    }
  }

  return true;
}
