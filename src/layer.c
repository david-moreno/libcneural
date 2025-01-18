#ifdef DEBUG
#include <stdio.h>
#endif /* DEBUG */

#include <stdlib.h>
#include "layer.h"
#include "neuron.h"
#include "error.h"

typedef struct layer_t {
	int neuron_num;
	neuron_t *neuron;
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
	layer->neuron = neurons_new(neuron_num, inp_num);

	return layer;
}

void cn_layer_free (layer_t *layer)
{
	neurons_free(layer->neuron, layer->neuron_num);
	if (layer != NULL) free(layer);
}

#ifdef DEBUG
void print_layer (layer_t *layer, int index)
{
	printf("\tLayer %i\n", index);
	printf("\t* Neuron num: %i\n", layer->neuron_num);
}
#endif /* DEBUG */
