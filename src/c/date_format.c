#include "date_format.h"

#include <stdio.h>

void date_format_day_month(const struct tm *tick_time, char *buffer, size_t buffer_size) {
  static const char *const k_months[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
  };

  snprintf(buffer, buffer_size, "%d %s", tick_time->tm_mday, k_months[tick_time->tm_mon]);
}
