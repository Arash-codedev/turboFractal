#include "escape_time.hpp"

float approx_et(float x,float ref)
{
	return float(exp(-std::abs(x-ref)*5.0));
}

void escape_time(RawPixel pixels_index[screen_height][screen_width],Color pixels_rendered[screen_height][screen_width])
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

	for(int j=0;j<screen_height;j++)
		for(int i=0;i<screen_width;i++)
		{
			int index=pixels_index[j][i].count%int(palette.size());
			pixels_rendered[j][i].r = palette[index].r;
			pixels_rendered[j][i].g = palette[index].g;
			pixels_rendered[j][i].b = palette[index].b;

		}
}

