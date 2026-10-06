#include "Stack.h"

Stack::Stack(){

    size = 1;
    top = -1;
    stack = (int *)malloc(size * sizeof(int));

    if (stack == NULL) {
        std::cout<<"Failed to allocate memory!"<<std::endl;
        exit(1);
    }

    std::cout<<"Constructor called succesfully"<<std::endl;

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
        std::cout<<"Stack resized to: "<<size<<std::endl;

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

Stack::~Stack() {
    free(stack);
    std::cout<<"Destructor called, memory freed"<<std::endl;
}

