#pragma once

#include "Complex.h"

// DO NOT change the public interface - TestComplexStack.cpp depends on it.
// You MAY change the private section (different members, helper methods).

class ComplexStack {

    private:
        ComplexNumber* stack;
        int size;  // allocated capacity
        int top;   // index of the top element, -1 when empty

    public:
        ComplexStack();
        ComplexStack(const ComplexStack& other);
        ComplexStack& operator=(const ComplexStack& other);
        ~ComplexStack();

        bool isEmpty() const;
        int getCount() const;
        void push(const ComplexNumber& element);
        ComplexNumber pop();
        ComplexNumber peek() const;
        ComplexNumber sum() const;

        ComplexStack operator+(const ComplexStack& other) const;
        ComplexStack& operator+=(const ComplexStack& other);
        ComplexStack operator*(double val) const;
        ComplexStack& operator*=(double val);
        bool operator==(const ComplexStack& other) const;
        bool operator!=(const ComplexStack& other) const;
};

ComplexStack operator*(double lhs, const ComplexStack& rhs);
