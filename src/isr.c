#include <screen.h>
#include <isr.h>
#include <timer.h>

isr_t interrupt_handlers[256];

void isr_handler(registers_t regs)
{

	puts("Recieved interrupt number ");
	puthex(regs.int_no);
	puts("\n");
	for(;;);
}

void register_interrupt_handler(uint8_t n, isr_t handler)
{
	interrupt_handlers[n] = handler;
}

void remapPic()
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
