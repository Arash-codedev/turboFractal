#include "escape_time.hpp"

void escape_time(
	RawPixel pixels_index[screen_height][screen_width],
	Color pixels_rendered[screen_height][screen_width],
	const std::vector<PixelIndex> &indices_todo)
{
	std::vector<Color> palette={
		{0.0f,0.0f,0.0f},
		{0.2f,0.2f,0.1f},
		{0.1f,0.0f,0.1f},
		{0.0f,0.0f,0.2f},
		{0.0f,0.0f,0.3f},
		{0.0f,0.0f,0.4f},
		{0.0f,0.2f,0.5f},
		{0.1f,0.3f,0.7f},
		{0.2f,0.5f,0.8f},
		{0.5f,0.7f,0.9f},
		{0.8f,0.9f,1.0f},
		{0.9f,0.9f,0.7f},
		{1.0f,0.8f,0.4f},
		{1.0f,0.7f,0.0f},
		{0.8f,0.5f,0.0f},
		{0.6f,0.3f,0.0f},
		{0.4f,0.2f,0.0f}
	};

	for(PixelIndex pix_idx:indices_todo)
	{
		int j=pix_idx.j;
		int i=pix_idx.i;
		int index=pixels_index[j][i].count%int(palette.size());
		pixels_rendered[j][i].r = palette[index].r;
		pixels_rendered[j][i].g = palette[index].g;
		pixels_rendered[j][i].b = palette[index].b;
	}
}

