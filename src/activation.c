#include <math.h>
#include "activation.h"

//#define ALPHA_LEAKY 3.981072
#define ALPHA_LEAKY 0.025

float step (float sum, float threshold, float a)
{
	if (sum < threshold) return 0;
	return 1;
}

float linear (float sum, float threshold, float a)
{
	return a * sum;
}

float relu (float sum, float threshold, float a)
{
	if (sum > 0) return sum;
	return 0;
}

float relu_leaky (float sum, float threshold, float a)
{
	if (sum > 0) return sum;
	return ALPHA_LEAKY * sum;
}

float relu_leaky_param (float sum, float threshold, float a)
{
	if (sum > 0) return sum;
	return a * sum;
}

/* TODO: Concatenated ReLU (CReLU) */
/* TODO: Gaussian error linear unit (GELU) */
/* TODO: Sigmoid linear unit SiLU */
/* TODO: Softplus */
/* TODO: Exponential linear unit ELU */
/* TODO: Mish */
/* TODO: Squareplus */

float sigmoid (float sum, float threshold, float a)
{
	1.0 / (1.0 + powf(M_E, -sum));
}

float tanh (float sum, float threshold, float a)
{
	return sum;
}

float (*dispatcher (ACTIVATION type)) (float, float, float)
{
	if (type == STEP) return &step;
	if (type == LINEAR) return &linear;
	if (type == RELU) return &relu;
	if (type == RELU_LEAKY) return &relu_leaky;
	if (type == RELU_PARAM) return &relu_leaky;
	if (type == SIGMOID) return &sigmoid;
	if (type == TANH) return &tanh;

	return NULL;
}
