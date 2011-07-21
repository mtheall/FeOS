//
// FeOS C Standard Library
// string.h
//     String/memory manipulation functions
//

#pragma once
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

// String functions
size_t strlen(const char*);
char*  strcpy(char*, const char*);
char*  strcat(char*, const char*);
int    strcmp(const char*, const char*);
int    stricmp(const char*, const char*);
char*  strncpy(char*, const char*, size_t);
char*  strncat(char*, const char*, size_t);
int    strncmp(const char*, const char*, size_t);
int    strnicmp(const char*, const char*, size_t);

// Memory functions
void* memcpy(void*, const void*, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);
int   memcmp(const void*, const void*, size_t);

// Searching functions
void* memchr(const void*, int, size_t);
char* strchr(const char*, int);
size_t strcspn(const char*, const char*);
char* strpbrk(const char*, const char*);
char* strrchr(const char*, int);
size_t strspn(const char*, const char*);
char* strstr(const char*, const char*);
char* strtok(char*, const char*);

// These functions will never be implemented:
// strcoll, strxfrm, strerror

#ifdef __cplusplus
}
#endif
