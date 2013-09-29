global set_idt
set_idt:
 push eax
 mov eax, [esp + 0x8]
 lidt [eax]
 pop eax
 ret
