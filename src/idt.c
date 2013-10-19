#include <idt.h>
#include <isr.h>
#include <gdt.h>

// Defined in src/asmidt.s
extern void set_idt(struct idt_ptr *);

struct IDT idt[IDT_ENTRIES];

void idt_set_gate(int num, int offset, int selector, int type)
{
	idt[num].offset_low  = offset & 0xFFFF;
	idt[num].offset_high = offset >> 16 & 0xFFFF;
	idt[num].type_attr   = type;
	idt[num].selector    = selector;
}

/*
 * This function sets up all of the interrupt handlers in our system. It uses
 * assembly functions defined in the files src/asmirq.s and src/asmisr.s, which
 * in turn call a common interrupt handling stub defined in src/asmisr.s, which
 * in turn calls the C function isr_handler() defined src/isr.c.
 */
void idt_init()
{
	memset(&idt, 0, sizeof(struct IDT) * IDT_ENTRIES - 1);
	struct idt_ptr idtp;
	idtp.limit = sizeof(struct IDT) * IDT_ENTRIES - 1;
	idtp.offset = (uint32_t)&idt;

    /*
     * 32-bit Interrupt gate: 0x8E
     *   ( P=1, DPL=00b, S=0, type=1110b => * type_attr=1000_1110b=0x8E)
     *
     * More info: http://wiki.osdev.org/Interrupt_Descriptor_Table#Structure
     */
	idt_set_gate(0, (uint32_t)isr0, GDT_CODE, 0x8E);
	idt_set_gate(1, (uint32_t)isr1, GDT_CODE, 0x8E);
	idt_set_gate(2, (uint32_t)isr2, GDT_CODE, 0x8E);
	idt_set_gate(3, (uint32_t)isr3, GDT_CODE, 0x8E);
	idt_set_gate(4, (uint32_t)isr4, GDT_CODE, 0x8E);
	idt_set_gate(5, (uint32_t)isr5, GDT_CODE, 0x8E);
	idt_set_gate(6, (uint32_t)isr6, GDT_CODE, 0x8E);
	idt_set_gate(7, (uint32_t)isr7, GDT_CODE, 0x8E);
	idt_set_gate(8, (uint32_t)isr8, GDT_CODE, 0x8E);
	idt_set_gate(9, (uint32_t)isr9, GDT_CODE, 0x8E);
	idt_set_gate(10, (uint32_t)isr10, GDT_CODE, 0x8E);
	idt_set_gate(11, (uint32_t)isr11, GDT_CODE, 0x8E);
	idt_set_gate(12, (uint32_t)isr12, GDT_CODE, 0x8E);
	idt_set_gate(13, (uint32_t)isr13, GDT_CODE, 0x8E);
	idt_set_gate(14, (uint32_t)isr14, GDT_CODE, 0x8E);
	idt_set_gate(15, (uint32_t)isr15, GDT_CODE, 0x8E);
	idt_set_gate(16, (uint32_t)isr16, GDT_CODE, 0x8E);
	idt_set_gate(17, (uint32_t)isr17, GDT_CODE, 0x8E);
	idt_set_gate(18, (uint32_t)isr18, GDT_CODE, 0x8E);
	idt_set_gate(19, (uint32_t)isr19, GDT_CODE, 0x8E);
	idt_set_gate(20, (uint32_t)isr20, GDT_CODE, 0x8E);
	idt_set_gate(21, (uint32_t)isr21, GDT_CODE, 0x8E);
	idt_set_gate(22, (uint32_t)isr22, GDT_CODE, 0x8E);
	idt_set_gate(23, (uint32_t)isr23, GDT_CODE, 0x8E);
	idt_set_gate(24, (uint32_t)isr24, GDT_CODE, 0x8E);
	idt_set_gate(25, (uint32_t)isr25, GDT_CODE, 0x8E);
	idt_set_gate(26, (uint32_t)isr26, GDT_CODE, 0x8E);
	idt_set_gate(27, (uint32_t)isr27, GDT_CODE, 0x8E);
	idt_set_gate(28, (uint32_t)isr28, GDT_CODE, 0x8E);
	idt_set_gate(29, (uint32_t)isr29, GDT_CODE, 0x8E);
	idt_set_gate(30, (uint32_t)isr30, GDT_CODE, 0x8E);
	idt_set_gate(31, (uint32_t)isr31, GDT_CODE, 0x8E);

	remap_pic();

	idt_set_gate(32, (uint32_t)irq0, GDT_CODE, 0x8E);
	idt_set_gate(33, (uint32_t)irq1, GDT_CODE, 0x8E);
	idt_set_gate(34, (uint32_t)irq2, GDT_CODE, 0x8E);
	idt_set_gate(35, (uint32_t)irq3, GDT_CODE, 0x8E);
	idt_set_gate(36, (uint32_t)irq4, GDT_CODE, 0x8E);
	idt_set_gate(37, (uint32_t)irq5, GDT_CODE, 0x8E);
	idt_set_gate(38, (uint32_t)irq6, GDT_CODE, 0x8E);
	idt_set_gate(39, (uint32_t)irq7, GDT_CODE, 0x8E);
	idt_set_gate(40, (uint32_t)irq8, GDT_CODE, 0x8E);
	idt_set_gate(41, (uint32_t)irq9, GDT_CODE, 0x8E);
	idt_set_gate(42, (uint32_t)irq10, GDT_CODE, 0x8E);
	idt_set_gate(43, (uint32_t)irq11, GDT_CODE, 0x8E);
	idt_set_gate(44, (uint32_t)irq12, GDT_CODE, 0x8E);
	idt_set_gate(45, (uint32_t)irq13, GDT_CODE, 0x8E);
	idt_set_gate(46, (uint32_t)irq14, GDT_CODE, 0x8E);
	idt_set_gate(47, (uint32_t)irq15, GDT_CODE, 0x8E);
	set_idt(&idtp);
}
