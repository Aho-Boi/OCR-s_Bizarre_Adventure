#ifndef _MAT_FUNC_
#define _MAT_FUNC_

struct matrix_s {
  int height;
  int width;
  double *mat;
};
typedef struct matrix_s matrix_t;

matrix_t *mat_create(int h, int w);
inline void *mat_free(matrix_t mat);
matrix_t *mat_mult(matrix_t *mat1, matrix_t *mat2);
void mat_rand(matrix_t *matr);

#endif /* _MAT_FUNC_ */
