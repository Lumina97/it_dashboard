#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void get_ram() {
    FILE *file = fopen("/proc/meminfo", "r");

    if (!file) {
        perror("meminfo");
        return;
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

    printf("RAM: %.1f%%\n", percent);
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


int main() {

    while(1) {

        float cpu = get_cpu();

        printf("CPU: %.1f%%\n", cpu);

        get_ram();

        printf("----------------\n");

        sleep(1);
    }

    return 0;
}
