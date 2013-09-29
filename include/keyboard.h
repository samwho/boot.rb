#pragma once

void keyboard_init();
uint32_t read_buffer(int len, char *out);
char *read_until_return();

#define fgets(s, size, stream) read_buffer(size, s)
int getchar();
