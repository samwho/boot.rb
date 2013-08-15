; Based on FreeBSD's lib/libc/i386/gen/_setjmp.S.

[GLOBAL setjmp]
[GLOBAL longjmp]

setjmp:
  mov eax, [4 + esp]   ; env
  mov edx, [0 + esp]   ; return address

  mov [0  + eax], edx  ; return address
  mov [4  + eax], ebx
  mov [8  + eax], esp
  mov [12 + eax], ebp
  mov [16 + eax], esi
  mov [20 + eax], edi

  xor  eax, eax
  ret

longjmp:
  mov edx, [4 + esp]  ; env
  mov eax, [8 + esp]  ; return value

  mov ecx, [0 + edx]  ; return address
  mov ebx, [4 + edx]
  mov esp, [8 + edx]
  mov ebp, [12 + edx]
  mov esi, [16 + edx]
  mov edi, [20 + edx]

  mov ecx, [0 + esp]  ; overwrite return address
  ret

