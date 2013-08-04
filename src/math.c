#include <math.h>

uint32_t abs(uint32_t n) {
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
		return 1.0/powd(base, (-1)*exponent);

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
		guess = ( (n-1)*guess + a/powd(guess,(n-1)) )/n;
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
