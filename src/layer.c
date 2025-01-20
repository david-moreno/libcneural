#ifdef DEBUG
#include <stdio.h>
#endif /* DEBUG */

#include <stdlib.h>
#include "layer.h"
#include "neuron.h"
#include "error.h"

typedef struct layer_t {
	int neuron_num, inp_num;
	neuron_t *neurons;
} layer_t;

layer_t *cn_layer_new (int neuron_num, int inp_num)
{
	layer_t *layer;

	layer = calloc(1, sizeof(layer_t));
	if (layer == NULL) {
		set_error(CN_ERR_NOMEM);
		return NULL;
	}

	layer->neuron_num = neuron_num;
	layer->inp_num = inp_num;
	layer->neurons = neurons_new(neuron_num, inp_num);

	return layer;
}

void cn_layer_free (layer_t *layer)
{
	neurons_free(layer->neurons, layer->neuron_num);
	if (layer != NULL) free(layer);
}

int get_neurons_num (layer_t *layer)
{
	return layer->neuron_num;
}

int get_inputs_num (layer_t *layer)
{
	return layer->inp_num;
}

neuron_t *get_neuron_array (layer_t *layer)
{
	return layer->neurons;
}

void debug_dump_layer (layer_t *layer)
{
	printf("%i neurons, %i inputs\n",
			layer->neuron_num, layer->inp_num);
}
