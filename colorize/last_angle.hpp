#pragma once
#include <types/types.hpp>

void last_angle(
	RawPixel pixels_index[screen_height][screen_width],
	Color pixels_rendered[screen_height][screen_width],
	const std::vector<PixelIndex> &indices_todo);
