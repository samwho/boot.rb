#ifndef ERRNO_H
#define ERRNO_H

#include <stdint.h>

#define EDOM   0
#define ERANGE 1
#define EILSEQ 2

static uint32_t errno = 0;

#endif /* end of include guard: ERRNO_H */
