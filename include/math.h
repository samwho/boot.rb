#ifndef MATH_H
#define MATH_H

#include <stdint.h>

int32_t abs(int32_t);
double fabs(double);
double sqrt(double);
int floor(double n);
double floorf(double n);
int ceil(double n);
double ceilf(double n);

double pow(double, double);
float powf(float, float);
double nth_root(double, double);

double fmod(double x, double y);
float fmodf(float x, float y);
long double fmodl(long double x, long double y);

double log10(double x);
float log10f(float x);
//long double log10l(long double x);

#define INFINITY  (__builtin_inff())
#define NAN       (__builtin_nanf (""))

/*
#define fpclassify(x) \
  (sizeof (x) == sizeof (float)					      \
   ? __fpclassifyf (x)						      \
   : sizeof (x) == sizeof (double)					      \
     ? __fpclassify (x) : __fpclassifyl (x))
*/
#define fpclassify(x) _Generic((X), long double: 1, \
                                    double: 1,      \
                                    float: 1,       \
                                    default: 0)


#define isnan(x) (x == NAN ? 1 : 0)
#define isinf(x) (x == INFINITY ? 1 : 0)

#endif
