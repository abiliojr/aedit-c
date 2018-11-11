#pragma once

#ifdef MSDOS
#define access _access
#define unlink _unlink

#else

/* #todo: fix issue where including <unistd.h> gives conflicts with pause and sleep */
int unlink(const char *pathname);
int access(const char *pathname, int mode);
#endif
