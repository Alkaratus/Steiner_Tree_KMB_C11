//
// Created by alkaratus on 11.12.23.
//

#include <stdlib.h>
#include <stdio.h>
#include "Matrix.h"

Matrix *matrix_create(int rows,int columns){
    Matrix *new=malloc(sizeof(Matrix));
    new->rows=rows;
    new->columns=columns;
    new->values=calloc(rows,sizeof(int*));
    for(int i=0;i<rows;i++){
        new->values[i]=calloc(columns,sizeof(int));
    }
    return new;
}

void matrix_destroy(Matrix *matrix){
    for(int i=0; i<matrix->rows;i++){
        free(matrix->values[i]);
    }

}

void matrix_display(Matrix *matrix) {
    for(int i=0;i<matrix->rows;i++){
        for(int j=0;j<matrix->columns;j++){
            printf("%d ",matrix->values[i][j]);
        }
        printf("\n");
    }
}
