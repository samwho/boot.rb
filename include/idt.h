#pragma once
#pragma pack(1)
#include <misc.h>

#define IDT_ENTRIES 256

/*
 * For more details on this struct, go here:
 *
 *   http://wiki.osdev.org/Interrupt_Descriptor_Table#Structure
 */
struct IDT
{
	uint16_t offset_low;  // Offset bits 0..15
	uint16_t selector;    // A code segment selector in GDT or LDT
	uint8_t  zero;        // Unused
	uint8_t  type_attr;   // What type of gate this is
	uint16_t offset_high; // Offset bits 16..31
};

enum {
	IDT_TASK_GATE_32      = 0x5,
	IDT_INTERRUPT_GATE_16 = 0x6,
	IDT_TRAP_GATE_16      = 0x7,
	IDT_INTERRUPT_GATE_32 = 0xE,
	IDT_TRAP_GATE_32      = 0xF
};

struct idt_ptr {
	uint16_t limit;
	uint32_t offset;
};

void idt_set_gate(int num, int offset, int selector, int type);
void idt_init();

// Defined in src/asmisr.s
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr32();
