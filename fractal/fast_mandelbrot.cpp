#include <types/complex.hpp>
#include "fast_mandelbrot.hpp"

void fast_mandelbrot(
	const Zone &zone,
	RawPixel pixels_raw[screen_height][screen_width],
	const std::vector<PixelIndex> &indices_todo,
	const int max_iteration)
{
	complex c=complex_of(zone.center_x,zone.center_y);
	complex z=complex_of(0.0,0.0);
	const std::complex<double> number2=complex_of_double(2.0,0.0);
	complex z_list[max_iteration];
	std::complex<double> z_list_double[max_iteration];
	int max_calculated=0;
	z_list[0]=z;
	z_list_double[0].real((double)z.real());
	z_list_double[0].imag((double)z.imag());
	z=z*z+c;

	double fractal_width=(double)zone.get_width();
	double fractal_height=(double)zone.get_width();

	for(PixelIndex pix_idx:indices_todo)
	{
		int j=pix_idx.j;
		int i=pix_idx.i;

		double dx=fractal_width*(-0.5+double(i)/double(screen_width));
		double dy=fractal_height*(-0.5+double(j)/double(screen_height));
		std::complex<double> epsilon0,epsilon;
		epsilon0.real(dx);
		epsilon0.imag(dy);
		epsilon.real(0);
		epsilon.imag(0);
		bool stop=false;
		for(int count=1;count<max_iteration && !stop;count++)
		{
			if(count>max_calculated)
			{
				z_list[count]=z;
				z_list_double[count].real((double)z.real());
				z_list_double[count].imag((double)z.imag());
				z=z*z+c;
				max_calculated++;
			}
			std::complex<double> &z_last=z_list_double[count-1];
			std::complex<double> &z=z_list_double[count];
			epsilon=number2*z_last*epsilon+epsilon*epsilon+epsilon0;
			std::complex<double> local_z=z+epsilon;
			pixels_raw[j][i].x=float(local_z.real());
			pixels_raw[j][i].y=float(local_z.imag());
			pixels_raw[j][i].count=count;
			if(std::norm(local_z)>=2.0*2.0)
				stop=true;
		}
	}
}
