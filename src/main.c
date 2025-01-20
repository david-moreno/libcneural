#include <stdio.h>
#include "cneural.h"

#define LAYNUM 5
#define INPNUM 3
#define OUTNUM 8
#define FNAME "nn-graph.gv"

int main(int argc, char *argv[])
{
	cneural_t *nn;
	int r;

	printf("/* Layers: %i, Inputs: %i, Outputs: %i */\n", LAYNUM, INPNUM, OUTNUM);

	nn = cn_network_new(LAYNUM, INPNUM, OUTNUM);
	if (nn == NULL) {
		printf("ERROR: %s\n", cn_get_error_msg());
		return 1;
	}

	r = cn_set_layer_size(nn, 3, 5);
	//printf("r: %i\n", r);

	cn_build_network(nn);

	cn_graph_network(nn, FNAME);
	//debug_dump_layer_info(nn);
	//debug_dump_network(nn);

	cn_network_free(nn);

	return 0;
}
