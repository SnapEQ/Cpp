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

void Stack::printStack() {

    if(isEmpty()) {
        return;
    }

    for (int i = 0; i <= this->top; i++) {
        std::cout<<this->stack[i]<<", ";
    }
    std::cout<<std::endl;
}

Stack::~Stack() {
    free(stack);
}

