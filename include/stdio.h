#ifndef STDIO_H
#define STDIO_H

#include <text.h>
#include <screen.h>
#include <keyboard.h>

// BEGIN CHEATING

#define stderr (-1)
#define stdin  (-1)
#define stdout (-1)

// Hack because all of boot.rb expects putc(c), but ruby expects putc(c, stream).
#define putc(c, ...) putc(c)

#define fputc(c, stream) putc(c)
#define fputs(s, stream) puts(s)
#define fprintf(stream, format, ...) printf(format, ##__VA_ARGS__)

typedef uint32_t FILE;

#define EOF (-1)

size_t fwrite(const void *ptr, size_t size, size_t nmemb,
                     FILE *stream);

// END CHEATING

#endif /* end of include guard: STDIO_H */
