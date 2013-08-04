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

int strcmp(const char *a, const char *b)
{
	int i = 0;
	while (a[i] != 0 && b[i] != 0)
	{
		if(a[i] != b[i])
			return 1;
		i++;
	}
	return 0;
}

char *substr(char *str, int len)
{
	char *res = "";
	int i = 0;
	while(str[i] != 0 && i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return res;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
  size_t i;

  for (i = 0; i < n; i++, s1++, s2++) {
    if ( *((uint8_t*)(s1)) != *((uint8_t*)(s2)) )
      return ( *((uint8_t*)(s1)) - *((uint8_t*)(s2)) );
  }

  return 0;
}
