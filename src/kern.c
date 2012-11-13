#include <gdt.h>
#include <misc.h>
#include <screen.h>
#include <multiboot.h>
#include <idt.h>
#include <timer.h>
#include <isr.h>

void kmain(void)
{
	extern unsigned int magic;

	extern multiboot_info_t *mbd;

	if (magic != 0x2BADB002)
	{
		/* Something went wrong. Should abort. Or something */
	}

	cls();

	puts("Welcome to Kernel!\n");

	puts("Multiboot command line: ");
	puts((char *)mbd->cmdline);
	puts("\nMultiboot flags: ");
	puthex(mbd->flags);
	puts("\n");

	puts("Initalising GDT...");
	gdtInit();
	puts("done.\n");

	puts("Initalising IDT...");
	idtInit();
	puts("done.\n");

	puts("Initialising PIT...");
	timerInit(1);
	puts("done.\n");


	__asm__("sti");

	for(;;);

}

