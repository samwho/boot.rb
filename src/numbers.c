#include <stdlib.h>

int atoi(const char *str)
{
	int ret = 0,
	    pos = 0;
	char *tmp = end(str);

	for (pos = 0; tmp-- != str; pos++)
		ret += (pos * 10) + (*tmp - 48);

	return ret;
}
