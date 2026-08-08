#include "ram.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float get_ram_usage() {
  FILE *file = fopen("/proc/meminfo", "r");

  if (!file) {
    perror("meminfo");
    return -1.0;
  }

  long total = 0;
  long available = 0;

  char label[64];

  while (fscanf(file, "%63s %ld kB", label, &available) == 2) {

    if (strcmp(label, "MemTotal:") == 0) {
      total = available;
    }

    if (strcmp(label, "MemAvailable:") == 0) {
      available = available;
      break;
    }
  }

  fclose(file);

  long used = total - available;
  float percent = ((float)used / total) * 100;
  return percent;
}
