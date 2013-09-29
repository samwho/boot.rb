#include <misc.h>
#pragma once
#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

#define PIC1         0x20
#define PIC2         0xA0
#define PIC1_COMMAND 0x20
#define PIC2_COMMAND 0xA0
#define PIC1_DATA    0x21
#define PIC2_DATA    0xA1
#define PIC_EOI      0x20
#define PIC_INIT     0x11

#pragma pack(1)

typedef struct registers
{
   uint32_t ds;                  // Data segment selector
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
   uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;

typedef enum {
    I_DIV0ERROR        = 0,
    I_DEBUGEXCEPTION   = 1,
    I_NONMASKABLE      = 2,
    I_BREAKPOINT       = 3,
    I_IDOVERFLOW       = 4,
    I_OUTOFBOUNDS      = 5,
    I_INVALIDOP        = 6,
    I_NOCOPROCESSOR    = 7,
    I_DOUBLEFAULT      = 8,
    I_COSEGMENTOVERRUN = 9,
    I_BADTSS           = 10,
    I_SEGNOTPRESENT    = 11,
    I_STACKSEGFAULT    = 12,
    I_GENPROTFAULT     = 13,
    I_PAGEFAULT        = 14,
    I_UNKNOWN          = 15,
    I_COPROCESSORFAULT = 16,
    I_ALIGNMENTCHECK   = 17,
    I_MACHINECHECK     = 18,
    I_TIMER            = 32,
    I_KEYBOARD         = 33,
} interrupt_t;

typedef void (*isr_t)();
void register_interrupt_handler(uint8_t n, isr_t handler);
void print_isrs();

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

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void remap_pic();
void timercallback(registers_t regs);
void isr_init(void);
