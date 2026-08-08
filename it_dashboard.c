#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "arduino.h"
#include "cpu.h"
#include "ram.h"

int main() {

  int arduino = arduino_init("/dev/ttyACM0");
  if (arduino == -1) {
    perror("Failed to initialize arduino - shutting down");
    return -1;
  }
  sleep(2);
  while (1) {

    float cpu = get_cpu_usage();
    float ram = get_ram_usage();
    float temp = 0;
    float net = 0;

    if (arduino_send(cpu, ram, temp, net) == -1) {
      break;
    }

    sleep(1);
  }
  arduino_close();

  return 0;
}
