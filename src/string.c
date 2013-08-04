#include "string.h"

int strlen(const char* str) {
	int i = 0;
	while(str[i] != '\0')
		i++;
	return i;
}

const char* begin(const char* str) {
	return str;
}

const char* end(const char* str) {
	// Find the end of the string (where the nul is found)
	while(*str != '\0')
		str++;
  return str;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
  while (*s1++ && *s2++) {
    if (*s1 < *s2)
      return -1;
    else if (*s1 > *s2)
      return 1;
  }

  return 0;
}
