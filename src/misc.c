#include <misc.h>

void memset(void *ptr, char val, int size)
{
	for(int i = 0; i < size; i++)
	{
		((char *)ptr)[i] = val;
	}
}
