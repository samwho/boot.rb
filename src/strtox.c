#include <stdlib.h>

double strtod(const char *nptr, char **endptr) {
	return 4;
}

inline float strtof(const char *nptr, char **endptr) {
	return (float)strtod(nptr, endptr);
}

//long strtol(const char *nptr, char **endptr, int base);
//long double strtold(const char *nptr, char **endptr);
//long long strtoll(const char *nptr, char **endptr, int base);

unsigned long strtoul(const char *nptr, char **endptr, int base) {
	return 4;
}

//unsigned long long strtoull(const char *nptr, char **endptr, int base);
