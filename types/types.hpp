#pragma once
#include <boost/multiprecision/gmp.hpp> // sudo apt-get install libgmp3-dev
#include <string>

constexpr int screen_width=640;
constexpr int screen_height=480;
constexpr int max_palettes = 100;
constexpr int digits=50;
typedef boost::multiprecision::number<boost::multiprecision::gmp_float<digits> > number;
typedef std::complex<number> complex;


struct Color
{
	float r;
	float g;
	float b;
};

struct RawPixel
{
	float x;
	float y;
	int count;
};

struct PixelIndex
{
	int j;
	int i;
	bool done;
};

struct Zone
{
	number center_x;
	number center_y;
	number window_size;

	Zone():
		center_x("0"),
		center_y("1"),
		window_size("1")
		// screen_width(640),
		// screen_height(480)
	{
	};

	number get_height() const
	{
		return window_size*sqrt(double(screen_height)/double(screen_width));
	}

	number get_width() const
	{
		return window_size*sqrt(double(screen_width)/double(screen_height));
	}

	// Zone(number center_x,number center_y,number window_size):
	// 	center_x(center_x), center_y(center_y), window_size(window_size)
	// {
	// }

	// Zone(std::string center_x,std::string center_y,std::string window_size):
	// 	center_x(center_x), center_y(center_y), fractal_width(window_size)
	// {
	// }

};
