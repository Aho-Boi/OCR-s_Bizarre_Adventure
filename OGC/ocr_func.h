#ifndef _OCR_FUNC_
#define _OCR_FUNC_

#include "mat_func.h"

void work(matrix_t *input, matrix_t *neuron, matrix_t *output);
double back_prop(matrix_t *exp, matrix_t *input, matrix_t *neuron, matrix_t *output);

#endif /* _OCR_FUNC_ */
