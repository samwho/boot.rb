#pragma once
#include <multiboot.h>
#include <stdint.h>
#include <text.h>

void print_mmap_info(multiboot_info_t *mbd);
void print_mmap_entry(multiboot_info_t *mbd, uint32_t n);
multiboot_memory_map_t *first_available_memory_range(multiboot_info_t *mbd);

/*
 * Start linker script variables. These define where each kernel section begins
 * and ends.
 */
extern void _BSS_START;
extern void _BSS_END;
extern void _DATA_START;
extern void _DATA_END;
extern void _TEXT_START;
extern void _TEXT_END;
#define BSS_END    &_BSS_END
#define BSS_START  &_BSS_START
#define DATA_END   &_DATA_END
#define DATA_START &_DATA_START
#define TEXT_END   &_TEXT_END
#define TEXT_START &_TEXT_START
#define KERNEL_END BSS_END
/*
 * End linker script variables
 */

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
void memcpy(void *dest, const void *src, int size);
