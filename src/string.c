#include "string.h"

int strlen(const char* str) {
	size_t i = 0;
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
	size_t i = 0;

	while (a[i] != 0 && b[i] != 0)
	{
		if(a[i] != b[i])
			break;
		i++;
	}

	if (a[i] == 0 && b[i] == 0)
		return 0;
	else if (a[i] == 0)
		return -1;
	else if (b[i] == 0)
		return 1;
    else
        return 2;
}

char *substr(char *str, size_t len)
{
	char *res = "";
	size_t i = 0;
	while(str[i] != 0 && i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return res;
}

char *strchr(const char *s, int c)
{
	while (*s++ != c)
		;

	return (char*)s;
}

int strncmp(const char *a, const char *b, size_t n)
{
	size_t i = 0;

	while (a[i] != 0 && b[i] != 0 && i < n)
	{
		if(a[i] != b[i])
			break;
		i++;
	}

	if (a[i] == 0 && b[i] == 0)
		return 0;
	else if (a[i] == 0)
		return -1;
	else if (b[i] == 0)
		return 1;
    else
        return 2;
}

char *strcat(char *dest, const char *src)
{
	char *tmp = dest;

	// Skip to end of dest.
	while (*tmp++)
		;

	do {
		*tmp = *src;

		tmp++;
	} while (*src++);

	return dest;
}

char *strcpy(char *dest, const char *src)
{
	char *tmp = dest;

	while ((*tmp++ = *src++))
		;

	return dest;
}

char *strncpy(char *dest, const char *src, size_t n)
{
	size_t i = n;

	while (i--)
		dest[i] = src[i];

	for (i = strlen(dest) - 1; i < n; i++)
		dest[i] = '\0';

	return dest;
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

void *memchr(const void *s, int c, size_t n)
{
	while ( ( *(unsigned char*)(s++) != (unsigned char)(c) ) && (n-- > 0))
		;

	return (void*)s;
}
