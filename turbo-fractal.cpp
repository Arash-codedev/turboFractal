#include <manager/manager.hpp>
#include <fractal/mandelbrot.hpp>
#include <fractal/fast_mandelbrot.hpp>
#include <colorize/escape_time.hpp>
#include <colorize/smooth.hpp>
#include <colorize/last_angle.hpp>

int main(int argc, char** argv)
{
	zone.center_x=number("-0.017129859053038708066553865791980737173456736280136");
	zone.center_y=number("1.0066502118237216019272457126712419103917799980319");
	zone.window_size=number("1");

	// fractal_function=mandelbrot;
	fractal_function=fast_mandelbrot;
	colorize_function=escape_time;
	// colorize_function=smooth;
	// colorize_function=last_angle;
	show_fractal(argc,argv);
	return 0;
}
