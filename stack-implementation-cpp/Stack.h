#include <iostream>
#include <stdlib.h>

#pragma once

class Stack{

    private:
        int* stack;
        int size;
        int top;

    public:
        Stack();
        bool isEmpty();
        void push(int element);
        int pop();
        void printStack();
        ~Stack();
};
