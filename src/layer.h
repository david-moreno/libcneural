#ifndef LAYER_H
#define LAYER_H

typedef struct layer_t layer_t;

layer_t *cn_layer_new (int neuron_num, int inp_num);
void cn_layer_free (layer_t *layer);

#ifdef DEBUG
void print_layer (layer_t *layer, int index);
#endif /* DEBUG */

#endif /* LAYER_H */
