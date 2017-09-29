#include <types/complex.hpp>
#include "mandelbrot.hpp"
#include <iostream>

void mandelbrot(
	const Zone &zone,
	RawPixel pixels_raw[screen_height][screen_width],
	const std::vector<PixelIndex> &indices_todo,
	const int max_iteration)
{
	number fractal_width=zone.get_width();
	number fractal_height=zone.get_width();
	for(PixelIndex pix_idx:indices_todo)
	{
		int j=pix_idx.j;
		int i=pix_idx.i;
		number x0=zone.center_x-fractal_width/number(2.0)+number(i)*fractal_width/number(screen_width);
		number y0=zone.center_y-fractal_height/number(2.0)+number(j)*fractal_height/number(screen_height);
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
		pixels_raw[j][i].x=float(z.real());
		pixels_raw[j][i].y=float(z.imag());
		pixels_raw[j][i].count=count;
	}
}
