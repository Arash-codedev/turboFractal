#pragma once
#include <boost/multiprecision/gmp.hpp> // sudo apt-get install libgmp3-dev
#include <string>

constexpr int screen_width=200;
constexpr int screen_height=200;
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



struct Zone
{
	number center_x;
	number center_y;
	number fractal_width;
	number fractal_height;

	Zone(){};
	Zone(number center_x,number center_y,number fractal_width,number fractal_height):
		center_x(center_x), center_y(center_y), fractal_width(fractal_width), fractal_height(fractal_height)
	{
	}

	Zone(std::string center_x,std::string center_y,std::string fractal_width,std::string fractal_height):
		center_x(center_x), center_y(center_y), fractal_width(fractal_width), fractal_height(fractal_height)
	{
	}

};
