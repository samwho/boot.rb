#include <gdt.h>
#include <misc.h>
#include <screen.h>
#include <multiboot.h>
#include <idt.h>
#include <timer.h>
#include <isr.h>
#include <keyboard.h>
#include <text.h>
#include <memory.h>

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

	puts("Initialising memory manager...");
	mm_init(0xDEADBEEF);
	puts("done.\n");

	__asm__("sti");

	char *cmd = "";
	while(1)
	{
		puts("# ");
		cmd = readUntilReturn();
		if(strcmp(cmd, "test") == 0)
			printf("ERROR: Test failed.\n");
		else if (strcmp(cmd, "help") == 0)
			printf("COMMANDS:\nhelp - This command.\ntest - A useful test.\nreset - Resets the CPU.\n");
		else if (strcmp(cmd, "reset") == 0)
			outb(0x64, 0xFE);
		else if (strcmp(cmd, "malloc") == 0)
			printf("Mallocing one 4k block: 0x%x", malloc(4096));
		else if (strcmp(cmd, "memreset") == 0)
		{
			printf("Resetting heap\n.");
			mm_init(0xDEADBEEF);
		}
		else if (strcmp(substr(cmd, 4), "mmap") == 0)
		{
			printf("mmap no. %c\n", cmd[5]);
			print_mmap_entry(mbd, cmd[5] - 48);
		}
		else 
			printf("ERROR: Command not recognised. Please blow into the cartridge and try again.\n");

	}

	for(;;);

}

