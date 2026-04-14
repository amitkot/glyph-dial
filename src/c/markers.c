#include "markers.h"

static const MarkerSpec s_hebrew_specs[12] = {
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
      0, 0, 0, 0},
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
      0, 0, 0, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_05,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_05,
#endif
      0, 0, 0, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_06,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_06,
#endif
      0, 0, 0, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_07,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_07,
#endif
      0, 0, 0, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_08,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_08,
#endif
      0, 0, 0, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_09,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_09,
#endif
      0, 0, 0, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_10,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_10,
#endif
      0, 0, 0, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_11,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_11,
#endif
      0, -1, 0, -1},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_HEBREW_GABBRO_12,
#else
      RESOURCE_ID_IMG_HEBREW_EMERY_12,
#endif
      0, -1, 0, -1},
};

static const MarkerSpec s_arabic_indic_specs[12] = {
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
      0, 0, 0, 0},
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
      0, 0, 0, 0},
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
      0, 0, 0, 0},
  {
#ifdef PBL_ROUND
      RESOURCE_ID_IMG_ARABIC_INDIC_GABBRO_10,
#else
      RESOURCE_ID_IMG_ARABIC_INDIC_EMERY_10,
#endif
      0, -1, 0, -1},
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
};

const MarkerSpec *markers_get_specs(ScriptPack pack) {
  switch (pack) {
    case SCRIPT_PACK_ARABIC_INDIC:
      return s_arabic_indic_specs;
    case SCRIPT_PACK_HEBREW:
    default:
      return s_hebrew_specs;
  }
}
