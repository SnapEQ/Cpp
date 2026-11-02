#include <stdexcept>
#include <string>
#include "ComplexStack.h"
#include "Complex.h"

// Every stub throws, so TestComplexStack.cpp reports it as FAIL instead of crashing.
// Remove the throwNotImplemented(...) line when you implement a function.
[[noreturn]] static void throwNotImplemented(const char* function) {
    throw std::logic_error(std::string(function) + " is not implemented");
}

ComplexStack::ComplexStack() 
: stack(new ComplexNumber[0]), size(0), top(-1) {

}

ComplexStack::ComplexStack(const ComplexStack& other) {
    stack = new ComplexNumber[other.size];
    size = other.size;
    top = other.top;

    for(int i = 0; i <= other.top; ++i) {
        stack[i] = other.stack[i];
    }
}

ComplexStack& ComplexStack::operator=(const ComplexStack& other) {
    if(this == &other) {
        return *this;
    }

    int elementsToCopy = other.top + 1;

    if (size < elementsToCopy) {
        ComplexNumber* temp = new ComplexNumber[elementsToCopy];
        delete[] stack;
        size = elementsToCopy;
        stack = temp;
    }

    for (int i = 0; i < elementsToCopy; ++i) {
        stack[i] = other.stack[i];
    }

    top = other.top;

    return *this;
}

ComplexStack::~ComplexStack() {
    delete[] stack;
}

bool ComplexStack::isEmpty() const {
    return top == -1;
}

int ComplexStack::getCount() const {
    return top + 1;
}

void ComplexStack::push(const ComplexNumber& element) {

    ComplexNumber copy = element;
    if (top + 1 == size) {
        size = (size == 0) ? 1 : size*2;
        ComplexNumber* temp = new ComplexNumber[size];
        for (int i = 0; i <= top; ++i) {
            temp[i] = stack[i];
        }
        delete[] stack;
        stack = temp;
    }

    top++;
    stack[top] = copy;
}

ComplexNumber ComplexStack::pop() {
    if(isEmpty()) {
        throw std::underflow_error("Cannot pop from empty stack");
    }

    ComplexNumber res = stack[top];
    top--;
    return res;
}

ComplexNumber ComplexStack::peek() const {
    if(isEmpty()) {
        throw std::underflow_error("Cannot peek an empty stack");
    }

    return stack[top];
}

ComplexNumber ComplexStack::sum() const {
    ComplexNumber sum = 0.0;
    for (int i = 0; i <= top; ++i) {
        sum += stack[i];
    }

    return sum;
}

ComplexStack ComplexStack::operator+(const ComplexStack& other) const {
    ComplexStack res = ComplexStack(*this);

    for (int i = 0; i <= other.top; ++i) {
        res.push(other.stack[i]);
    }

    return res;
}

ComplexStack& ComplexStack::operator+=(const ComplexStack& other) {

    int n = other.top;

    for (int i = 0; i <= n; ++i) {
        this->push(other.stack[i]);
    }
    return *this;
}

ComplexStack ComplexStack::operator*(double val) const {
    ComplexStack res = ComplexStack();

    int n = this->top;

    for (int i = 0; i <= n; ++i){
        res.push(this->stack[i]*val);
    }

    return res;
}

ComplexStack& ComplexStack::operator*=(double val) {
    *this = *this * val;
    return *this;
}

bool ComplexStack::operator==(const ComplexStack& other) const {
    if (top != other.top) {
        return false;
    }

    for(int i = 0; i <= top; ++i) {
        if (stack[i] != other.stack[i]) {
            return false;
        }
    }

    return true;
}

bool ComplexStack::operator!=(const ComplexStack& other) const {
    return !(*this==other);
}

ComplexStack operator*(double lhs, const ComplexStack& rhs) {
    ComplexStack res = rhs * lhs;
    return res;
}
