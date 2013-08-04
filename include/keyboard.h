#pragma once

void keyboardInit();
uint32_t readBuffer(int len, char *out); 
char *readUntilReturn();

#define fgets(s, size, stream) readBuffer(size, s)
int getchar();
