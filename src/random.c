#include <stdlib.h>
#include "cneural.h"

/* Don't forget to:
 *
 *    srand(time(NULL));
 *
 * Before call this function!
 */
static inline float frand (float min, float max)
{
	float diff;

	diff = max - min;

	return ((float) rand() / (float) (RAND_MAX/diff)) + min;
}

void randomize_weights (cneural_t *network)
{
	int layer_num, neuron_num, inp_num;
	float inf, sup, w;

	layer_num = cn_get_layers_num(network);
	inf = cn_get_weight_inf(network);
	sup = cn_get_weight_sup(network);

	for (int l=1; l < layer_num; l++) {
		neuron_num = cn_get_layer_neuron_num(network, l);
		inp_num = cn_get_layer_input_num(network, l);

		for (int n=0; n < neuron_num; n++) {
			for (int i=0; i < inp_num; i++) {
				w = frand(inf, sup);
				cn_set_neuron_input_weight(network, l, n, i, w);
			}
		}
	}
}
