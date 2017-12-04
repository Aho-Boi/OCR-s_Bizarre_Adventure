#ifndef _OCR_FUNC_
#define _OCR_FUNC_

matrix_t work(matrix_t *input, matrix_t *neuron, matrix_t *output);
void back_prop(int expOutput, matrix_t *neuron, matrix_t *output);

#endif /* _OCR_FUNC_ */
