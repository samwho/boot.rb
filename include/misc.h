#pragma once
#include <stdint.h>

void memset(void *ptr, char val, int size);
void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);

