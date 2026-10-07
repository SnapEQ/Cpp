#include <stdio.h>
#include "Stack.h"

int failed = 0;

void check(const char* name, bool condition) {
    if (condition) {
        printf("PASS: %s \n", name);
    } else {
        printf("FAIL: %s \n", name);
        failed++;
    }
}

void testInit() {
    Stack stack;

    init(&stack);

    check("init - stack is empty", isEmpty(&stack));
    check("init - top is -1", stack.top == -1);
    check("init - size is 1", stack.size == 1);
    check("init - memory is allocated", stack.stack != NULL);

    destroy(&stack);
}

void testPushPop() {
    Stack stack;

    init(&stack);

    push(&stack, 50);

    check("push - stack is not empty", !isEmpty(&stack));
    check("push - top is 0", stack.top == 0);
    check("pop - returns pushed element", pop(&stack) == 50);
    check("pop - stack is empty again", isEmpty(&stack));

    destroy(&stack);
}

void testOrder() {
    Stack stack;

    init(&stack);

    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);

    check("order - first pop returns 3", pop(&stack) == 3);
    check("order - second pop returns 2", pop(&stack) == 2);
    check("order - third pop returns 1", pop(&stack) == 1);
    check("order - stack is empty", isEmpty(&stack));

    destroy(&stack);
}

void testResize() {
    Stack stack;
    bool correct = true;

    init(&stack);

    for (int i = 0; i < 10; i++) {
        push(&stack, i * 10);
    }

    check("resize - top is 9", stack.top == 9);
    check("resize - size is 16", stack.size == 16);

    for (int i = 9; i >= 0; i--) {
        if (pop(&stack) != i * 10) {
            correct = false;
        }
    }

    check("resize - elements survived resizing", correct);
    check("resize - stack is empty", isEmpty(&stack));

    destroy(&stack);
}

void testPushAfterPop() {
    Stack stack;

    init(&stack);

    push(&stack, 50);
    push(&stack, 15);
    pop(&stack);
    push(&stack, 5);

    check("push after pop - returns 5", pop(&stack) == 5);
    check("push after pop - returns 50", pop(&stack) == 50);
    check("push after pop - stack is empty", isEmpty(&stack));

    destroy(&stack);
}

void testDestroy() {
    Stack stack;

    init(&stack);

    push(&stack, 50);

    destroy(&stack);

    check("destroy - pointer is NULL", stack.stack == NULL);
    check("destroy - top is -1", stack.top == -1);
    check("destroy - size is 0", stack.size == 0);
}

int main() {

    testInit();
    testPushPop();
    testOrder();
    testResize();
    testPushAfterPop();
    testDestroy();

    printf("\n");

    if (failed == 0) {
        printf("All tests passed \n");
    } else {
        printf("%d tests failed \n", failed);
    }

    return failed != 0;
}
