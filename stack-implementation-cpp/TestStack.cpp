#include "Stack.h"

int main (int argc, char *argv[]) {
    
    Stack s;
    s.push(15);
    s.printStack();
    std::cout<<"Popped element: "<<s.pop()<<std::endl;
    s.printStack();
    s.push(30);
    s.printStack();
    s.push(40);
    s.printStack();
    std::cout<<"Stack empty: "<<s.isEmpty()<<std::endl;
    s.pop();
    s.printStack();


    return 0;
}
