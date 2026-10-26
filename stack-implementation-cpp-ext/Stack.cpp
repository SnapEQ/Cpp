#include <stdlib.h>
#include <stdexcept>
#include "Stack.h"

void assertAllocated(int* pointer) {
    if (pointer == NULL) {
        throw std::bad_alloc();
    }
}

void assertNotEmpty(bool empty) {
    if (empty) {
        throw std::underflow_error("Stack underflow");
    }
}

Stack::Stack(){

    size = 1;
    top = -1;
    stack = (int *)malloc(size * sizeof(int));
    assertAllocated(stack);
}

Stack::Stack(const Stack& other) {

    top = other.top;
    size = other.top + 1;
    if (size < 1) {
        size = 1;
    }

    stack = (int *)malloc(size * sizeof(int));
    assertAllocated(stack);

    for (int i = 0; i <= top; i++) {
        stack[i] = other.stack[i];
    }
}

Stack& Stack::operator=(const Stack& other) {
    if (this == &other) {
        return *this;
    }

    int elementsToCopy = other.top + 1;

    if (this->size < elementsToCopy) {
        int* temp = (int *)malloc(elementsToCopy * sizeof(int));
        assertAllocated(temp);
        free(this->stack);
        this->stack = temp;
        this->size = elementsToCopy;
    }

    for (int i = 0; i < elementsToCopy; i++) {
        this->stack[i] = other.stack[i];
    }
    this->top = other.top;

    return *this;
}

bool Stack::isEmpty() {
    return top == -1;
}

void Stack::push(int element) {

    if (this->top + 1 == this->size) {
        int* temp = (int *)realloc(this->stack, this->size * 2 * sizeof(int));
        assertAllocated(temp);
        this->stack = temp;
        this->size *= 2;

    }
    this->stack[++(this->top)] = element;
}

int Stack::pop() {
    assertNotEmpty(this->isEmpty());

    return this->stack[(this->top)--];
}

Stack::~Stack() {
    free(stack);
}
