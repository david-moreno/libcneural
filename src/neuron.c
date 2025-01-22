#ifdef DEBUG
#include <stdio.h>
#endif /* DEBUG */

#include <stdlib.h>
#include <math.h>
#include "neuron.h"
#include "activation.h"
#include "error.h"

#define ALPHA_LEAKY 0.025

typedef struct input_t {
	float value;
	float weight;
} input_t;

typedef struct neuron_t {
	int input_num;
	input_t *input;
	void (*activation)(neuron_t *);
	float threshold;
	float bias;
	float sum;
	float a;    /* For ReLU leaky */
	float output;
} neuron_t;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Activation functions
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

static void act_step (neuron_t *neuron)
{
	if (neuron->sum < neuron->threshold) neuron->output = 0;
	neuron->output = 1;
}

static void act_linear (neuron_t *neuron)
{
	neuron->output = neuron->a * neuron->sum;
}

static void act_relu (neuron_t *neuron)
{
	neuron->output = (neuron->sum > 0) ? neuron->sum : 0;
}

/* TODO: Implement a way to modify default ALPHA_LEAKY value */
static void act_relu_leaky (neuron_t *neuron)
{
	neuron->output = (neuron->sum > 0) ? neuron->sum : neuron->a * neuron->sum;
}

static void act_relu_leaky_param (neuron_t *neuron)
{
	neuron->output = (neuron->sum > 0) ? neuron->sum : neuron->a * neuron->sum;
}

/* TODO: Concatenated ReLU (CReLU) */
/* TODO: Gaussian error linear unit (GELU) */
/* TODO: Sigmoid linear unit SiLU */
/* TODO: Softplus */
/* TODO: Exponential linear unit ELU */
/* TODO: Mish */
/* TODO: Squareplus */

static void act_sigmoid (neuron_t *neuron)
{
	neuron->output = 1.0 / (1.0 + powf(M_E, -neuron->sum));
}

static void act_tanh (neuron_t *neuron)
{
	float n, d;

	n = powf(M_E, neuron->sum) - powf(M_E, -neuron->sum);
	d = powf(M_E, neuron->sum) + powf(M_E, -neuron->sum);

	neuron->output = n / d;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * End of activation functions
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*! brief Sums all the inputs
 *
 *  Summation of the neuron inputs values considering
 *  its weights and neuron bias.
 *
 * return Sets neuron->sum
 */
static void sum (neuron_t *neuron)
{
	int i;
	float v, w;

	for (i=0; i < neuron->input_num; i++) {
		v = neuron->input[i].value;
		w = neuron->input[i].weight;
		neuron->sum += v * w;
	}

	neuron->sum += neuron->bias;
}

static input_t *inputs_new (int inp_num)
{
	input_t *inputs = calloc(inp_num, sizeof(input_t));
	if (inputs == NULL) return NULL;

	return inputs;
}

static void inputs_free (input_t *inputs)
{
	if (inputs != NULL) free(inputs);
}

static void (*set_activation (ACTIVATION type)) (neuron_t *)
{
	if (type == STEP) return &act_step;
	if (type == LINEAR) return &act_linear;
	if (type == RELU) return &act_relu;
	if (type == RELU_LEAKY) return &act_relu_leaky;
	if (type == RELU_PARAM) return &act_relu_leaky_param;
	if (type == SIGMOID) return &act_sigmoid;
	if (type == TANH) return &act_tanh;

	return NULL;
}

static int alloc_array_inputs (neuron_t *array, int num, int inp_num)
{
	int i, j;

	for (i=0; i < num; i++) {
		array[i].input = inputs_new(inp_num);

		if (array[i].input == NULL) {
			set_error(CN_ERR_NOMEM);
			for (j=0; j < i; j++) {
				if (array[j].input != NULL) free(array[j].input);
			}
			return 0;
		}

		array[i].input_num = inp_num;
	}

	return inp_num;
}

neuron_t *neurons_new (int num, int inp_num, ACTIVATION type)
{
	neuron_t *array;
	int i, r;

	array = calloc(num, sizeof(neuron_t));
	if (array == NULL) return NULL;

	for (i=0; i < num; i++) {
		array[i].activation = set_activation(type);
		array[i].threshold = 0;
		array[i].bias = 0;
		array[i].sum = 0;
		array[i].a = ALPHA_LEAKY;
		array[i].output = 0;
	}

	r = alloc_array_inputs(array, num, inp_num);
	if (r != inp_num) {
		set_error(CN_ERR_NOMEM);
		if (array != NULL) free(array);
		return NULL;
	}

	return array;
}

void neurons_free (neuron_t *array, int num)
{
	int i;

	for (i=0; i < num; i++) {
		if (array[i].input != NULL) inputs_free(array[i].input);
	}

	if (array != NULL) free(array);
}

float get_neuron_input_value (neuron_t *neurons, int neuron_i, int inp_i)
{
	return neurons[neuron_i].input[inp_i].value;
}

float get_neuron_input_weight (neuron_t *neurons, int neuron_i, int inp_i)
{
	return neurons[neuron_i].input[inp_i].weight;
}

float set_neuron_input_weight (neuron_t *neurons, int neuron_i, int inp_i, float weight)
{
	neurons[neuron_i].input[inp_i].weight = weight;
	return weight;
}
