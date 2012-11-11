#include <gdt.h>
#include <misc.h>

extern void setGdt(struct gdt_ptr *);

unsigned next_entry;
struct GDT gdt[3];

/* Copied with love from tsion's spideros */
void new_entry(int base, int limit, char access, char flags)
{
	gdt[next_entry].base_low = base & 0xFFFF;
	gdt[next_entry].base_middle = base >> 16 & 0xFF;
	gdt[next_entry].base_high = base >> 24 & 0xFF;
	gdt[next_entry].limit_low = limit & 0xFFFF;
	gdt[next_entry].flags_and_limit = flags | (limit >> 16 & 0xF);
	gdt[next_entry].access = access | 0x10;

	next_entry++;
}


void gdtInit()
{
/*	  initGDT[0] = struct GDT {.base=0, .limit=0, .type=0}; //Selector 0x00 is unusable
	initGDT[1] = {.base=0x04000000, .limit=0x03ffffff, .type=0x9A}; //Selector 0x08 is code
	initGDT[2] = {.base=0x08000000, .limit=0x03ffffff, .type=0x92}; //Selector 0x10 is data */

	memset(&gdt, 0, sizeof(struct GDT) * 3);
	next_entry = 1;

	new_entry(0, 0xFFFFF,
			GDT_PRESENT | GDT_DPL0 | GDT_CODE | GDT_READABLE, GDT_GRANULAR | GDT_32BIT);

	new_entry(0, 0xFFFFF,
			GDT_PRESENT | GDT_DPL0 | GDT_DATA | GDT_WRITABLE, GDT_GRANULAR | GDT_32BIT);


	struct gdt_ptr gdtp;
	gdtp.limit = sizeof(struct GDT) * GDT_ENTRIES - 1;
	gdtp.base = (unsigned int)&gdt;
	setGdt(&gdtp);

}


