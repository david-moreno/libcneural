#include <stdio.h>
#include "cneural.h"
#include "graph.h"

static int graph_layer (cneural_t *network, int index, FILE *fp)
{
	int layer_num, neuron_num, next_neuron_num, next_index, n, nn;
	float v, w;

	layer_num = cn_get_layers_num(network) - 1;
	neuron_num = cn_get_layer_neuron_num(network, index);

	if (index < layer_num) {
		next_neuron_num = cn_get_layer_neuron_num(network, index + 1);
		next_index = index + 1;
		for (n=0; n < neuron_num; n++) {
			for (nn=0; nn < next_neuron_num; nn++) {
				v = cn_get_neuron_input_value(network, next_index, nn, n);
				w = cn_get_neuron_input_weight(network, next_index, nn, n);
				fprintf(fp, "\t\"%i-%i\" -- ", index, n);
				fprintf(fp, "\"%i-%i\" ", next_index, nn);
				fprintf(fp, "[headlabel=\"(%f, %f)\", fontsize=%i]\n", v, w, VW_SIZE);
			}

			fprintf(fp, "\n");
		}
	}

	return neuron_num;
}

int graph_network (cneural_t *network, FILE *fp)
{
	int lay_num, l;

	fprintf(fp, "graph network {\n\n");
	fprintf(fp,
			"\tnodesep=%i;\n\tranksep=%i;\n\trankdir=LR;\n\n",
			NODESEP, RANKSEP);

	lay_num = cn_get_layers_num(network) - 1;
	for (l=0; l < lay_num; l++) {
		graph_layer(network, l, fp);
	}

	fprintf(fp, "}\n");

	return l;
}
