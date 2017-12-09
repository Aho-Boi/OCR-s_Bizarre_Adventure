#ifndef _MAT_FUNC_
#define _MAT_FUNC_

struct matrix_s {
  int height;
  int width;
  double *mat; // height * width
  double *output; // 1 * width
};
typedef struct matrix_s matrix_t;

struct input_s {
  matrix_t *mat;
  matrix_t *expOutput;
  int exp;
};
typedef struct input_s input_t;

matrix_t *mat_create(int h, int w);
void mat_free(matrix_t *mat);
matrix_t *mat_mult(matrix_t *mat1, matrix_t *mat2);
void mat_rand(matrix_t *matr);
void mat_activation(matrix_t *mat);

#endif /* _MAT_FUNC_ */
