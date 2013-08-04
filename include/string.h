#ifndef STRING_H
#define STRING_H

int strcmp(char *a, char *b);
int strlen(char *str);
char *substr(char *str, int len);

const char* begin(const char* str);
const char* end(const char* str);

#endif /* STRING_H */
