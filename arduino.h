#ifndef ARDUINO_H
#define ARDUINO_H

int arduino_init(const char *device);
int arduino_send(float cpu, float ram, float temp, float net);
void arduino_close(void);

#endif // !ARDUINO_H
