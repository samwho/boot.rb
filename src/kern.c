#include <gdt.h>
#include <misc.h>
#include <screen.h>
#include <multiboot.h>
#include <idt.h>
#include <timer.h>
#include <isr.h>
#include <keyboard.h>
#include <text.h>

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

	printf("Multiboot command line: %s \nMultiboot flags: 0x%x\n", mbd->cmdline, mbd->flags);

	puts("Initalising GDT...");
	gdtInit();
	puts("done.\n");

	puts("Initalising IDT...");
	idtInit();
	puts("done.\n");

	puts("Initialising PIT...");
	timerInit(1);
	puts("done.\n");

	puts("Initialising keyboard...");
	keyboardInit();
	puts("done.\n");


	__asm__("sti");

	while(1)
	{
		char *keys;
		if(readBuffer(1, keys))
			printf("%c", keys[0]);
	}

	for(;;);

}

