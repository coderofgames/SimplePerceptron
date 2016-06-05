#ifndef SIMMPLE_EXAMPLE_H
#define SIMPLE_EXAMPLE_H

#include "SimplePerceptron.h"
#include "Utils.h"
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h


class SimpleExample
{
protected:
	bool m_bDeleted = false;
public:

	SimpleExample(){}
	~SimpleExample(){
		if (m_bDeleted == false)
			this->Delete();
	}

	virtual void Initialize(){}
	virtual void Draw(){};
	virtual void Delete(){};
	virtual void keyboard(unsigned char key, int x, int y){};
	virtual void keyboardup(unsigned char key, int x, int y){};
	virtual void Special(int key, int x, int y){};
	virtual void reshape(GLsizei width, GLsizei height){}
	virtual void mouse(int button, int state, int x, int y){}
};



class SimplePerceptronExample :public SimpleExample
{
public:
	Perceptron *ptron=0;
	//2, 000 training points
	int num_training_points = 2000;
	Trainer** training;// = new Trainer*[num_training_points];
	int width = 640;
	int height = 640;
	int count = 0;

	int num_perceptron_weights = 3;

	// accessors
	void SetNumTrainingPoints(int n){
		num_training_points = n;
	}

	void SetViewport(int w, int h)
	{
		width = w;
		height = h;
	}

	void SetNumPerceptronWeights(int n){
		num_perceptron_weights = n;
	}

	//The formula for a line
	float f(float x) {
		return 2 * x + 1;
	}

	SimplePerceptronExample(){}
	~SimplePerceptronExample(){
	}

	void Initialize()
	{

		training = new Trainer*[num_training_points];

		ptron = new Perceptron(num_perceptron_weights);

		//Make 2, 000 training points.
		for (int i = 0; i < num_training_points; i++) {
			float x = RandomFloat(-width / 2, width / 2);
			float y = RandomFloat(-height / 2, height / 2);
			//Is the correct answer 1 or - 1 ?
			int answer = 1;
			if (y < f(x)) answer = -1;
			training[i] = new Trainer(x, y, answer);
		}

		m_bDeleted = false;
	}
	
	void Draw(){
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		count = (count + 1) % num_training_points;
		ptron->train(training[count]->inputs, training[count]->answer);
		for (int i = 0; i < count; i++) {
			//stroke(0);
			int guess = ptron->feedforward(training[i]->inputs);
			//Show the classification—no fill for - 1, black for + 1.
			float val = 0.015f;
			float offsetX = 1.8* training[i]->inputs[0] / width;
			float offsetY = 1.8*training[i]->inputs[1] / height;


			glBegin(GL_QUADS);
			if (guess > 0) glColor3f(1.0f, 0.0f, 0.0f); //std::cout << "guess >0" << std::endl;//noFill();
			else           glColor3f(0.0f, 1.0f, 0.0f);// std::cout << "guess <=0" << std::endl;

			// Each set of 4 vertices form a quad
			// Red
			//glPushMatrix();
			//glTranslatef(training[i]->inputs[0] , training[i]->inputs[1] , 0.0f);
			glVertex2f(-val + offsetX, -val + offsetY);    // x, y
			glVertex2f(val + offsetX, -val + offsetY);
			glVertex2f(val + offsetX, val + offsetY);
			glVertex2f(-val + offsetX, val + offsetY);
			glEnd();
			//glPopMatrix();
			//ellipse(training[i].inputs[0], training[i].inputs[1], 8, 8);

		}
		glutSwapBuffers();
	}

	void keyboard(unsigned char key, int x, int y){}
	void keyboardup(unsigned char key, int x, int y){}
	void Special(int key, int x, int y){};
	void reshape(GLsizei width, GLsizei height){}
	void mouse(int button, int state, int x, int y){}

	void Delete(){
		for (int i = 0; i < num_training_points; i++)
		{
			delete training[i];
		}
		delete[] training;

		delete ptron;

		m_bDeleted = true;
	}



};

#endif