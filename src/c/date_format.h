#pragma once

#include <pebble.h>

void date_format_day_month(const struct tm *tick_time, char *buffer, size_t buffer_size);
