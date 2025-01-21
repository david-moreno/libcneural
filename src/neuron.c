#ifdef DEBUG
#include <stdio.h>
#endif /* DEBUG */

#include <stdlib.h>
#include "neuron.h"
#include "error.h"

typedef struct input_t {
	float value;
	float weight;
} input_t;

typedef struct neuron_t {
	int input_num;
	input_t *input;
	float (*step)(neuron_t *);
	float threshold;
	float output;
} neuron_t;

static float sum (neuron_t *neuron)
{
	int i, inp_n = neuron->input_num;
	float v, w, s = 0;

	for (i=0; i < inp_n; i++) {
		v = neuron->input[i].value;
		w = neuron->input[i].weight;
		s += v*w;
	}

	return s;
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

neuron_t *neurons_new (int num, int inp_num)
{
	neuron_t *array;
	int i, r;

	array = calloc(num, sizeof(neuron_t));
	if (array == NULL) return NULL;

	for (i=0; i < num; i++) {
		array[i].step = NULL;
		array[i].threshold = 0;
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
