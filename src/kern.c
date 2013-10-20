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
#include <test.h>

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

	LOG("Welcome to Kernel!");

	LOG("Multiboot command line: %d", mbd->cmdline);
    LOG("Multiboot flags: 0x%x", mbd->flags);

	LOG("gdt_init() start...");
	gdt_init();
	LOG("gdt_init() done.");

	LOG("idt_init() start...");
	idt_init();
	LOG("idt_init() done.");

	LOG("isr_init() start...");
	isr_init();
	LOG("isr_init() done.");

	LOG("timer_init() start...");
	timer_init(1);
	LOG("timer_init() done.");

	LOG("keyboard_init() start...");
	keyboard_init();
	LOG("keyboard_init() done.");

	LOG("mm_init() start...");
	mm_init((void*)0x60000000);
	LOG("mm_init() done.");

	__asm__("sti");

    LOG("test_init() start...");
    test_init();
    LOG("test_init() done.");

	run_tests();

	char *cmd = "";
	while(1)
	{
		puts("# ");

		cmd = "";
		cmd = read_until_return();

		if (strlen(cmd) == 0)
			continue;
		else if (strcmp(cmd, "help") == 0)
			printf(
"COMMANDS:\n\
help      - This command.\n\
test      - A useful test.\n\
reset     - Resets the CPU.\n\
malloc    - Allocate a 4k block of RAM.\n\
memreset  - Reset the heap.\n\
mmap      - Print a memory map.\n\
irb       - Open an mruby terminal.\n\
printisrs - Prints the full ISR table.\n\
");
		else if(strcmp(cmd, "test") == 0)
			run_tests();
		else if (strcmp(cmd, "reset") == 0)
			outb(0x64, 0xFE);
		else if (strcmp(cmd, "malloc") == 0)
			printf("Mallocing one 4k block: 0x%x\n", (unsigned int)malloc(4096));
		else if (strcmp(cmd, "memreset") == 0)
		{
			printf("Resetting heap.\n");
			mm_init((void*)0xDEADBEEF);
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
        else if (strcmp(cmd, "printisrs") == 0)
        {
            print_isrs();
        }
		else
			printf("ERROR: Command not recognised. Please blow into the cartridge and try again.\n");

	}

	for(;;);
}
