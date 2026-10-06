#include "Stack.h"
#include <cstddef>

Stack::Stack() {

    size = 1;
    top = -1;
    stack = (int *)malloc(size * sizeof(int));

    if (stack == NULL) {
        std::cout<<"Failed to allocate memory!"<<std::endl;
        exit(1);
    }

    std::cout<<"Constructor called succesfully"<<std::endl;

}

Stack::Stack(const Stack& other) {
    top = other.top;

    size = other.top + 1;
    if (size < 1) {
        size = 1;
    }

    stack = (int *)malloc(size * sizeof(int));

    if (stack == NULL) {
        std::cout << "Failed to allocate memory!"<<std::endl;
        exit(1);
    }

    for (int i = 0; i <= top; i++) {
        stack[i] = other.stack[i];
    }

    std::cout<< "Copy constructor called successfully" <<std::endl;

}

Stack& Stack::operator=(const Stack& other) {
    if (this == &other) {
        return *this;
    }

    int elementsToCopy = other.top + 1;

    if (size < elementsToCopy) {
        int* newStack = (int*)malloc(elementsToCopy * sizeof(int));

        if (newStack == NULL) {
            std::cout<<"Failed to allocate memory!"<<std::endl;
            exit(1);
        }

        free(stack);
        stack = newStack;
        size = elementsToCopy;

    }

        for (int i = 0; i < elementsToCopy; i++) {
            stack[i] = other.stack[i];
        }

        top = other.top;
        return *this;
}

bool Stack::isEmpty() {
    return top == -1;
}

void Stack::push(int element) {

    if (this->top + 1 == this->size) {
        this->size *= 2;
        int* temp = (int *)realloc(this->stack, this->size * sizeof(int));
        if (temp == NULL) {
            std::cout<<"Failed to allocate memory!"<<std::endl;
        }
        this->stack = temp;
        //std::cout<<"Stack resized to: "<<size<<std::endl;

    }
    this->stack[++(this->top)] = element;
}

int Stack::pop() {
    if(this->isEmpty()) {
        std::cout<<"Stack underflow"<<std::endl;
        exit(1);
    }

    return this->stack[(this->top)--];
}

void Stack::printStack() {

    if(isEmpty()) {
        std::cout<<"Cannot print, stack is empty"<<std::endl;
        return;
    }

    for (int i = 0; i <= this->top; i++) {
        std::cout<<this->stack[i]<<", ";
    }
    std::cout<<std::endl;
}

int Stack::getSize() {
    return this->size;
}

Stack::~Stack() {
    free(stack);
    std::cout<<"Destructor called, memory freed"<<std::endl;
}

