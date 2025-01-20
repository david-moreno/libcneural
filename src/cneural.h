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
float cn_get_neuron_input_value (cneural_t *network, int layer_i, int neuron_i, int input_i);
float cn_get_neuron_input_weight (cneural_t *network, int layer_i, int neuron_i, int input_i);

/* DEBUG */
void debug_dump_network (cneural_t *network);
void debug_dump_layer_info (cneural_t *network);



/* Error codes. */
char *cn_get_error_msg (void);

#endif /* CNEURAL_H */
