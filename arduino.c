#include "arduino.h"

#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

static int arduino_fd = -1;

int arduino_init(const char *device) {
  arduino_fd = open(device, O_RDWR | O_NOCTTY);

  if (arduino_fd == -1) {
  }

  struct termios tty;

  if (tcgetattr(arduino_fd, &tty) != 0) {
    perror("Failed to get serial settings");
    close(arduino_fd);
    arduino_fd = -1;
    return -1;
  }

  cfsetispeed(&tty, B9600);
  cfsetospeed(&tty, B9600);

  tty.c_cflag |= (CLOCAL | CREAD);
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;
  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CRTSCTS;

  tty.c_lflag = 0;
  tty.c_oflag = 0;
  tty.c_iflag = 0;

  tcsetattr(arduino_fd, TCSANOW, &tty);

  return 0;
}

void arduino_close() {
  if (arduino_fd != -1) {
    close(arduino_fd);
    arduino_fd = -1;
  }
}

int arduino_send(float cpu, float ram, float temp, float net) {
  if (arduino_fd == -1) {
    return -1;
  }

  char message[128];

  int length =
      snprintf(message, sizeof(message),
               "CPU=%.1f,RAM=%.1f,TEMP=%.1f,NET=%.1f\n", cpu, ram, temp, net);

  if (length < 0 || (size_t)length >= sizeof(message)) {
    return -1;
  }

  int written = write(arduino_fd, message, length);

  if (written != length) {
    perror("Failed to send data to arduino");
    return -1;
  }

  return 0;
}
