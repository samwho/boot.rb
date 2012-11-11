global outb
global inb

;; void outb(uint16_t port, char val)
outb:
	push ebp
	mov ebp, esp
	mov dx, [ebp + 8]
	mov ax, [ebp + 12]
	out dx, ax
	leave
	ret
