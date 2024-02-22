#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

// Verem inicializálása
void initialize_stack(MatrixStack *stack) {
    stack->top = -1;
}

// Ellenőrzi, hogy a verem üres-e
int is_empty(MatrixStack *stack) {
    return stack->top == -1;
}

// Ellenőrzi, hogy a verem tele van-e
int is_full(MatrixStack *stack) {
    return stack->top == MAX_STACK_SIZE - 1;
}

// Mátrix hozzáadása a veremhez
void push_matrix(MatrixStack *stack, Matrix m) {
    if (is_full(stack)) {
        printf("A verem tele van, nem lehet további elemeket hozzáadni.\n");
        return;
    }
    stack->data[++stack->top] = m;
}

// Mátrix kivétele a veremből
Matrix pop_matrix(MatrixStack *stack) {
    if (is_empty(stack)) {
        printf("A verem üres, nem lehet elemet kivenni.\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}