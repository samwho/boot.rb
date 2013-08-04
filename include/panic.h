#ifndef STDLIB_H
#define STDLIB_H

#define __halt_with_message(format, ...) {   \
	printf(format, ##__VA_ARGS__); \
	while(1) __asm__("cli; hlt");  \
}

#define panic(format, ...) __halt_with_message("PANIC: " ## format, ##__VA_ARGS__)

#endif
