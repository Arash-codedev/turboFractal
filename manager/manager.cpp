#include "manager.hpp"
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread/thread.hpp> 
#include <stdexcept>
#include <thread>
#include <mutex>

Zone zone;
std::mutex plot_mutex;
RawPixel pixels_raw[screen_height][screen_width];
Color pixels_rendered[screen_height][screen_width];

Fractal_Function fractal_function = nullptr;
Colorizer_Function colorize_function = nullptr;
const double size_1=1.5;

void init()
{
	glViewport(0, 0, screen_width, screen_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, screen_width, 0, screen_height);
	glEnable(GL_MULTISAMPLE);
	glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
	RefreshFractal();
}

void onDisplay()
{
	std::lock_guard<std::mutex> guard(plot_mutex);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(screen_width, screen_height, GL_RGB, GL_FLOAT, pixels_rendered);
	glutSwapBuffers();
}

void print_coordinates()
{
	std::cout.precision(digits);
	std::cout<<"center ("<<zone.center_x<<", "<<zone.center_y<<") ";
	std::cout<<", window_size ("<<zone.window_size<<")";
	std::cout<<std::endl;
}

void keyPressed(unsigned char key, int /*x*/, int /*y*/)
{
	switch (key)
	{
		case 27: // Escape key
			exit(0);
			break;
		case '+':
			zone.window_size/=number(size_1);
			RefreshFractal();
			break;
		case '-':
			zone.window_size*=number(size_1);
			RefreshFractal();
			break;
		case '[':
			zone.window_size/=number(10);
			RefreshFractal();
			break;
		case ']':
			zone.window_size*=number(10);
			RefreshFractal();
			break;
		case '{':
			zone.window_size/=number(100);
			RefreshFractal();
			break;
		case '}':
			zone.window_size*=number(100);
			RefreshFractal();
			break;
		case '0':
			zone.window_size=number(1);
			RefreshFractal();
			break;
		case '9':
			zone.window_size=number(1e-40);
			RefreshFractal();
			break;
	}
	glutPostRedisplay();
}

void special_keyPressed(int key, int /*x*/, int /*y*/)
{
	switch (key)
	{
		case 27: // Escape key
			exit(0);
			break;
		case GLUT_KEY_UP:
			zone.center_y+=zone.get_height()/number(size_1);
			RefreshFractal();
			break;

		case GLUT_KEY_DOWN:
			zone.center_y-=zone.get_height()/number(size_1);
			RefreshFractal();
			break;

		case GLUT_KEY_LEFT:
			zone.center_x-=zone.get_width()/number(size_1);
			RefreshFractal();
			break;

		case GLUT_KEY_RIGHT:
			zone.center_x+=zone.get_width()/number(size_1);
			RefreshFractal();
			break;
	}
	glutPostRedisplay();
}

void onMouseButton(int button, int state, int x, int y)
{
	static bool mouse_pressed=false;
	if((state == GLUT_DOWN) != mouse_pressed)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			zone.center_x+=(number(x)/number(screen_width)-number(0.5))*zone.get_width();
			zone.center_y-=(number(y)/number(screen_height)-number(0.5))*zone.get_height();
			RefreshFractal();
		}
	}
	mouse_pressed=(state == GLUT_DOWN);
    glutPostRedisplay();
}

void show_fractal(int argc, char** argv)
{
	std::cout<<"Turbo Fractal"<<std::endl;
	std::cout<<"https://github.com/Arash-codedev/turboFractal"<<std::endl<<std::endl;
	
	glutInit(&argc, argv);
	glutInitWindowSize (screen_width, screen_height);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Turbo Fractal");

	init();
	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(special_keyPressed);
	glutMouseFunc(onMouseButton);
	glutDisplayFunc(onDisplay);
	glutMainLoop();
}

void plot_thread(
	const std::vector<PixelIndex> &indices_todo,
	bool *done, // when passing by reference, gcc faces with eror
	int max_iteration)
{
	fractal_function(zone,pixels_raw,indices_todo,max_iteration);
	colorize_function(pixels_raw,pixels_rendered,indices_todo);
	*done=true;
}

void RefreshFractal()
{
	if(fractal_function==nullptr)
		throw std::runtime_error("fractal_function is not assigned");
	if(colorize_function==nullptr)
		throw std::runtime_error("colorize_function is not assigned");

	static bool is_running=false;
	while(is_running)
	{
		boost::this_thread::sleep(boost::posix_time::milliseconds(100));
	}
	is_running=true;

	print_coordinates();
	std::cout<<"rendering..."<<std::endl;
	constexpr int N_groups=100;
	std::vector<std::vector<PixelIndex>> indices_list(N_groups);
	bool indices_done[N_groups];
	for(auto &v:indices_list)
		v.reserve(screen_height*screen_width*6/N_groups);
	for(bool &done:indices_done)
		done=false;

	for(int j=0;j<screen_height;j++)
		for(int i=0;i<screen_width;i++)
		{
			pixels_raw[j][i]={1.0f,1.0f,0};
			pixels_rendered[j][i]={0.0f,0.0f,0.0f};
			PixelIndex p;
			p.i=i;
			p.j=j;
			p.done=false;
			indices_list[rand()%N_groups].push_back(p);
		}
	std::vector<std::thread> workers;
	const int max_iteration=300;
	for(int i=0;i<N_groups;i++)
	{
		workers.push_back(std::thread(plot_thread,indices_list[i],&indices_done[i],max_iteration));
	}

	int last_done_count=-1;
	int done_count=0;
	do
	{
		done_count=0;
		for(bool &done:indices_done)
			if(done)
				done_count++;
		if(done_count!=last_done_count)
			onDisplay();
		last_done_count=done_count;
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	while(done_count<N_groups);

	for(std::thread &w:workers)
		w.join();
	onDisplay();
	std::cout<<"ready"<<std::endl;
	is_running=false;
}

