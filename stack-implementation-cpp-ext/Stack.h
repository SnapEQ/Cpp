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
        Stack(const Stack& other);
        Stack& operator=(const Stack& other);
        bool isEmpty();
        void push(int element);
        int pop();
        void printStack();
        int getSize();
        ~Stack();
};
