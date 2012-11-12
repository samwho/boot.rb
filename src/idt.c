#include <idt.h>

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
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
	setIdt(&idtp);
}


