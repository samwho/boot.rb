; Very simple bit of assembly code to set the interrupt descriptor table. It
; simply gets the first argument from the stack and calls lidt. More information
; can be found here:
;
;   http://wiki.osdev.org/Interrupt_Descriptor_Table#Loading.2FStoring

global set_idt
set_idt:
  push eax
  mov eax, [esp + 0x8]
  lidt [eax]
  pop eax
  ret
