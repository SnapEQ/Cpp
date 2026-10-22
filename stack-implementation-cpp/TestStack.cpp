#include <iostream>
#include "Stack.h"

int failed = 0;

void check(const char* name, bool condition) {
    if (condition) {
        std::cout<<"PASS: "<<name<<std::endl;
    } else {
        std::cout<<"FAIL: "<<name<<std::endl;
        failed++;
    }
}

void testInit() {
    Stack stack;

    check("init - stack is empty", stack.isEmpty());
}

void testPushPop() {
    Stack stack;

    stack.push(50);

    check("push - stack is not empty", !stack.isEmpty());
    check("pop - returns pushed element", stack.pop() == 50);
    check("pop - stack is empty again", stack.isEmpty());
}

void testOrder() {
    Stack stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    check("order - first pop returns 3", stack.pop() == 3);
    check("order - second pop returns 2", stack.pop() == 2);
    check("order - third pop returns 1", stack.pop() == 1);
    check("order - stack is empty", stack.isEmpty());
}

void testResize() {
    Stack stack;
    bool correct = true;

    for (int i = 0; i < 10; i++) {
        stack.push(i * 10);
    }

    check("resize - stack is not empty", !stack.isEmpty());

    for (int i = 9; i >= 0; i--) {
        if (stack.pop() != i * 10) {
            correct = false;
        }
    }

    check("resize - elements survived resizing", correct);
    check("resize - stack is empty", stack.isEmpty());
}

void testPushAfterPop() {
    Stack stack;

    stack.push(50);
    stack.push(15);
    stack.pop();
    stack.push(5);

    check("push after pop - returns 5", stack.pop() == 5);
    check("push after pop - returns 50", stack.pop() == 50);
    check("push after pop - stack is empty", stack.isEmpty());
}

void testUnderflow() {
    Stack stack;
    bool thrown = false;

    try {
        stack.pop();
    } catch (const std::underflow_error&) {
        thrown = true;
    }

    check("underflow - pop on empty stack throws", thrown);
    check("underflow - stack is still empty", stack.isEmpty());
}

void testUnderflowAfterPop() {
    Stack stack;
    bool thrown = false;

    stack.push(10);
    stack.pop();

    try {
        stack.pop();
    } catch (const std::underflow_error&) {
        thrown = true;
    }

    check("underflow after pop - throws", thrown);
}

void testTwoStacks() {
    Stack stack1;
    Stack stack2;

    stack1.push(20);
    stack1.push(30);
    stack1.push(50);

    stack2.push(10);
    stack2.push(20);
    stack2.push(40);


    check("Stack 1 pop - returns 50", stack1.pop() == 50);
    check("Stack 1 pop - returns 30", stack1.pop() == 30);
    check("Stack 1 pop - returns 20", stack1.pop() == 20);
    check("Stack 2 pop - returns 40", stack1.pop() == 40);
    check("Stack 2 pop - returns 20", stack1.pop() == 20);
    check("Stack 2 pop - returns 10", stack1.pop() == 10);
}

int main() {

    testInit();
    testPushPop();
    testOrder();
    testResize();
    testPushAfterPop();
    testUnderflow();
    testUnderflowAfterPop();
    testTwoStacks();

    std::cout<<std::endl;

    if (failed == 0) {
        std::cout<<"All tests passed"<<std::endl;
    } else {
        std::cout<<failed<<" tests failed"<<std::endl;
    }

    return failed != 0;
}
