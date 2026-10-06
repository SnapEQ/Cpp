#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *stack;
    int top;
    int size;
}Stack;

void init(Stack* s);
void destroy(Stack* s);
void push(Stack* s, int element);
int pop(Stack* s);
bool isEmpty(const Stack* s);


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
    int index = 0;

    while(index < s->size) {
        printf("%d, ", s->stack[index]);
        index++;
    }
    printf("\n");
}

int main() {

    Stack stack;

    init(&stack);

    push(&stack, 50);

    printStack(&stack);

    push(&stack, 15);

    printStack(&stack);

    pop(&stack);

    printStack(&stack);

    push(&stack, 5);

    printStack(&stack);

    push(&stack,25);

    printStack(&stack);

    destroy(&stack);

    return 0;
}
