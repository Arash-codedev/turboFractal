#pragma once
#include <types/types.hpp>

typedef std::function<void(const Zone &zone,RawPixel pixels_index[screen_height][screen_width],const std::vector<PixelIndex> &indices_todo,const int max_iteration)> Fractal_Function;
typedef std::function<void(RawPixel pixels_index[screen_height][screen_width],Color pixels_rendered[screen_height][screen_width],const std::vector<PixelIndex> &indices_todo)> Colorizer_Function;

extern Fractal_Function fractal_function;
extern Colorizer_Function colorize_function;
extern Zone zone;

void init();
void onDisplay();
void print_coordinates();
void keyPressed(unsigned char key, int /*x*/, int /*y*/);
void special_keyPressed(int key, int /*x*/, int /*y*/);
void onMouseButton(int button, int state, int x, int y);
void show_fractal(int argc, char** argv);
void RefreshFractal();
