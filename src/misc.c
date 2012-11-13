#include <misc.h>

void memset(void *ptr, char val, int size)
{
	for(int i = 0; i < size; i++)
	{
		((char *)ptr)[i] = val;
	}
}

void outb(uint16_t port, uint8_t val)
{
	__asm__ volatile("outb %0, %1" : : "a"(val), "d"(port));
}

uint8_t inb(uint16_t port)
{
	uint8_t val;
	__asm__ volatile("inb %1, %0" : "=a"(val) : "d"(port));
	return val;
}

