#ifndef STDDEF_H
#define STDDEF_H

#ifdef __x86_64
	// 8 bytes for 64bit
	typedef unsigned long int size_t;
  typedef long int intptr_t;
#else
	// 4 bytes for 32bit
	typedef unsigned int size_t;
  typedef int intptr_t;
#endif

typedef size_t uintptr_t;
typedef size_t ptrdiff_t; // No clue if this is right.

#include <stdlib.h> // Is this right? I don't even care.

#endif /* end of include guard: STDDEF_H */
