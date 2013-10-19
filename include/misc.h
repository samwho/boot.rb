#pragma once
#include <stdint.h>
#include <string.h>

#define LOG(message, ...) printf("[%s:%d in %s()] " message "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
