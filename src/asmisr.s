; From http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
%macro ISR_NOERRCODE 1
	[GLOBAL isr%1]
	isr%1:
		cli
		push byte 0  ; No error code, stub this value
		push byte %1 ; Push the interrupt number for later
		jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
	[GLOBAL isr%1]
	isr%1:
		cli
		push byte %1 ; Push the interrupt number for later, error code has
                     ; already been pushed for us
		jmp isr_common_stub
%endmacro

; For a descriptio of what each of these interrupt numbers mean, see
; include/isr.h
ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

extern isr_handler
global io_wait

isr_common_stub:
   pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov ax, ds               ; Lower 16-bits of eax = ds.
   push eax                 ; save the data segment descriptor

   mov ax, 0x10  ; 1oad the kernel data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   call isr_handler

   pop eax        ; re1oad the original data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   popa           ; Pops edi,esi,ebp...
   add esp, 8     ; C1eans up the pushed error code and pushed ISR number
   sti
   iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

io_wait:
   out 0x80, al ; Push a random byte to 0x80, which seems to be unused.
