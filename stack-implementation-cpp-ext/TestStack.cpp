#include "Stack.h"

void printStackSizes(Stack& s1, Stack& s2);
void stackOperator_sameSizes_shouldAssignStack();
void stackOperator_firstStackSmaller_shouldAssignStack();
void stackOperator_firstStackLarger_shouldAssignStack();
void copyConstructor_secondStackWithElements_shouldCopyStack();

int main () {
    stackOperator_firstStackLarger_shouldAssignStack();
    stackOperator_firstStackSmaller_shouldAssignStack();
    stackOperator_sameSizes_shouldAssignStack();
    copyConstructor_secondStackWithElements_shouldCopyStack();

    return 0;
}

void stackOperator_sameSizes_shouldAssignStack() {
    std::cout<<"#stackOperator_sameSizes_shouldAssignStack# is running"<<std::endl;
    Stack s1, s2;

    for (int i = 0; i <= 20; i++) {
        s1.push(i);
        s2.push(20-i);
    }

    s1 = s2;

    printStackSizes(s1, s2);
}

void stackOperator_firstStackSmaller_shouldAssignStack() {
    std::cout<<"#stackOperator_firstStackSmaller_shouldAssignStack# is running"<<std::endl;

    Stack s1, s2;

    for (int i = 0; i <= 20; i++) {
        s1.push(i);
        if (i<10) s2.push(20 - i);
    }

    s1 = s2;

    printStackSizes(s1, s2);
}

void stackOperator_firstStackLarger_shouldAssignStack() {
    std::cout<<"#stackOperator_firstStackLarger_shouldAssignStack# is running"<<std::endl;

    Stack s1, s2;

    for (int i = 0; i <= 20; i++) {
        s2.push(i);
        if (i<10) s1.push(20 - i);
    }

    s1 = s2;

    printStackSizes(s1, s2);

}

void copyConstructor_secondStackWithElements_shouldCopyStack() {
    std::cout<<"#copyConstructor_secondStackWithElements_shouldCopyStack# is running"<<std::endl;

    Stack s1;

    for (int i = 0; i <= 20; i++) {
        s1.push(i);
    }

    Stack s2(s1);

    printStackSizes(s1, s2);
}

void printStackSizes(Stack& s1, Stack& s2) {
    std::cout<<"S1 size is: "<<s1.getSize()<<std::endl;
    std::cout<<"S2 size is: "<<s2.getSize()<<std::endl;
}


