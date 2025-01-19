#ifndef NEURON_H
#define NEURON_H

typedef struct neuron_t neuron_t;

neuron_t *neurons_new (int num, int inp_num);
void neurons_free (neuron_t *array, int num);
float get_neuron_input_value (neuron_t *neurons, int neuron_i, int inp_i);
float get_neuron_input_weight (neuron_t *neurons, int neuron_i, int inp_i);

#endif /* NEURON_H */
