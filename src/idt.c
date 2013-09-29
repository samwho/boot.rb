#include <idt.h>
#include <isr.h>

extern void setIdt(struct idt_ptr *);

struct IDT idt[IDT_ENTRIES];

void idtSetGate(int num, int offset, int selector, int type)
{
	idt[num].offset_low = offset & 0xFFFF;
	idt[num].offset_high = offset >> 16 & 0xFFFF;
	idt[num].type_attr = type;
	idt[num].selector = selector;
}

void idtInit()
{
	memset(&idt, 0, sizeof(struct IDT) * IDT_ENTRIES - 1);
	struct idt_ptr idtp;
	idtp.limit = sizeof(struct IDT) * IDT_ENTRIES - 1;
	idtp.offset = (uint32_t)&idt;

	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(1, (uint32_t)isr1, 0x08, 0x8E);
	idtSetGate(2, (uint32_t)isr2, 0x08, 0x8E);
	idtSetGate(3, (uint32_t)isr3, 0x08, 0x8E);
	idtSetGate(4, (uint32_t)isr4, 0x08, 0x8E);
	idtSetGate(5, (uint32_t)isr5, 0x08, 0x8E);
	idtSetGate(6, (uint32_t)isr6, 0x08, 0x8E);
	idtSetGate(7, (uint32_t)isr7, 0x08, 0x8E);
	idtSetGate(8, (uint32_t)isr8, 0x08, 0x8E);
	idtSetGate(9, (uint32_t)isr9, 0x08, 0x8E);
	idtSetGate(10, (uint32_t)isr10, 0x08, 0x8E);
	idtSetGate(11, (uint32_t)isr11, 0x08, 0x8E);
	idtSetGate(12, (uint32_t)isr12, 0x08, 0x8E);
	idtSetGate(13, (uint32_t)isr13, 0x08, 0x8E);
	idtSetGate(14, (uint32_t)isr14, 0x08, 0x8E);
	idtSetGate(15, (uint32_t)isr15, 0x08, 0x8E);
	idtSetGate(16, (uint32_t)isr16, 0x08, 0x8E);
	idtSetGate(17, (uint32_t)isr17, 0x08, 0x8E);
	idtSetGate(18, (uint32_t)isr18, 0x08, 0x8E);
	idtSetGate(19, (uint32_t)isr19, 0x08, 0x8E);
	idtSetGate(20, (uint32_t)isr20, 0x08, 0x8E);
	idtSetGate(21, (uint32_t)isr21, 0x08, 0x8E);
	idtSetGate(22, (uint32_t)isr22, 0x08, 0x8E);
	idtSetGate(23, (uint32_t)isr23, 0x08, 0x8E);
	idtSetGate(24, (uint32_t)isr24, 0x08, 0x8E);
	idtSetGate(25, (uint32_t)isr25, 0x08, 0x8E);
	idtSetGate(26, (uint32_t)isr26, 0x08, 0x8E);
	idtSetGate(27, (uint32_t)isr27, 0x08, 0x8E);
	idtSetGate(28, (uint32_t)isr28, 0x08, 0x8E);
	idtSetGate(29, (uint32_t)isr29, 0x08, 0x8E);
	idtSetGate(30, (uint32_t)isr30, 0x08, 0x8E);
	idtSetGate(31, (uint32_t)isr31, 0x08, 0x8E);

	remap_pic();

	idtSetGate(32, (uint32_t)irq0, 0x08, 0x8E);
	idtSetGate(33, (uint32_t)irq1, 0x08, 0x8E);
	idtSetGate(34, (uint32_t)irq2, 0x08, 0x8E);
	idtSetGate(35, (uint32_t)irq3, 0x08, 0x8E);
	idtSetGate(36, (uint32_t)irq4, 0x08, 0x8E);
	idtSetGate(37, (uint32_t)irq5, 0x08, 0x8E);
	idtSetGate(38, (uint32_t)irq6, 0x08, 0x8E);
	idtSetGate(39, (uint32_t)irq7, 0x08, 0x8E);
	idtSetGate(40, (uint32_t)irq8, 0x08, 0x8E);
	idtSetGate(41, (uint32_t)irq9, 0x08, 0x8E);
	idtSetGate(42, (uint32_t)irq10, 0x08, 0x8E);
	idtSetGate(43, (uint32_t)irq11, 0x08, 0x8E);
	idtSetGate(44, (uint32_t)irq12, 0x08, 0x8E);
	idtSetGate(45, (uint32_t)irq13, 0x08, 0x8E);
	idtSetGate(46, (uint32_t)irq14, 0x08, 0x8E);
	idtSetGate(47, (uint32_t)irq15, 0x08, 0x8E);
	setIdt(&idtp);
}


