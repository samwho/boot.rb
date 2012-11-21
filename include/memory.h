#pragma once
#include <multiboot.h>
#include <stdint.h>
#include <text.h>

void print_mmap_info(multiboot_info_t *mbd);
void print_mmap_entry(multiboot_info_t *mbd, uint32_t n);
