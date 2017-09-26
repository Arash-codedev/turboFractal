#include <types/complex.hpp>
#include "mandelbrot.hpp"


void mandelbrot(const Zone &zone,RawPixel pixels_index[screen_height][screen_width])
{
	constexpr int max_iteration = 2000;

	for(int j=0;j<screen_height;j++)
		for(int i=0;i<screen_width;i++)
		{
			number x0=zone.center_x-zone.fractal_width/number(2.0)+number(i)*zone.fractal_width/number(screen_width);
			number y0=zone.center_y-zone.fractal_height/number(2.0)+number(j)*zone.fractal_height/number(screen_height);
			complex z0=complex_of(x0,y0);
			complex z=complex_of(0,0);
			int count = 0;
			while(std::norm(z)<2*2 && count <= max_iteration)
			{
				z=z*z+z0;
				count++;
			}
			if(count >= max_iteration)
				count=0;
			pixels_index[j][i].x=float(z.real());
			pixels_index[j][i].y=float(z.imag());
			pixels_index[j][i].count=count;
		}
}
