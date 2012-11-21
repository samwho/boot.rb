#pragma once

#include <modifiers.h>
#include <stdint.h>
#include <stdarg.h>

#define TF_ALTERNATE 1
#define TF_ZEROPAD 2
#define TF_LEFT 4
#define TF_SPACE 8
#define TF_EXP_SIGN 16
#define TF_SMALL 32
#define TF_PLUS 64
#define TF_UNSIGNED 128

int m_printn(OUT char *str, IN size_t maxlength, IN int len, IN unsigned int n,
				IN unsigned int base, IN size_t size, IN int flags, IN int precision);
int printf(IN const char *fmt, ...);
int sprintf(OUT char *str, IN const char *fmt, ...);
int snprintf(OUT char *str, IN size_t size, IN const char *fmt, ...);
int vprintf(IN const char *fmt, va_list ap);
int vsprintf(OUT char *str, IN const char *fmt, va_list ap);
int vsnprintf(OUT char *str, IN size_t size, IN const char *fmt,
				IN va_list ap);

int strcmp(char *a, char *b);
int strlen(char *str);
char *substr(char *str, int len);
