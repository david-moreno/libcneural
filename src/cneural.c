#ifdef DEBUG
#include <stdio.h>
#endif /* DEBUG */

#include <stdlib.h>
#include "cneural.h"
#include "layer.h"
#include "graph.h"
#include "error.h"

#define MIN_LAYNUM 2
#define MIN_INPNUM 1
#define MIN_OUTNUM 1
#define MIN_NEURONNUM 1

typedef enum {CN_FALSE, CN_TRUE} truth_t;

typedef struct layer_info_t {
	int neuron_num;
	int inp_num;
} layer_info_t;

typedef struct cneural_t {
	truth_t built;
	int lay_num, inp_num, out_num;
	layer_info_t *layer_info;
	layer_t **layer;
} cneural_t;

static inline CN_ERROR_T check_param (int lay_num, int inp_num, int out_num)
{
	if (lay_num < MIN_LAYNUM) return CN_ERR_LAYNUM;
	if (inp_num < MIN_INPNUM) return CN_ERR_INPNUM;
	if (out_num < MIN_OUTNUM) return CN_ERR_OUTNUM;

	return CN_ERR_OK;
}

static int set_layer_info (cneural_t *network)
{
	int lay_num, inp_num, out_num, neuron_num, prev_inp_num, i;
	layer_info_t *layer_info;

	lay_num = network->lay_num - 1;
	inp_num = network->inp_num;
	out_num = network->out_num;
	layer_info = network->layer_info;

	neuron_num = (inp_num >= out_num) ? inp_num : out_num;
	if (neuron_num < MIN_NEURONNUM) {
		set_error(CN_ERR_NEURONNUM);
		return -1;
	}

	layer_info[0].neuron_num = inp_num;
	layer_info[0].inp_num = 1;
	prev_inp_num = inp_num;

	for (i=1; i < lay_num; i++) {
		layer_info[i].neuron_num = neuron_num;
		layer_info[i].inp_num = prev_inp_num;
		prev_inp_num = neuron_num;
	}

	layer_info[i].neuron_num = out_num;
	layer_info[i].inp_num = prev_inp_num;

	return network->lay_num;
}

cneural_t *cn_network_new (int lay_num, int inp_num, int out_num)
{
	cneural_t *network;
	CN_ERROR_T param_err;
	int r;

	param_err = check_param(lay_num, inp_num, out_num);
	if (param_err != CN_ERR_OK) {
		set_error(param_err);
		return NULL;
	}

	network = calloc(1, sizeof(cneural_t));
	if (network == NULL) {
		set_error(CN_ERR_NOMEM);
		return NULL;
	}

	network->layer_info = calloc(lay_num, sizeof(layer_info_t));
	if (network->layer_info == NULL) {
		if (network != NULL) free(network);
		set_error(CN_ERR_NOMEM);
		return NULL;
	}

	network->built = CN_FALSE;
	network->lay_num = lay_num;
	network->inp_num = inp_num;
	network->out_num = out_num;

	r = set_layer_info(network);
	if (r != lay_num) {
		set_error(CN_ERR_NOMEM);
		if (network->layer_info != NULL) free(network->layer_info);
		if (network != NULL) free(network);
		return NULL;
	}

	return network;
}

static layer_t **alloc_layers (cneural_t *network)
{
	int i, j, lay_num, neuron_num, inp_num;
	layer_t **layer;

	layer = calloc(network->lay_num, sizeof(layer_t *));
	if (layer == NULL) {
		set_error(CN_ERR_NOMEM);
		return NULL;
	}

	lay_num = network->lay_num;
	for (i=0; i < lay_num; i++) {
		neuron_num = network->layer_info[i].neuron_num;
		inp_num = network->layer_info[i].inp_num;

		layer[i] = cn_layer_new(neuron_num, inp_num);
		if (layer[i] == NULL) {
			set_error(CN_ERR_NOMEM);
			for (j=0; j < i; j++) {
				if (layer[j] != NULL) free(layer[j]);
			}
			return NULL;
		}
	}

	return layer;
}

int cn_build_network (cneural_t *network)
{
	if (network->built == CN_TRUE) {
		set_error(CN_ERR_BUILT);
		return -1;
	}

	network->layer = alloc_layers(network);
	if (network->layer == NULL) {
		set_error(CN_ERR_NOMEM);
		if (network != NULL) free(network);
		return -1;
	}

	network->built = CN_TRUE;

	return network->lay_num;
}

void cn_network_free (cneural_t *network)
{
	int i;

	if (network->built == CN_TRUE) {
		for (i=0; i < network->lay_num; i++) {
			if (network->layer[i] != NULL) {
				cn_layer_free(network->layer[i]);
			}
		}

		if (network->layer != NULL) free(network->layer);
	}

	if (network->layer_info != NULL) free(network->layer_info);
	if (network != NULL) free(network);
}

int cn_set_layer_size (cneural_t *network, int index, int size)
{
	int last_layer, next;

	if (network->built == CN_TRUE) {
		set_error(CN_ERR_BUILT);
		return -1;
	}

	if ((index < 0) || (index >= network->lay_num)) {
		set_error(CN_ERR_OUTBOUND);
		return -1;
	}

	if (size < MIN_NEURONNUM) {
		set_error(CN_ERR_NEURONNUM);
		return -1;
	}

	network->layer_info[index].neuron_num = size;
	last_layer = network->lay_num - 1;
	if (index < last_layer) {
		next = index + 1;
		network->layer_info[next].inp_num = size;
	}

	return size;
}

int cn_graph_network (cneural_t *network, const char *fname)
{
	FILE *fp;
	int r;

	fp = fopen(fname, "w");
	if (fp == NULL) {
		set_error(CN_ERR_OPENFILE);
		return -1;
	}

	r = graph_network(network, fp);
	fclose(fp);

	return r; 
}

int cn_get_layers_num (cneural_t *network)
{
	return network->lay_num;
}

int cn_get_layer_neuron_num (cneural_t *network, int layer)
{
	return network->layer_info[layer].neuron_num;
}

float cn_get_neuron_input_value (cneural_t *network, int layer_i, int neuron_i, int input_i)
{
	neuron_t *neurons;
	int layer_num, neuron_num, input_num;

	layer_num = network->lay_num;
	neuron_num = network->layer_info[layer_i].neuron_num;
	input_num = network->layer_info[layer_i].inp_num;

	if (layer_i < 0) return -1.0;
	if (layer_i >= layer_num) return 1.0;

	if (neuron_i < 0) return -2.0;
	if (neuron_i >= neuron_num) return 2.0;

	if (input_i < 0) return -3.0;
	if (input_i >= input_num) return 3.0;

	neurons = get_neuron_array(network->layer[layer_i]);
	return get_neuron_input_value(neurons, neuron_i, input_i);
}

float cn_get_neuron_input_weight (cneural_t *network, int layer_i, int neuron_i, int input_i)
{
	neuron_t *neurons;
	int layer_num, neuron_num, input_num;

	layer_num = network->lay_num;
	neuron_num = network->layer_info[layer_i].neuron_num;
	input_num = network->layer_info[layer_i].inp_num;

	if (layer_i < 0) return -1.0;
	if (layer_i >= layer_num) return 1.0;

	if (neuron_i < 0) return -2.0;
	if (neuron_i >= neuron_num) return 2.0;

	if (input_i < 0) return -3.0;
	if (input_i >= input_num) return 3.0;

	neurons = get_neuron_array(network->layer[layer_i]);
	return get_neuron_input_weight(neurons, neuron_i, input_i);
}

/* Error codes. */
char *cn_get_error_msg (void)
{
	return get_error_msg();
}

/* DEBUG */
void debug_dump_network (cneural_t *network)
{
	int layer_num, l;

	layer_num = network->lay_num;
	for (l=0; l < layer_num; l++) {
		printf("[%i]  ", l);
		debug_dump_layer(network->layer[l]);
	}
}

/* DEBUG */
void debug_dump_layer_info (cneural_t *network)
{
	int lay_num, neuron_num, inp_num, l;

	lay_num = network->lay_num;
	for (l=0; l < lay_num; l++) {
		neuron_num = network->layer_info[l].neuron_num;
		inp_num = network->layer_info[l].inp_num;
		printf("* [%i]  ", l);
		printf("%i neurons, %i inputs\n",
				neuron_num, inp_num);
	}
}
