// Pilotage d'une LED RGB anode commune via GPIO (sysfs)
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#define _POSIX_C_SOURCE 200809L

#include "lib_couleurs.h"

/* Numéros GPIO (BCM) pour chaque couleur. Adapte-les à ton câblage. */
static const int RED_PIN = 581;
static const int GREEN_PIN = 588;
static const int BLUE_PIN = 582;

/* LED anode commune : active à l'état bas (0 = allumé, 1 = éteint). */
#define LED_ON 0
#define LED_OFF 1

static int file_exists(const char *path) {
    struct stat st;
    return stat(path, &st) == 0;
}




static int write_str(const char *path, const char *value) {
    FILE *f = fopen(path, "w");
    if (!f) return -1;
    if (fprintf(f, "%s", value) < 0) {
        fclose(f);
        return -1;
    }
    fclose(f);
    return 0;
}

static int ensure_output(int pin) {
    char path[96];
    snprintf(path, sizeof path, "/sys/class/gpio/gpio%d/direction", pin);
    if (!file_exists(path)) {
        char num[16];
        snprintf(num, sizeof num, "%d", pin);
        if (write_str("/sys/class/gpio/export", num) < 0) return -1;
    }
    if (write_str(path, "out") < 0) return -1;
    return 0;
}

static int set_pin(int pin, int level) {
    char path[96];
    snprintf(path, sizeof path, "/sys/class/gpio/gpio%d/value", pin);
    char val[4];
    snprintf(val, sizeof val, "%d", level);
    if (write_str(path, val) < 0) return -1;
    return 0;
}

static int set_rgb(int r_level, int g_level, int b_level) {
    if (set_pin(RED_PIN, r_level) < 0) return -1;
    if (set_pin(GREEN_PIN, g_level) < 0) return -1;
    if (set_pin(BLUE_PIN, b_level) < 0) return -1;
    return 0;
}

int led_init(void) {
    if (ensure_output(RED_PIN) < 0) return -1;
    if (ensure_output(GREEN_PIN) < 0) return -1;
    if (ensure_output(BLUE_PIN) < 0) return -1;
    return turnOff();
}

void led_shutdown(void) {
    turnOff();
    char num[16];
    snprintf(num, sizeof num, "%d", RED_PIN);
    write_str("/sys/class/gpio/unexport", num);
    snprintf(num, sizeof num, "%d", GREEN_PIN);
    write_str("/sys/class/gpio/unexport", num);
    snprintf(num, sizeof num, "%d", BLUE_PIN);
    write_str("/sys/class/gpio/unexport", num);
}

int led_set_success(void) { return green(); }
int led_set_error(void)   { return red();   }

int led_toggle_running(void) {
    static bool toggle = false;
    static struct timespec last = {0};

    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);

    long elapsed_ms =
        (now.tv_sec - last.tv_sec) * 1000L +
        (now.tv_nsec - last.tv_nsec) / 1000000L;

    if (last.tv_sec == 0 && last.tv_nsec == 0) {
        // première fois: initialise et allume une couleur
        last = now;
        toggle = false;
        return blue();
    }

    if (elapsed_ms < 200) {
        // pas encore le moment de changer
        return 0;
    }

    last = now;
    toggle = !toggle;
    return toggle ? purple() : blue();
}


int turnOff(void)   { return set_rgb(LED_OFF, LED_OFF, LED_OFF); }
int white(void)     { return set_rgb(LED_ON,  LED_ON,  LED_ON ); }
int red(void)       { return set_rgb(LED_ON,  LED_OFF, LED_OFF); }
int green(void)     { return set_rgb(LED_OFF, LED_ON,  LED_OFF); }
int blue(void)      { return set_rgb(LED_OFF, LED_OFF, LED_ON ); }
int yellow(void)    { return set_rgb(LED_ON,  LED_ON,  LED_OFF); }
int purple(void)    { return set_rgb(LED_ON,  LED_OFF, LED_ON ); }
int lightBlue(void) { return set_rgb(LED_OFF, LED_ON,  LED_ON ); }
