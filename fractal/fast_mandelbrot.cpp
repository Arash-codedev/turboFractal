#include <types/complex.hpp>
#include "fast_mandelbrot.hpp"

// struct Pixel
// {
// 	// int pixel_i, pixel_j;
// 	// std::complex<double> epsilon0,epsilon;
// 	std::complex<double> z;
// 	int count;
// };

void fast_mandelbrot(const Zone &zone,RawPixel pixels[screen_height][screen_width])
{
	constexpr int max_iteration = 2000;

	complex c=complex_of(zone.center_x,zone.center_y);
	complex z=complex_of(0.0,0.0);
	const std::complex<double> number2=complex_of_double(2.0,0.0);
	// Pixel pixels[screen_height][screen_width];
	complex z_list[max_iteration];
	std::complex<double> z_list_double[max_iteration];
	int max_calculated=0;
	z_list[0]=z;
	z_list_double[0].real((double)z.real());
	z_list_double[0].imag((double)z.imag());
	z=z*z+c;
	// for(int i=0;i<max_iteration;i++)
	// {
	// 	z_list[i]=z;
	// 	z_list_double[i].real((double)z.real());
	// 	z_list_double[i].imag((double)z.imag());
	// 	z=z*z+c;
	// }
	for(int j=0;j<screen_height;j++)
		for(int i=0;i<screen_width;i++)
		{
			double dx=double(zone.fractal_width)*(-0.5+double(i)/double(screen_width));
			double dy=double(zone.fractal_height)*(-0.5+double(j)/double(screen_height));
			std::complex<double> epsilon0,epsilon;
			epsilon0.real(dx);
			epsilon0.imag(dy);
			epsilon.real(0);
			epsilon.imag(0);
			// int count=0;
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
				pixels[j][i].x=float(local_z.real());
				pixels[j][i].y=float(local_z.imag());
				pixels[j][i].count=count;
				if(std::norm(local_z)>=2.0*2.0)
					stop=true;
			}

		}
}
