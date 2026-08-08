#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "cpu.h"

float get_cpu_usage() {

    FILE *file = fopen("/proc/stat", "r");

    if (!file)
        return 0;

    char cpu[10];
    long user, nice, system, idle;

    fscanf(file, "%s %ld %ld %ld %ld",
           cpu,
           &user,
           &nice,
           &system,
           &idle);

    fclose(file);


    long total = user + nice + system + idle;

    static long last_total = 0;
    static long last_idle = 0;

    long total_diff = total - last_total;
    long idle_diff = idle - last_idle;

    last_total = total;
    last_idle = idle;


    if(total_diff == 0)
        return 0;

    return (float)(total_diff - idle_diff) / total_diff * 100;
}
float get_cpu() {

    FILE *file = fopen("/proc/stat", "r");

    if (!file)
        return 0;

    char cpu[10];
    long user, nice, system, idle;

    fscanf(file, "%s %ld %ld %ld %ld",
           cpu,
           &user,
           &nice,
           &system,
           &idle);

    fclose(file);


    long total = user + nice + system + idle;

    static long last_total = 0;
    static long last_idle = 0;

    long total_diff = total - last_total;
    long idle_diff = idle - last_idle;

    last_total = total;
    last_idle = idle;


    if(total_diff == 0)
        return 0;

    return (float)(total_diff - idle_diff) / total_diff * 100;
}

