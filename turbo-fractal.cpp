#include <manager/manager.hpp>
#include <fractal/mandelbrot.hpp>
#include <fractal/fast_mandelbrot.hpp>
#include <colorize/escape_time.hpp>
#include <colorize/smooth.hpp>

int main(int argc, char** argv)
{
	fractal_function=mandelbrot;
	// fractal_function=fast_mandelbrot;
	colorize_function=escape_time;
	// colorize_function=smooth;
	show_fractal(argc,argv);
	return 0;
}
