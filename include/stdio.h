#ifndef STDIO_H
#define STDIO_H

#include <text.h>
#include <screen.h>

// BEGIN CHEATING

#define stderr (-1)
#define stdin  (-1)

#define fputc(c, stream) putc(c)
#define fputs(s, stream) puts(s)
#define fprintf(stream, format, ...) printf(format, ##__VA_ARGS__)

// END CHEATING

#endif /* end of include guard: STDIO_H */
