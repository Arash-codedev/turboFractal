#include "smooth.hpp"

float approx_smooth(float x,float ref)
{
	return float(exp(-std::abs(x-ref)*5.0));
}

#include <iostream>

void smooth(
	RawPixel pixels_index[screen_height][screen_width],
	Color pixels_rendered[screen_height][screen_width])
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
			double x=double(pixels_index[j][i].x);
			double y=double(pixels_index[j][i].y);
		
			double r2=x*x+y*y;
			double log_zn=log(r2)/2.0;
			double nu=log(log_zn/log(2))/log(2);
			float idx=float(pixels_index[j][i].count)-float(nu);
			int idx1=int(floor(idx)+0.1);
			idx1%=(int)palette.size();
			int idx2=(idx1+1)%(int)palette.size();
			float idx_rem=idx-float(floor(idx));
			const Color &c1=palette[idx1];
			const Color &c2=palette[idx2];
			pixels_rendered[j][i].r=(1.0f-idx_rem)*c1.r+idx_rem*c2.r;
			pixels_rendered[j][i].g=(1.0f-idx_rem)*c1.g+idx_rem*c2.g;
			pixels_rendered[j][i].b=(1.0f-idx_rem)*c1.b+idx_rem*c2.b;
		}
}

