#ifndef SIMPLE_PERCEPTRON
#define SIMPLE_PERCEPTRON
#include "Utils.h"

class Perceptron {
public:
	//The Perceptron stores its weights and learning constants.
	float* weights;
	int num_weights;
	float c = 0.01;

	Perceptron(int n) {
		weights = new float[n];
		num_weights = n;
		//Weights start off random.
		for (int i = 0; i < num_weights; i++) {
			weights[i] = RandomFloat(-1, 1);
		}
	}

	~Perceptron()
	{
		delete[] weights;
	}

	//Return an output based on inputs.
	int feedforward(float* inputs) {
		float sum = 0;
		for (int i = 0; i < num_weights; i++) {
			sum += inputs[i] * weights[i];
		}
		return activate(sum);
	}

	//Output is a + 1 or - 1.
	int activate(float sum) {
		if (sum > 0) return 1;
		else return -1;
	}

	//Train the network against known data.
	void train(float* inputs, int desired) {
		int guess = feedforward(inputs);
		float error = desired - guess;
		for (int i = 0; i < num_weights; i++) {
			weights[i] += c * error * inputs[i];
		}
	}
};


class Trainer {
public:
	//A "Trainer" object stores the inputs and the correct answer.
	float inputs[3];
	int answer;

	Trainer(float x, float y, int a) {
		//inputs = new float[3];
		inputs[0] = x;
		inputs[1] = y;
		//Note that the Trainer has the bias input built into its array.
		inputs[2] = 1;
		answer = a;
	}
};

#endif