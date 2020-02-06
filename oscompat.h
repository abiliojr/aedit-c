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
static inline unsigned char *ptoc(unsigned char *data) {
    if (!data) return NULL;
    unsigned len = data[0];
    if (len == 0) return data;
    memmove(data, data + 1, len);
    data[len] = '\0';
    return data;
}

static inline unsigned char *ctop(unsigned char *data) {
    if (!data) return NULL;
    unsigned len = strlen(data);
    if (len == 0) return data;
    memmove(data + 1, data, len);
    data[0] = len;
    return data;
}

static void inline strlcpy(char *dest, char *src, size_t n) {
    strncpy(dest, src, n);
    dest[n - 1] = '\0';
}

static unsigned char *copyToC(unsigned char *from, unsigned char *newMem) {
    ((unsigned char *) memcpy(newMem, from + 1, from[0]))[from[0]] = '\0';
    return newMem;
}

static unsigned char *copyToP(unsigned char *from, unsigned char *newMem) {
    memcpy(newMem + 1, from, strlen(from));
    newMem[0] = strlen(from);
    return newMem;
}

#define tmp_str(len) (unsigned char[len]){}
#define ptocC(var, len) copyToC(var, tmp_str(len))
#define ctopC(var, len) copyToP(var, tmp_str(len))
