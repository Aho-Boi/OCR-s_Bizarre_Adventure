#ifndef _OCR_FUNC_
#define _OCR_FUNC_

#include "mat_func.h"

matrix_t work(matrix_t *input, matrix_t *neuron, matrix_t *output);
double back_prop(int expOutput, matrix_t *neuron, matrix_t *output);

#endif /* _OCR_FUNC_ */
