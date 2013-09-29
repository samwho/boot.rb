#include <screen.h>
#include <isr.h>
#include <timer.h>

extern void io_wait();

isr_t interrupt_handlers[256];

/*
 * Function to translate an interrupt number into its name. List taken from:
 *
 *   http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
 */
char* interrupt_description(uint8_t n)
{
    switch(n) {
        case I_DIV0ERROR:         return "Divide by zero error";
        case I_DEBUGEXCEPTION:    return "Debug exception";
        case I_NONMASKABLE:       return "Non-Maskable interrupt";
        case I_BREAKPOINT:        return "Breakpoint exception";
        case I_IDOVERFLOW:        return "Into detected overflow";
        case I_OUTOFBOUNDS:       return "Out of bounds exception";
        case I_INVALIDOP:         return "Invalid opcode";
        case I_NOCOPROCESSOR:     return "No coprocessor exception";
        case I_DOUBLEFAULT:       return "Double fault";
        case I_COSEGMENTOVERRUN:  return "Coprocessor segment overrun";
        case I_BADTSS:            return "Bad TSS";
        case I_SEGNOTPRESENT:     return "Segment not present";
        case I_STACKSEGFAULT:     return "Stack-segment fault";
        case I_GENPROTFAULT:      return "General protection fault";
        case I_PAGEFAULT:         return "Page fault";
        case I_UNKNOWN:           return "Unknown interrupt exception";
        case I_COPROCESSORFAULT:  return "Coprocessor fault";
        case I_ALIGNMENTCHECK:    return "Alignment check exception";
        case I_MACHINECHECK:      return "Machine check";
        case I_TIMER:             return "Timer";
        case I_KEYBOARD:          return "Keyboard";

        default:
            if (n >= 32 && n <= 255)
                return "User Defined Interrupt";
            else
                return "Unknown";
    }
}

void isr_handler(registers_t regs)
{
	if (interrupt_handlers[regs.int_no] != 0) {
		interrupt_handlers[regs.int_no]();
    } else {
        puts("[isr_handler] Recieved interrupt without handler: ");
        puts(interrupt_description(regs.int_no));
        puts(" (");
        puthex(regs.int_no);
        puts(")");
        puts("\n");
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
 *
 * Or here:
 *
 *   http://wiki.osdev.org/PIC
 */
void remap_pic()
{
    unsigned char a1, a2;

    // Save masks for restoration later.
    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);

    // Start initialisation sequence in cascade mode.
	outb(PIC1_COMMAND, PIC_INIT); io_wait();
	outb(PIC2_COMMAND, PIC_INIT); io_wait();

    // Set master and slave vector offsets. 32 and 40 respectively.
	outb(PIC1_DATA, 0x20); io_wait();
	outb(PIC2_DATA, 0x28); io_wait();

    // Tell master that there is a slave PIC at IRQ2 (0000 0010)
	outb(PIC1_DATA, 0x04); io_wait();

	// Tell slave its cascade identity
	outb(PIC2_DATA, 0x02); io_wait();

    // Set master and slave to 8086/88 (MCS-80/85) mode
	outb(PIC1_DATA, 0x01); io_wait();
	outb(PIC2_DATA, 0x01); io_wait();

    // Restore saved masks
	outb(PIC1_DATA, a1);
	outb(PIC2_DATA, a2);
}

void irq_handler(registers_t regs)
{
    // If the IRQ involved the slave PIC chip (IRQ7 or greater), send the reset
    // signal to that chip.
	if(regs.int_no > IRQ7)
		outb(0xA0, 0x20);

    // Always send the reset signal to the master PIC chip.
	outb(0x20, 0x20);

    // And finally, call the necessary interrupt handler.
	if (interrupt_handlers[regs.int_no] != 0)
		interrupt_handlers[regs.int_no]();
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

void isr_init(void)
{
    register_interrupt_handler(I_INVALIDOP, invalid_opcode_handler);
}

void print_isrs()
{
    // Array of meaningful interrupts that we're handling.
    int i, interrupts[] = { 0, 2, 3, 6, 11, 12, 13, 14, 18, 32, 33 };

    for(i = 0; i < 11; i++) {
        putdec(interrupts[i]);
        puts(": ");
        puthex((uint32_t)interrupt_handlers[interrupts[i]]);
        puts(" (");
        puts(interrupt_description(interrupts[i]));
        puts(")\n");
    }
}
