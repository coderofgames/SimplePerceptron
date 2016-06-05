// SimplePerceptron.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include <iostream>

#include "SimpleExample.h"
#include "SimplePerceptron.h"


#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

#include "Utils.h"



SimpleExample *example;

int width = 640;
int height = 480;




void cleanup()
{
	example->Delete();
}


void setup() {
	example = new  SimplePerceptronExample();
}


void draw() {		
	example->Draw();
}

/* Handler for window re-size event. Called back when the window first appears and
whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
	// Compute aspect ratio of the new window
	example->reshape(width, height);
}

void display() {
	draw();
}


void mouse(int button, int state, int x, int y)
{
	example->mouse(button, state, x, y);
}


void keyboard(unsigned char key, int x, int y)
{
	example->keyboard(key, x, y);
}

void keyboardup(unsigned char key, int x, int y)
{
	example->keyboardup(key, x, y);
}

void special(int key, int x, int y) {

	example->Special(key, x, y);
}

int init_resources(void)
{
	example->Initialize();

	return 1;
}











int _tmain(int argc, char* argv[])
{

	cout << "**************************************************************" << endl;



	setup();

	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(width, height);   // Set the window's initial width & height
	glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
	
	glutInitWindowPosition(640, 480); // Position the window's initial top-left corner
	glutReshapeFunc(reshape);       // Register callback handler for window re-size event
	//glutDisplayFunc(display); // Register display callback handler for window re-paint

	/* Extension wrangler initialising */
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
	{
		printf( "Error: %s\n", glewGetErrorString(glew_status));
		return EXIT_FAILURE;
	}

	if (!GLEW_VERSION_2_0) {
		printf( "No support for OpenGL 2.0 found\n");
		return 1;
	}

	GLint max_units;

	glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &max_units);
	if (max_units < 1) {
		printf( "Your GPU does not have any vertex texture image units\n");
		return 1;
	}

	printf("Perceptron Classifier\n");

	/* When all init functions run without errors,
	the program can initialise the resources */
	if (init_resources())
	{
		/* We can display it if everything goes OK */
		glutDisplayFunc(display);
		glutKeyboardFunc(keyboard);
		glutKeyboardUpFunc(keyboardup); 
		glutIdleFunc(display);

		glutSpecialFunc(special);
		glutMouseFunc(mouse);
		
		glutMainLoop();
	}
	//glutMainLoop();           // Enter the event-processing loop

	cleanup();
	

	return 0;
}

