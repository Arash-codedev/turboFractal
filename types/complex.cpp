#include "complex.hpp"

complex complex_of(number x,number y)
{
	complex z;
	z.real(x);
	z.imag(y);
	return z;
}

std::complex<double> complex_of_double(double x,double y)
{
	std::complex<double> z;
	z.real(x);
	z.imag(y);
	return z;
}

complex img_unit()
{
	complex i;
	i.real(0);
	i.imag(1);
	return i;
}
