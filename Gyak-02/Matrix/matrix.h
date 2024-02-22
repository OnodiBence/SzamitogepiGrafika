#ifndef MATRIX_H
#define MATRIX_H

#define MAX_STACK_SIZE 100

/**
 * Transzformációs mátrix struktúra
 */
typedef struct {
    float matrix[4][4];
} Matrix;

/**
 * Verem struktúra
 */
typedef struct {
    Matrix data[MAX_STACK_SIZE];
    int top;
} MatrixStack;

void initialize_stack(MatrixStack *stack);

int is_empty(MatrixStack *stack);

int is_full(MatrixStack *stack);

void push_matrix(MatrixStack *stack, Matrix m);

Matrix pop_matrix(MatrixStack *stack);

#endif // CUBOID_H