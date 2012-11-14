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
		puts("# ");
		char *cmd = readUntilReturn();
		if(strcmp(cmd, "test") == 0)
			printf("ERROR: Test failed.\n");
		else if (strcmp(cmd, "help") == 0)
			printf("COMMANDS:\nhelp - This command.\ntest - A useful test.\n");
		else 
			printf("ERROR: Command not recognised. Please blow into the cartridge and try again.\n");

	}

	for(;;);

}

