#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

// Transzformációs mátrix struktúra
typedef struct {
    float matrix[4][4];
} Matrix;

// Verem struktúra
typedef struct {
    Matrix data[MAX_STACK_SIZE];
    int top;
} MatrixStack;

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

// Példa a verem működésére
int main() {
    MatrixStack stack;
    initialize_stack(&stack);

    // Példamátrixok létrehozása és hozzáadása a veremhez
    Matrix m1 = {
        {{2, 1, 0, 0},
         {0, 1, 3, 0},
         {2, 0, 1, 0},
         {0, 3, 0, 1}}
    };
    push_matrix(&stack, m1);

    Matrix m2 = {
        {{2, 0, 1, 0},
         {0, 2, 1, 0},
         {3, 0, 2, 0},
         {0, 2, 0, 1}}
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
