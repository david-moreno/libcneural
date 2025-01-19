#ifndef CNEURAL_H
#define CNEURAL_H

typedef struct cneural_t cneural_t;

cneural_t *cn_network_new (int lay_num, int inp_num, int out_num);
void cn_network_free (cneural_t *network);
int cn_set_layer_size (cneural_t *network, int index, int size);
int cn_build_network (cneural_t *network);
int cn_graph_network (cneural_t *network, const char *fname);

int cn_get_layers_num (cneural_t *network);
int cn_get_layer_neuron_num (cneural_t *network, int layer);

/* Error codes. */
char *cn_get_error_msg (void);

#endif /* CNEURAL_H */
