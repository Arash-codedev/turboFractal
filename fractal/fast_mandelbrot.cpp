#include <types/complex.hpp>
#include "fast_mandelbrot.hpp"

struct Pixel
{
	int pixel_i, pixel_j;
	std::complex<double> epsilon0,epsilon;
	std::complex<double> z;
	int count;
};

bool not_all_negative(std::vector<int> v)
{
	for(int i:v)
		if(i>=0)
			return true;
	return false;
}

void fast_mandelbrot(const Zone &zone,RawPixel pixels_index[screen_height][screen_width])
{
	constexpr int max_iteration = 2000;
	std::vector<int> remained_pixels(screen_height*screen_width);
	std::iota(remained_pixels.begin(), remained_pixels.end(), 0); // assnign 0..n-1
	std::vector<Pixel> pixels(screen_height*screen_width);
	for(int j=0;j<screen_height;j++)
		for(int i=0;i<screen_width;i++)
		{
			int idx=j*screen_width+i;
			pixels[idx].pixel_i=i;
			pixels[idx].pixel_j=j;
			double dx=double(zone.fractal_width)*(-0.5+double(i)/double(screen_width));
			double dy=double(zone.fractal_height)*(-0.5+double(j)/double(screen_height));
			pixels[idx].epsilon0.real(dx);
			pixels[idx].epsilon0.imag(dy);
			pixels[idx].epsilon.real(0);
			pixels[idx].epsilon.imag(0);
			pixels[idx].count=0;
		}

	complex z0=complex_of(zone.center_x,zone.center_y);
	complex z=complex_of(0.0,0.0);
	const std::complex<double> number2=complex_of_double(2.0,0.0);

	int count = 0;
	while(count <= max_iteration && not_all_negative(remained_pixels))
	{
		complex last_z=z;
		z=z*z+z0;
		std::complex<double> z_double_last=complex_of_double(double(last_z.real()),double(last_z.imag()));
		std::complex<double> z_double=complex_of_double(double(z.real()),double(z.imag()));
		count++;

		for(long ii=0;ii<long(remained_pixels.size());ii++) // index of index
		{
			long i=remained_pixels[ii];
			if(i>=0)
			{
				std::complex<double> &epsilon=pixels[i].epsilon;
				std::complex<double> &epsilon0=pixels[i].epsilon0;
				pixels[i].epsilon=number2*z_double_last*epsilon+epsilon*epsilon+epsilon0;
				pixels[i].z=z_double;
				if(std::norm(pixels[i].z+pixels[i].epsilon)<2.0*2.0)
					pixels[i].count++;
				else
					remained_pixels[ii]=-1; // remove index
			}
		}
	}

	for(long ii=0;ii<long(remained_pixels.size());ii++) // index of index
	{
		long i=remained_pixels[ii];
		if(i>=0) // reached maximum iteration
		{
			pixels[i].count=0;
			// pixels[i].x=0.1f;
			// pixels[i].y=0.1f;
		}
	}

	for(const Pixel &p:pixels)
	{
		pixels_index[p.pixel_j][p.pixel_i].x=float(p.z.real()+p.epsilon.real());
		pixels_index[p.pixel_j][p.pixel_i].y=float(p.z.imag()+p.epsilon.imag());
		pixels_index[p.pixel_j][p.pixel_i].count=p.count;
	}
}
