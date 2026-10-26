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
        ~Stack();
};
