#ifndef STRING_H
#define STRING_H

#include <memory.h>

int strcmp(const char *a, const char *b);
int strlen(const char *str);
char *substr(char *str, size_t len);

const char* begin(const char* str);
const char* end(const char* str);

int strncmp(const char *a, const char *b, size_t n);
char *strchr(const char *s, int c);
char *strcat(char *dest, const char *src);

char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);

int memcmp(const void *s1, const void *s2, size_t n);
void *memchr(const void *s, int c, size_t n);

#endif /* STRING_H */
