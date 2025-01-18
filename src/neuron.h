#ifndef NEURON_H
#define NEURON_H

typedef struct neuron_t neuron_t;

neuron_t *neurons_new (int num, int inp_num);
void neurons_free (neuron_t *array, int num);

#ifdef DEBUG
void neuron_info (neuron_t *neuron);
void array_info (neuron_t *array, int len);
#endif /* DEBUG */

#endif /* NEURON_H */
