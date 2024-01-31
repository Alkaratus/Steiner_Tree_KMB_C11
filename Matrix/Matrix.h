//
// Created by alkaratus on 11.12.23.
//

#ifndef KMB_PTHREADS_MATRIX_H
#define KMB_PTHREADS_MATRIX_H
typedef struct Matrix{
  int** values;
  int rows,columns;
} Matrix;

Matrix *matrix_create(int rows,int columns);
void matrix_destroy(Matrix *matrix);

void matrix_display(Matrix* matrix);

#endif //KMB_PTHREADS_MATRIX_H
