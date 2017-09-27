#include "manager.hpp"
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdexcept>

// Zone zone {
// "0.0",
// "1.0",
// "1e-300",
// "1e-300",
// };

Zone zone {
"-0.017129859053038708066553865791980737173456736280136",
"1.0066502118237216019272457126712419103917799980319",
"3.1913115432519800944242947387594453061954601850088e-60",
"3.1913115432519800944242947387594453061954601850088e-60"
};

RawPixel pixels_index[screen_height][screen_width];
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
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(screen_width, screen_height, GL_RGB, GL_FLOAT, pixels_rendered);
	glutSwapBuffers();
}

void print_coordinates()
{
	std::cout.precision(digits);
	std::cout<<"center ("<<zone.center_x<<", "<<zone.center_y<<") ";
	std::cout<<", window ("<<zone.fractal_width<<", "<<zone.fractal_height<<")";
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
			zone.fractal_width/=number(size_1);
			zone.fractal_height/=number(size_1);
			print_coordinates();
			std::cout<<"rendering..."<<std::endl;
			RefreshFractal();
			std::cout<<"ready"<<std::endl;
			break;
		case '-':
			zone.fractal_width*=number(size_1);
			zone.fractal_height*=number(size_1);
			print_coordinates();
			std::cout<<"rendering..."<<std::endl;
			RefreshFractal();
			std::cout<<"ready"<<std::endl;
			break;
		case '[':
			zone.fractal_width/=number(10);
			zone.fractal_height/=number(10);
			print_coordinates();
			std::cout<<"rendering..."<<std::endl;
			RefreshFractal();
			std::cout<<"ready"<<std::endl;
			break;
		case ']':
			zone.fractal_width*=number(10);
			zone.fractal_height*=number(10);
			print_coordinates();
			std::cout<<"rendering..."<<std::endl;
			RefreshFractal();
			std::cout<<"ready"<<std::endl;
			break;
		case '{':
			zone.fractal_width/=number(100);
			zone.fractal_height/=number(100);
			print_coordinates();
			std::cout<<"rendering..."<<std::endl;
			RefreshFractal();
			std::cout<<"ready"<<std::endl;
			break;
		case '}':
			zone.fractal_width*=number(100);
			zone.fractal_height*=number(100);
			print_coordinates();
			std::cout<<"rendering..."<<std::endl;
			RefreshFractal();
			std::cout<<"ready"<<std::endl;
			break;
		case '0':
			zone.fractal_width=number(1);
			zone.fractal_height=number(1);
			print_coordinates();
			std::cout<<"rendering..."<<std::endl;
			RefreshFractal();
			std::cout<<"ready"<<std::endl;
			break;
		case '9':
			zone.fractal_width=number(1e-40);
			zone.fractal_height=number(1e-40);
			print_coordinates();
			std::cout<<"rendering..."<<std::endl;
			RefreshFractal();
			std::cout<<"ready"<<std::endl;
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
			zone.center_y+=zone.fractal_height/number(size_1);
			print_coordinates();
			std::cout<<"rendering..."<<std::endl;
			RefreshFractal();
			std::cout<<"ready"<<std::endl;
			break;

		case GLUT_KEY_DOWN:
			zone.center_y-=zone.fractal_height/number(size_1);
			print_coordinates();
			std::cout<<"rendering..."<<std::endl;
			RefreshFractal();
			std::cout<<"ready"<<std::endl;
			break;

		case GLUT_KEY_LEFT:
			zone.center_x-=zone.fractal_width/number(size_1);
			print_coordinates();
			std::cout<<"rendering..."<<std::endl;
			RefreshFractal();
			std::cout<<"ready"<<std::endl;
			break;

		case GLUT_KEY_RIGHT:
			zone.center_x+=zone.fractal_width/number(size_1);
			print_coordinates();
			std::cout<<"rendering..."<<std::endl;
			RefreshFractal();
			std::cout<<"ready"<<std::endl;
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
			zone.center_x+=(number(x)/number(screen_width)-number(0.5))*number(zone.fractal_width);
			zone.center_y-=(number(y)/number(screen_height)-number(0.5))*number(zone.fractal_height);
			print_coordinates();
			std::cout<<"rendering..."<<std::endl;
			RefreshFractal();
			std::cout<<"ready"<<std::endl;
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


void RefreshFractal()
{
	if(fractal_function==nullptr)
		throw std::runtime_error("fractal_function is not assigned");
	if(colorize_function==nullptr)
		throw std::runtime_error("colorize_function is not assigned");

	fractal_function(zone,pixels_index);
	colorize_function(pixels_index,pixels_rendered);
}

