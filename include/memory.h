#pragma once
#include <multiboot.h>
#include <stdint.h>
#include <text.h>

void print_mmap_info(multiboot_info_t *mbd);
void print_mmap_entry(multiboot_info_t *mbd, uint32_t n);

#define BLOCK_MIN 4 // Smallest block is 4k
#define ORDER_LIMIT 10  // Largest allocatable block is 2^ORDER_LIMIT * BLOCK_MIN. ORDER_LIMIT of 10 makes 4096k
struct block
{
	void *addr;
	unsigned int  order;
	struct block *parent;
	int children[2]; // Indices to the children array
	char free;
	char pos; // 0 = left (first in memory), 1 = right (second in memory)
};

void mm_init(void *memstart);
void *malloc(uint32_t size);
void free(void *ptr);
void memset(void *ptr, char val, int size);
void memcpy(void *dest, void *src, int size);
