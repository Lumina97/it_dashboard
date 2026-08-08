#include "temp.h"

#include <stdio.h>
#include <stdlib.h>

float get_temperature() {

  FILE *file = fopen("/sys/class/thermal/thermal_zone0/temp", "r");

  if (!file) {
    perror("temp");
    return -1;
  }

  long temp;

  if (fscanf(file, "%ld", &temp) != 1) {
    fclose(file);
    return -1;
  }

  fclose(file);

  return temp /= 1000.0f;
}
