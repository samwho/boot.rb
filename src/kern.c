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
#include <tests.h>

extern int mirb_main(int argc, char **argv);

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

	run_tests();

	char *cmd = "";
	while(1)
	{
		puts("# ");

    cmd = "";
		cmd = readUntilReturn();

    if (strlen(cmd ) == 0)
      continue;
    else if (strcmp(cmd, "help") == 0)
			printf(
"COMMANDS:\n\
help     - This command.\n\
test     - A useful test.\n\
reset    - Resets the CPU.\n\
malloc   - Allocate a 4k block of RAM.\n\
memreset - Reset the heap.\n\
mmap     - Print a memory map.\n\
irb      - Open an mruby terminal.\n\
");
		else if(strcmp(cmd, "test") == 0)
			run_tests();
		else if (strcmp(cmd, "reset") == 0)
			outb(0x64, 0xFE);
		else if (strcmp(cmd, "malloc") == 0)
			printf("Mallocing one 4k block: 0x%x\n", malloc(4096));
		else if (strcmp(cmd, "memreset") == 0)
		{
			printf("Resetting heap.\n");
			mm_init(0xDEADBEEF);
		}
		else if (strcmp(cmd, "mmap") == 0)
		{
			printf("mmap no. %c\n", cmd[5]);
			print_mmap_entry(mbd, cmd[5] - 48);
      puts("\n");
		}
		else if (strcmp(cmd, "irb") == 0)
		{
			mirb_main(0, NULL);
		}
		else
			printf("ERROR: Command not recognised. Please blow into the cartridge and try again.\n");

	}

	for(;;);

}

