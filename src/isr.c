#include <screen.h>
#include <isr.h>
#include <timer.h>

typedef enum {
    I_DIVERROR      = 0,
    I_NONMASKABLE   = 2,
    I_BREAKPOINT    = 3,
    I_INVALIDOP     = 4,
    I_SEGNOTPRESENT = 11,
    I_STACKSEGFAULT = 12,
    I_GENPROTFAULT  = 13,
    I_PAGEFAULT     = 14,
    I_MACHINECHECK  = 18,
} interrupt_t;

isr_t interrupt_handlers[256];

char* interrupt_description(uint8_t n) {
    switch(n) {
        case 0:  return "Divide Error";
        case 2:  return "Non-Maskable Interrupt";
        case 3:  return "Breakpoint Exception";
        case 6:  return "Invalid Opcode";
        case 11: return "Segment Not Present";
        case 12: return "Stack-Segment Fault";
        case 13: return "General Protection Fault";
        case 14: return "Page Fault";
        case 18: return "Machine Check";
        default:
            if (n >= 32 && n <= 255)
                return "User Defined Interrupt";
            else
                return "Unknown";
    }
}

void isr_handler(registers_t regs)
{
	puts("Recieved interrupt ");
	puts(interrupt_description(regs.int_no));
	puts(" (");
	puthex(regs.int_no);
	puts(")");
	puts("\n");
	for(;;);
}

void register_interrupt_handler(uint8_t n, isr_t handler)
{
	interrupt_handlers[n] = handler;
}

/*
 * An explanation of WTF the below code means can be found here:
 *
 *   https://en.wikibooks.org/wiki/X86_Assembly/Programmable_Interrupt_Controller#Remapping
 */
void remap_pic()
{
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);
}


void irq_handler(registers_t regs)
{
	if(regs.int_no >= 40)
	{
		outb(0xA0, 0x20);
	}

	outb(0x20, 0x20);
	if (interrupt_handlers[regs.int_no] != 0)
	{
		void (*handler)() = interrupt_handlers[regs.int_no];
		handler(regs);
	}
}
