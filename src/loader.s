global loader
global magic
global mbd

global set_gdt
global reloadSegments
global hang

extern kmain

; Multiboot header
;
; More information:
;   https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#OS-image-format
MODULEALIGN equ 1 << 0
MEMINFO		equ 1 << 1
FLAGS		equ MODULEALIGN | MEMINFO
MAGIC		equ 0x1BADB002
CHECKSUM	equ -(MAGIC+FLAGS)

section .mboot

align 4
	dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .text

STACKSIZE equ 0x4000 ; 16k

loader:
	mov esp, stack+STACKSIZE
	mov [magic], eax
	mov [mbd], ebx

	call kmain

	cli

	dd 0

set_gdt:
	push eax
	mov eax, [esp + 0x8]
	lgdt [eax]
	pop eax
	jmp 0x08:.reload_CS
.reload_CS:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret

hang:
	hlt
	jmp hang

section .bss

align 4
stack: resb STACKSIZE
magic: resd 1
mbd: resd 1
