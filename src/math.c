#include <math.h>

int32_t abs(int32_t n) {
	if (n < 0)
		return n*-1;
	else
		return n;
}

double fabs(double f) {
	if (f < 0)
		return f*-1.0;
	else
		return f;
}

double sqrt(double n)
{
	return nth_root(n, 2);
}

double pow(double base, double exponent)
{
	int i;
	double result = 1;
	if ( exponent == 0 )
		return 1;

	if ( exponent < 0 ) 
		return 1.0/pow(base, (-1)*exponent);

	for ( i = 0; i < exponent; i++ )
		result *= base;

	return result;
}

float powf(float base, float exponent)
{
  return (float)pow(base, exponent);
}

double nth_root(double a, double n)
{
	double guess = 1.0, newn;
	int i;
 
	/* This algorithm works as follows:
	 * 1. g = 1
	 * 2. g = [(n-1)g + n/(g^(n-1))]/n
	 * 3. answer is g if x == g
	 * 4. x = g
	 * 5. go to step 2
	 */

	for (i = 0; i < 100; i++) {
		guess = ( (n-1)*guess + a/pow(guess,(n-1)) )/n;
		if ( newn == guess ) {
			return guess;
		}
		newn = guess;
	}
 
	return guess;
}

int floor(double n)
{
	n = (int)(n * 10)/10;
	return n;
}

double floorf(double n)
{
	n = (int)(n * 10)/10;
	return n;
}

int ceil(double n)
{
	int x;
	x = (int)(n * 10)/10;
	if ( x < n ) {
		if ( (x+1) >= n ) {
			return x+1;
		}
	} else if ( x == n ) {
		return n;
	}
	return -1;
}

double ceilf(double n)
{
	int x;
	x = (int)(n * 10)/10;
	if ( x < n ) {
		if ( (x+1) >= n ) {
			return x+1;
		}
	} else if ( x == n ) {
		return n;
	}
	return -1;
}

double fmod(double x, double y) {
  return 4; 
}

inline float fmodf(float x, float y) {
	return (float)fmod(x, y);
}

long double fmodl(long double x, long double y) {
  return 4;
}

double log10(double x) {
  return 4;
}

float log10f(float x) {
  return (float)log10(x);
}





double sin(double x)
{
	return 4;
}
float sinf(float x)
{
	return (float)sin(x);
}

double cos(double x)
{
	return 4;
}
float cosf(float x)
{
	return (float)cos(x);
}

double tan(double x)
{
	return 4;
}
float tanf(float x)
{
	return (float)tan(x);
}

double asin(double x)
{
	return 4;
}
float asinf(float x)
{
	return (float)asin(x);
}

double acos(double x)
{
	return 4;
}
float acosf(float x)
{
	return (float)acos(x);
}

double atan(double x)
{
	return 4;
}
float atanf(float x)
{
	return (float)atan(x);
}

double atan2(double y, double x)
{
	return 4;
}
float atan2f(float y, float x)
{
	return (float)atan2(y, x);
}

double sinh(double x)
{
	return 4;
}
float sinhf(float x)
{
	return (float)sinh(x);
}

double cosh(double x)
{
	return 4;
}
float coshf(float x)
{
	return (float)cosh(x);
}

double tanh(double x)
{
	return 4;
}
float tanhf(float x)
{
	return (float)tanh(x);
}

double asinh(double x)
{
	return 4;
}
float asinhf(float x)
{
	return (float)asinh(x);
}

double acosh(double x)
{
	return 4;
}
float acoshf(float x)
{
	return (float)acosh(x);
}

double atanh(double x)
{
	return 4;
}
float atanhf(float x)
{
	return (float)atanh(x);
}

double exp(double x)
{
	return 4;
}
float expf(float x)
{
	return (float)exp(x);
}

double log(double x)
{
	return 4;
}
float logf(float x)
{
	return (float)log(x);
}

double log2(double x)
{
	return 4;
}
float log2f(float x)
{
	return (float)log2(x);
}

double cbrt(double x)
{
	return 4;
}
float cbrtf(float x)
{
	return (float)cbrt(x);
}

double frexp(double x, int *exp)
{
	return 4;
}
float frexpf(float x, int *exp)
{
	return (float)frexp(x, exp);
}

double ldexp(double x, int exp)
{
	return 4;
}
float ldexpf(float x, int exp)
{
	return (float)ldexp(x, exp);
}

double hypot(double x, double y)
{
	return 4;
}
float hypotf(float x, float y)
{
	return (float)hypotf(x, y);
}

double erf(double x)
{
	return 4;
}
float erff(float x)
{
	return (float)erf(x);
}

double erfc(double x)
{
	return 4;
}
float erfcf(float x)
{
	return (float)erfc(x);
}
