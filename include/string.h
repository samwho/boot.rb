#ifndef STRING_H
#define STRING_H

#include <memory.h>

int strcmp(const char *a, const char *b);
int strlen(const char *str);
char *substr(char *str, int len);

const char* begin(char* str);
const char* end(char* str);

int memcmp(const void *s1, const void *s2, size_t n);

#endif /* STRING_H */
