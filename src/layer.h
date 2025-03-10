#ifndef LAYER_H
#define LAYER_H

#include "neuron.h"

typedef struct layer_t layer_t;

layer_t *cn_layer_new (int neuron_num, int inp_num, ACTIVATION type);
void cn_layer_free (layer_t *layer);
int get_neurons_num (layer_t *layer);
int get_inputs_num (layer_t *layer);
neuron_t *get_neuron_array (layer_t *layer);

/* DEBUG */
void debug_dump_layer (layer_t *layer);

#endif /* LAYER_H */
