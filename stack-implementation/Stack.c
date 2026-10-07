#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

void init(Stack* s) {
    s->size = 1;
    s->top = -1;
    s->stack = (int *)malloc(s->size * sizeof(int));

    if (s->stack == NULL) {
        printf("Failed to allocate memory \n");
        exit(1);
    }
}

void destroy(Stack* s) {
    free(s->stack);
    s->stack = NULL;
    s->top = -1;
    s->size = 0;
}

void push(Stack *s, int element) {
    if(s->top+1 == s->size) {
        s->size*=2;
        int* temp = (int *)realloc(s->stack, s->size * sizeof(int));
        if (temp == NULL) {
            printf("Failed to allocate memory \n");
            exit(1);
        }
        s->stack = temp;
        printf("Stack resized to %d \n", s->size);
    }
    s->stack[++(s->top)] = element;
}

int pop(Stack *s) {

    if(isEmpty(s)){
        printf("Stack underflow \n");
        exit(1);
    }

    return s->stack[(s->top)--];

}

bool isEmpty(const Stack *s) {
    return s->top == -1;
}

void printStack(Stack *s) {
    if(isEmpty(s)) {
        printf("Cannot print, stack is empty \n");
        return;
    }

    for (int i = 0; i <= s->top; i++) {
        printf("%d, ", s->stack[i]);
    }
    printf("\n");
}
