#pragma once

#ifdef MSDOS
#define access _access
#define unlink _unlink
#define kbhit _kbhit

#else

#include <unistd.h>
#define _getch  getchar
#define _putch  putchar

int kbhit(void);
void setup_stdin(void);
void restore_stdin(void);
void Ignore_quit_signal(void);
void Restore_quit_signal(void);
void ms_sleep(unsigned int milliseconds);
#endif

#include <string.h>
static void inline ptoc(unsigned char *data) {
    if (!data) return;
    unsigned len = data[0];
    if (len == 0) return;
    memmove(data, data + 1, len);
    data[len] = '\0';
}

static void inline ctop(unsigned char *data) {
    if (!data) return;
    unsigned len = strlen(data);
    if (len == 0) return;
    memmove(data + 1, data, len);
    data[0] = len;
}

static void inline strlcpy(char *dest, char *src, size_t n) {
    strncpy(dest, src, n);
    dest[n - 1] = '\0';
}