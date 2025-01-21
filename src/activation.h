#ifndef ACTIVATION_H
#define ACTIVATION_H

typedef enum {
	STEP,
	LINEAR,
	RELU,
	RELU_LEAKY,
	RELU_PARAM,
	SIGMOID,
	TANH
} ACTIVATION;

float (*dispatcher (ACTIVATION type)) (float, float, float);

#endif /* ACTIVATION_H */
