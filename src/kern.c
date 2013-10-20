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

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
	{
		PANIC("Multiboot magic number is wrong: %08x", magic);
	}

	cls();

    if (mbd->flags & MULTIBOOT_INFO_CMDLINE) {
        printf("[mbd] cmdline: %s\n", (char*)mbd->cmdline);
    }

	if (mbd->flags & MULTIBOOT_INFO_MEMORY) {
        printf("[mbd] mem_lower: %dkb\n", (unsigned)mbd->mem_lower);
        printf("[mbd] mem_upper: %dkb\n", (unsigned)mbd->mem_upper);
    }

    if (mbd->flags & MULTIBOOT_INFO_MEM_MAP){
        print_mmap_info(mbd);
    }

	gdt_init();
	idt_init();
	isr_init();
	timer_init(1);
	keyboard_init();

    // TODO: We'll need a way of checking we aren't going outside the
    // available range.
    mm_init(KERNEL_END);

	__asm__("sti");

    test_init();
	/* run_tests(); */

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
mmap      - Print the memory map from GRUB.\n\
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
			print_mmap_info(mbd);
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
