#pragma once
#pragma pack(1) 
struct GDT 
{
	short limit_low;
	short base_low;
	char base_middle;
	char access;
	char flags_and_limit;
	char base_high;
};__attribute((packed))__;

struct gdt_ptr {
	unsigned short limit;
	unsigned int base;
};__attribute((packed))__;

enum {
	// Access byte properties
	GDT_PRESENT    = 0x80,

	GDT_DPL0	   = 0x00, // DPL = descriptor privilege level (ring level)
	GDT_DPL1	   = 0x20,
	GDT_DPL2	   = 0x40,
	GDT_DPL3	   = 0x60,

	GDT_CODE	   = 0x08,
	GDT_READABLE   = 0x02,
	GDT_CONFORMING = 0x04,

	GDT_DATA	   = 0x00,
	GDT_WRITABLE   = 0x02,
	GDT_GROW_DOWN  = 0x04,

	// Flags
	GDT_GRANULAR   = 0x80,
	GDT_32BIT	   = 0x40,
	GDT_16BIT	   = 0x00
};

#define GDT_ENTRIES 256

void gdtInit();
