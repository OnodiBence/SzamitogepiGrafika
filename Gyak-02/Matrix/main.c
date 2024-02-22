#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

// Példa a verem működésére
int main() {
    MatrixStack stack;
    initialize_stack(&stack);

    // Példamátrixok létrehozása és hozzáadása a veremhez
    Matrix m1 = {
        {{1, 0, 0, 0},
         {0, 1, 0, 0},
         {0, 0, 1, 0},
         {0, 0, 0, 1}}
    };
    push_matrix(&stack, m1);

    Matrix m2 = {
        {{2, 0, 0, 0},
         {0, 2, 0, 0},
         {0, 0, 2, 0},
         {0, 0, 0, 1}}
    };
    push_matrix(&stack, m2);

    // Mátrixok kivétele a veremből és kiíratása
    Matrix result = pop_matrix(&stack);
    printf("Pop matrix 1:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%.2f\t", result.matrix[i][j]);
        }
        printf("\n");
    }

    result = pop_matrix(&stack);
    printf("\nPop matrix 2:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%.2f\t", result.matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
