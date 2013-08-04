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



double sin(double x);
float sinf(float x);

double cos(double x);
float cosf(float x);

double tan(double x);
float tanf(float x);

double asin(double x);
float asinf(float x);

double acos(double x);
float acosf(float x);

double atan(double x);
float atanf(float x);

double atan2(double y, double x);
float atan2f(float y, float x);

double sinh(double x);
float sinhf(float x);

double cosh(double x);
float coshf(float x);

double tanh(double x);
float tanhf(float x);

double asinh(double x);
float asinhf(float x);

double acosh(double x);
float acoshf(float x);

double atanh(double x);
float atanhf(float x);

double exp(double x);
float expf(float x);

double log(double x);
float logf(float x);

double log2(double x);
float log2f(float x);

double cbrt(double x);
float cbrtf(float x);

double frexp(double x, int *exp);
float frexpf(float x, int *exp);

double ldexp(double x, int exp);
float ldexpf(float x, int exp);

double hypot(double x, double y);
float hypotf(float x, float y);

double erf(double x);
float erff(float x);

double erfc(double x);
float erfcf(float x);

#endif
