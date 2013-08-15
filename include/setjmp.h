#ifndef SETJMP_H
#define SETJMP_H

// Note that this is only correct for 32bit systems.
typedef int jmp_buf[6];

void longjmp(jmp_buf env, int val);
int setjmp(jmp_buf env);

#endif /* SETJMP_H */
