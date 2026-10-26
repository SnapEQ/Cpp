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

void testCopyConstructor() {
    Stack stack1;
    bool correct = true;

    for (int i = 0; i <= 20; i++) {
        stack1.push(i);
    }

    Stack stack2(stack1);

    for (int i = 20; i >= 0; i--) {
        if (stack2.pop() != i) {
            correct = false;
        }
    }

    check("copy constructor - copy has the same elements", correct);
    check("copy constructor - copy is empty after popping", stack2.isEmpty());
    check("copy constructor - original is untouched", stack1.pop() == 20);
}

void testCopyConstructorEmpty() {
    Stack stack1;
    Stack stack2(stack1);

    check("copy constructor empty - copy is empty", stack2.isEmpty());

    stack2.push(5);

    check("copy constructor empty - copy can be pushed to", stack2.pop() == 5);
    check("copy constructor empty - original is still empty", stack1.isEmpty());
}

void testAssignSameSizes() {
    Stack stack1;
    Stack stack2;

    for (int i = 0; i <= 20; i++) {
        stack1.push(i);
        stack2.push(20 - i);
    }

    stack1 = stack2;

    check("assign same sizes - top is copied", stack1.pop() == 0);
    check("assign same sizes - next is copied", stack1.pop() == 1);
    check("assign same sizes - source is untouched", stack2.pop() == 0);
}

void testAssignFirstSmaller() {
    Stack stack1;
    Stack stack2;
    bool correct = true;

    for (int i = 0; i < 10; i++) {
        stack1.push(i);
    }
    for (int i = 0; i <= 20; i++) {
        stack2.push(i * 2);
    }

    stack1 = stack2;

    for (int i = 20; i >= 0; i--) {
        if (stack1.pop() != i * 2) {
            correct = false;
        }
    }

    check("assign first smaller - all elements copied", correct);
    check("assign first smaller - stack is empty", stack1.isEmpty());
}

void testAssignFirstLarger() {
    Stack stack1;
    Stack stack2;

    for (int i = 0; i <= 20; i++) {
        stack1.push(i);
    }
    for (int i = 0; i < 3; i++) {
        stack2.push(i * 2);
    }

    stack1 = stack2;

    check("assign first larger - returns 4", stack1.pop() == 4);
    check("assign first larger - returns 2", stack1.pop() == 2);
    check("assign first larger - returns 0", stack1.pop() == 0);
    check("assign first larger - stack is empty", stack1.isEmpty());
}

void testAssignSelf() {
    Stack stack;

    stack.push(10);
    stack.push(20);

    Stack& alias = stack;
    stack = alias;

    check("assign self - returns 20", stack.pop() == 20);
    check("assign self - returns 10", stack.pop() == 10);
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
    check("Stack 2 pop - returns 40", stack2.pop() == 40);
    check("Stack 2 pop - returns 20", stack2.pop() == 20);
    check("Stack 2 pop - returns 10", stack2.pop() == 10);
}

int main() {

    testInit();
    testPushPop();
    testOrder();
    testResize();
    testUnderflow();
    testCopyConstructor();
    testCopyConstructorEmpty();
    testAssignSameSizes();
    testAssignFirstSmaller();
    testAssignFirstLarger();
    testAssignSelf();
    testTwoStacks();

    std::cout<<std::endl;

    if (failed == 0) {
        std::cout<<"All tests passed"<<std::endl;
    } else {
        std::cout<<failed<<" tests failed"<<std::endl;
    }

    return failed != 0;
}
