#ifndef CNEURAL_T_H
#define CNEURAL_T_H

#include "layer.h"

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

#endif /* CNEURAL_T_H */
