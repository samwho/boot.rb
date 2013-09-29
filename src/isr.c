#include <screen.h>
#include <isr.h>
#include <timer.h>

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
        case 32: return "Timer";
        case 33: return "Keyboard";
        default:
            if (n >= 32 && n <= 255)
                return "User Defined Interrupt";
            else
                return "Unknown";
    }
}

void isr_handler(registers_t regs)
{
	puts("[isr_handler] Recieved interrupt ");
	puts(interrupt_description(regs.int_no));
	puts(" (");
	puthex(regs.int_no);
	puts(")");
	puts("\n");

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

    // Spin for the time being. Remove this when no longer debugging.
	for(;;);
}

void register_interrupt_handler(uint8_t n, isr_t handler)
{
    puts("[isr]  Set handler for interrupt number ");
    putdec(n);
    puts(" to function at ");
    puthex((uint32_t)handler);
    puts("\n");
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

void invalid_opcode_handler(registers_t regs)
{
    puts("Invalid Opcode interrupt thrown (I_INVALIDOP).\n");
    puts("EIP points to: ");
    puthex(regs.eip);
    puts("\n");
    puthex(regs.eip);
    puts(" contains: ");
    puthex(*(uint32_t*)regs.eip);
    puts("\n");
}

void isr_init(void) {
    register_interrupt_handler(I_INVALIDOP, invalid_opcode_handler);
}

void print_isrs() {
    int i, interrupts[] = { 0, 2, 3, 6, 11, 12, 13, 14, 18, 32, 33 };
    for(i = 0; i < 11; i++) {
        putdec(interrupts[i]);
        puts(": ");
        puthex((uint32_t*)interrupt_handlers[interrupts[i]]);
        puts(" (");
        puts(interrupt_description(interrupts[i]));
        puts(")\n");
    }
}
