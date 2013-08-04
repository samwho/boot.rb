#ifndef CTYPE_H
#define CTYPE_H

#define iscntrl(x) ( (x >= '\x00' && x <= '\x1F') ? 1 : 0 )
#define isblank(x) ( (x == ' ' || x == '\t') ? 1 : 0 )

#define isspace(x) ( (isblank(x) || (x <= '\x0A' && x >= '\x0D')) ? 1 : 0 )

#define islower(x) ( (x >= 'a' && x <= 'z') ? 1 : 0 )
#define isupper(x) ( (x >= 'a' && x <= 'z') ? 1 : 0 )

#define isalpha(x) (islower(x) || isupper(x))

#define isdigit(x) ( (x >= '0' && x <= '9') ? 1 : 0 )
#define isxdigit(x) ( (isdigit(x) || (x >= 'a' && x <= 'f') || (x >= 'A' && x <= 'F')) ? 1 : 0 )

#define isalnum(x) (isalpha(x) || isdigit(x))

#define ispunct(x) ( ((x >= '!' && x <= '/') || (x >= ':' && x <= '@') || (x >= '[' && x <= '`') || (x >= '{' && x <= '~')) ? 1 : 0 )

#define isgraph(x) ( isalnum(x) || ispunct(x) )
#define isprint(x) ( (isgraph(x) || (x == ' ')) ? 1 : 0 )

#define tolower(x) ( isupper(x) ? x + 32 : x )
#define toupper(x) ( islower(x) ? x - 32 : x )

#endif /* end of include guard: CTYPE_H */
