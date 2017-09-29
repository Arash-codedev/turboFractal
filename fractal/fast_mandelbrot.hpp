#pragma once
#include <types/types.hpp>

void fast_mandelbrot(
	const Zone &zone,
	RawPixel pixels_raw[screen_height][screen_width],
	const std::vector<PixelIndex> &indices_todo,
	const int max_iteration);


