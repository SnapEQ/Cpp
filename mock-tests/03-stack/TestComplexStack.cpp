#include <cmath>
#include <iostream>
#include <stdexcept>
#include "Complex.h"
#include "ComplexStack.h"

int passed = 0;
int failed = 0;

void check(const char* name, bool condition) {
    if (condition) {
        std::cout<<"PASS: "<<name<<std::endl;
        passed++;
    } else {
        std::cout<<"FAIL: "<<name<<std::endl;
        failed++;
    }
}

void run(const char* testName, void (*test)()) {
    try {
        test();
    } catch (const std::exception& e) {
        std::cout<<"FAIL: "<<testName<<" - unexpected exception: "<<e.what()<<std::endl;
        failed++;
    } catch (...) {
        std::cout<<"FAIL: "<<testName<<" - unexpected unknown exception"<<std::endl;
        failed++;
    }
}

// Compares through the getters, so these checks don't depend on your operator==.
bool is(const ComplexNumber& num, double realPart, double imaginaryPart) {
    return std::fabs(num.getRealPart() - realPart) < 1e-9
        && std::fabs(num.getImaginaryPart() - imaginaryPart) < 1e-9;
}

// Pushes real numbers 1, 2, ..., n (n ends up on top).
void pushReals(ComplexStack& stack, int n) {
    for (int i = 1; i <= n; i++) {
        stack.push(ComplexNumber(i, 0));
    }
}

// Pops everything and checks the real parts came out as expected[0..n-1] (top first).
bool popsReals(ComplexStack& stack, const double* expected, int n) {
    if (stack.getCount() != n) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (!is(stack.pop(), expected[i], 0)) {
            return false;
        }
    }
    return stack.isEmpty();
}

// ===================== PART A - ComplexNumber =====================

void testComplexConstructor() {
    ComplexNumber zero;
    ComplexNumber real(3);
    ComplexNumber full(3, -4);

    check("complex constructor - default is 0+0i", is(zero, 0, 0));
    check("complex constructor - one argument is real", is(real, 3, 0));
    check("complex constructor - two arguments", is(full, 3, -4));
}

void testComplexAddSubtract() {
    ComplexNumber num1(2, -3);
    ComplexNumber num2(3, 2);

    check("complex + complex", is(num1 + num2, 5, -1));
    check("complex - complex", is(num1 - num2, -1, -5));
    check("complex + double", is(num1 + 0.5, 2.5, -3));
    check("complex - double", is(num1 - 0.5, 1.5, -3));
    check("complex + - - operands untouched", is(num1, 2, -3) && is(num2, 3, 2));
}

void testComplexMultiplyDivide() {
    ComplexNumber num1(2, -3);
    ComplexNumber num2(3, 2);

    check("complex * complex", is(num1 * num2, 12, -5));
    check("complex / complex", is(num1 / num2, 0, -1));
    check("complex * double", is(num1 * 2.0, 4, -6));
    check("complex / double", is(num1 / 2.0, 1, -1.5));
    check("complex * / - operands untouched", is(num1, 2, -3) && is(num2, 3, 2));
}

void testComplexDoubleOnLeft() {
    ComplexNumber num(3, 2);
    ComplexNumber one(1, 1);

    check("double + complex", is(2.0 + num, 5, 2));
    check("double - complex", is(2.0 - num, -1, -2));
    check("double * complex", is(2.0 * num, 6, 4));
    check("double / complex", is(2.0 / one, 1, -1));
    check("double on left - operand untouched", is(num, 3, 2));
}

void testComplexCompoundComplex() {
    ComplexNumber num(2, -3);
    ComplexNumber other(3, 2);

    num += other;
    check("complex += complex", is(num, 5, -1));

    num -= other;
    check("complex -= complex", is(num, 2, -3));

    num *= other;
    check("complex *= complex", is(num, 12, -5));

    num /= other;
    check("complex /= complex", is(num, 2, -3));

    check("compound complex - right operand untouched", is(other, 3, 2));
}

void testComplexCompoundDouble() {
    ComplexNumber num(2.5, -5);

    num += 0.5;
    check("complex += double", is(num, 3, -5));

    num -= 1.0;
    check("complex -= double", is(num, 2, -5));

    num *= 2.0;
    check("complex *= double", is(num, 4, -10));

    num /= 4.0;
    check("complex /= double", is(num, 1, -2.5));
}

void testComplexCompoundSelf() {
    ComplexNumber num1(1, 2);
    ComplexNumber num2(1, 2);

    num1 += num1;
    num2 *= num2;

    check("complex += itself", is(num1, 2, 4));
    check("complex *= itself", is(num2, -3, 4));
}

void testComplexCompoundChain() {
    ComplexNumber num1(1.0, 0.5);
    ComplexNumber num2(2.0, 0.25);
    ComplexNumber num3(4.0, 0.125);

    num1 += num2 += num3;

    check("complex a += b += c - b changed", is(num2, 6, 0.375));
    check("complex a += b += c - a changed", is(num1, 7, 0.875));

    ComplexNumber num4(1, 1);
    ComplexNumber num5(0, 1);

    (num4 *= num5) *= num5;

    check("complex (a *= b) *= b", is(num4, -1, -1));
    check("complex compound returns *this", &(num4 += 1.0) == &num4);
}

void testComplexEqual() {
    ComplexNumber num1(1.5, 1.25);
    ComplexNumber num2(1.5, 1.25);
    ComplexNumber num3(1.5, 1.0);
    ComplexNumber real(1.5, 0.0);

    check("complex == complex - true", num1 == num2);
    check("complex == complex - false", !(num1 == num3));
    check("complex != complex - true", num1 != num3);
    check("complex != complex - false", !(num1 != num2));
    check("complex == double - true", real == 1.5);
    check("complex == double - imaginary part matters", !(num1 == 1.5));
    check("complex != double - true", num1 != 1.5);
    check("complex != double - false", !(real != 1.5));
}

// ===================== PART B - basic ComplexStack =====================

void testInit() {
    ComplexStack stack;

    check("init - stack is empty", stack.isEmpty());
    check("init - count is 0", stack.getCount() == 0);
}

void testPushPop() {
    ComplexStack stack;

    stack.push(ComplexNumber(1.5, -2));

    check("push - stack is not empty", !stack.isEmpty());
    check("push - count is 1", stack.getCount() == 1);
    check("peek - returns the top", is(stack.peek(), 1.5, -2));
    check("peek - does not remove the top", stack.getCount() == 1);
    check("pop - returns pushed element", is(stack.pop(), 1.5, -2));
    check("pop - stack is empty again", stack.isEmpty());
}

void testOrder() {
    ComplexStack stack;

    stack.push(ComplexNumber(1, 1));
    stack.push(ComplexNumber(2, 2));
    stack.push(ComplexNumber(3, 3));

    check("order - first pop returns 3+3i", is(stack.pop(), 3, 3));
    check("order - second pop returns 2+2i", is(stack.pop(), 2, 2));
    check("order - third pop returns 1+1i", is(stack.pop(), 1, 1));
    check("order - stack is empty", stack.isEmpty());
}

void testPushedCopy() {
    ComplexStack stack;
    ComplexNumber num(1, 1);

    stack.push(num);
    num.setRealPart(100);

    check("pushed copy - changing the variable later does not change the stack", is(stack.peek(), 1, 1));
}

void testResize() {
    ComplexStack stack;
    bool correct = true;

    for (int i = 0; i < 100; i++) {
        stack.push(ComplexNumber(i, -i));
    }

    check("resize - count is 100", stack.getCount() == 100);

    for (int i = 99; i >= 0; i--) {
        if (!is(stack.pop(), i, -i)) {
            correct = false;
        }
    }

    check("resize - elements survived resizing", correct);
    check("resize - stack is empty", stack.isEmpty());
}

void testUnderflow() {
    ComplexStack stack;
    bool popThrown = false;
    bool peekThrown = false;

    try {
        stack.pop();
    } catch (const std::underflow_error&) {
        popThrown = true;
    }

    try {
        stack.peek();
    } catch (const std::underflow_error&) {
        peekThrown = true;
    }

    check("underflow - pop on empty stack throws", popThrown);
    check("underflow - peek on empty stack throws", peekThrown);
    check("underflow - stack is still empty", stack.isEmpty());
}

void testSum() {
    ComplexStack stack;
    ComplexStack empty;

    stack.push(ComplexNumber(1, 1));
    stack.push(ComplexNumber(2, -3));
    stack.push(ComplexNumber(0.5, 0));

    check("sum - adds all elements", is(stack.sum(), 3.5, -2));
    check("sum - does not change the stack", stack.getCount() == 3 && is(stack.peek(), 0.5, 0));
    check("sum - empty stack sums to 0+0i", is(empty.sum(), 0, 0));
}

// ===================== PART C - copy semantics =====================

void testCopyConstructor() {
    ComplexStack stack1;
    bool correct = true;

    for (int i = 0; i <= 20; i++) {
        stack1.push(ComplexNumber(i, 1));
    }

    ComplexStack stack2(stack1);

    check("copy constructor - copy has the same count", stack2.getCount() == 21);

    for (int i = 20; i >= 0; i--) {
        if (!is(stack2.pop(), i, 1)) {
            correct = false;
        }
    }

    check("copy constructor - copy has the same elements", correct);
    check("copy constructor - copy is empty after popping", stack2.isEmpty());
    check("copy constructor - original is untouched", stack1.getCount() == 21 && is(stack1.pop(), 20, 1));
}

void testCopyConstructorIndependent() {
    ComplexStack stack1;

    pushReals(stack1, 3);

    ComplexStack stack2(stack1);

    stack1.pop();
    stack1.push(ComplexNumber(9, 9));
    stack2.push(ComplexNumber(7, 7));

    check("copy constructor independent - original top", is(stack1.peek(), 9, 9));
    check("copy constructor independent - copy top", is(stack2.peek(), 7, 7));
    check("copy constructor independent - original count", stack1.getCount() == 3);
    check("copy constructor independent - copy count", stack2.getCount() == 4);
}

void testCopyConstructorEmpty() {
    ComplexStack stack1;
    ComplexStack stack2(stack1);

    check("copy constructor empty - copy is empty", stack2.isEmpty());

    stack2.push(ComplexNumber(5, 0));

    check("copy constructor empty - copy can be pushed to", is(stack2.pop(), 5, 0));
    check("copy constructor empty - original is still empty", stack1.isEmpty());
}

void testAssignFirstSmaller() {
    ComplexStack stack1;
    ComplexStack stack2;
    bool correct = true;

    stack1.push(ComplexNumber(7, 7));
    for (int i = 0; i <= 20; i++) {
        stack2.push(ComplexNumber(i * 2, 0));
    }

    stack1 = stack2;

    check("assign first smaller - count is copied", stack1.getCount() == 21);

    for (int i = 20; i >= 0; i--) {
        if (!is(stack1.pop(), i * 2, 0)) {
            correct = false;
        }
    }

    check("assign first smaller - all elements copied", correct);
    check("assign first smaller - source is untouched", stack2.getCount() == 21);
}

void testAssignFirstLarger() {
    ComplexStack stack1;
    ComplexStack stack2;
    double expected[] = {3, 2, 1};

    pushReals(stack1, 21);
    pushReals(stack2, 3);

    stack1 = stack2;

    check("assign first larger - exactly the source elements", popsReals(stack1, expected, 3));
}

void testAssignEmpty() {
    ComplexStack stack1;
    ComplexStack stack2;

    pushReals(stack1, 2);

    stack1 = stack2;

    check("assign empty - target is empty", stack1.isEmpty());

    stack1.push(ComplexNumber(3, 0));

    check("assign empty - target still usable", is(stack1.pop(), 3, 0));
}

void testAssignIndependent() {
    ComplexStack stack1;
    ComplexStack stack2;
    double expected[] = {3, 2, 1};

    pushReals(stack2, 3);

    stack1 = stack2;

    stack2.pop();
    stack2.push(ComplexNumber(99, 0));

    check("assign independent - changing source does not change target", popsReals(stack1, expected, 3));
}

void testAssignSelf() {
    ComplexStack stack;
    double expected[] = {2, 1};

    pushReals(stack, 2);

    ComplexStack& alias = stack;
    stack = alias;

    check("assign self - elements kept", popsReals(stack, expected, 2));
}

void testAssignChain() {
    ComplexStack stack1;
    ComplexStack stack2;
    ComplexStack stack3;

    pushReals(stack3, 2);

    stack1 = stack2 = stack3;

    check("assign chain - first target has the elements", stack1.getCount() == 2 && is(stack1.peek(), 2, 0));
    check("assign chain - second target has the elements", stack2.getCount() == 2 && is(stack2.peek(), 2, 0));
    check("assign chain - returns *this", &(stack1 = stack3) == &stack1);
}

ComplexNumber sumByPopping(ComplexStack stack) {
    ComplexNumber total;
    while (!stack.isEmpty()) {
        total += stack.pop();
    }
    return total;
}

void pushByReference(ComplexStack& stack) {
    stack.push(ComplexNumber(99, 0));
}

void testPassing() {
    ComplexStack stack;

    pushReals(stack, 3);

    check("pass by value - function sees the elements", is(sumByPopping(stack), 6, 0));
    check("pass by value - original is untouched", stack.getCount() == 3);

    pushByReference(stack);

    check("pass by reference - original is changed", is(stack.peek(), 99, 0));
}

// ===================== PART D - ComplexStack operators =====================

void testEqual() {
    ComplexStack stack1;
    ComplexStack stack2;
    ComplexStack empty1;
    ComplexStack empty2;

    pushReals(stack1, 3);
    pushReals(stack2, 4);
    stack2.pop();

    check("equal - same elements are equal", stack1 == stack2);
    check("equal - same elements are not different", !(stack1 != stack2));
    check("equal - two empty stacks are equal", empty1 == empty2);
    check("equal - stack equals itself", stack1 == stack1);
}

void testNotEqual() {
    ComplexStack stack1;
    ComplexStack stack2;
    ComplexStack stack3;
    ComplexStack empty;

    stack1.push(ComplexNumber(1, 1));
    stack1.push(ComplexNumber(2, 2));
    stack2.push(ComplexNumber(1, 1));
    stack2.push(ComplexNumber(2, -2));
    stack3.push(ComplexNumber(1, 1));

    check("not equal - imaginary part differs", stack1 != stack2);
    check("not equal - imaginary part differs is not equal", !(stack1 == stack2));
    check("not equal - different count", stack1 != stack3);
    check("not equal - shorter is prefix of longer", !(stack3 == stack1));
    check("not equal - empty vs non-empty", empty != stack3);
}

void testPlusStacks() {
    ComplexStack stack1;
    ComplexStack stack2;
    double expected[] = {4, 3, 2, 1};

    stack1.push(ComplexNumber(1, 0));
    stack1.push(ComplexNumber(2, 0));
    stack2.push(ComplexNumber(3, 0));
    stack2.push(ComplexNumber(4, 0));

    ComplexStack result = stack1 + stack2;

    check("plus stacks - left operand untouched", stack1.getCount() == 2 && is(stack1.peek(), 2, 0));
    check("plus stacks - right operand untouched", stack2.getCount() == 2 && is(stack2.peek(), 4, 0));
    check("plus stacks - right stack is placed on top of the left", popsReals(result, expected, 4));
}

void testPlusEmpty() {
    ComplexStack stack;
    ComplexStack empty;

    pushReals(stack, 2);

    ComplexStack result1 = stack + empty;
    ComplexStack result2 = empty + stack;
    ComplexStack result3 = empty + empty;

    check("plus empty - stack + empty == stack", result1 == stack);
    check("plus empty - empty + stack == stack", result2 == stack);
    check("plus empty - empty + empty is empty", result3.isEmpty());
}

void testPlusAssign() {
    ComplexStack stack1;
    ComplexStack stack2;
    double expected[] = {4, 3, 2, 1};

    stack1.push(ComplexNumber(1, 0));
    stack1.push(ComplexNumber(2, 0));
    stack2.push(ComplexNumber(3, 0));
    stack2.push(ComplexNumber(4, 0));

    stack1 += stack2;

    check("plus assign - right operand untouched", stack2.getCount() == 2);
    check("plus assign - right stack is placed on top", popsReals(stack1, expected, 4));
}

void testPlusAssignChain() {
    ComplexStack stack;
    ComplexStack other;
    double expected[] = {2, 2, 1};

    stack.push(ComplexNumber(1, 0));
    other.push(ComplexNumber(2, 0));

    (stack += other) += other;

    check("plus assign chain - (s += a) += a", popsReals(stack, expected, 3));
    check("plus assign chain - returns *this", &(stack += other) == &stack);
}

void testPlusAssignSelf() {
    ComplexStack stack;
    double expected[] = {3, 2, 1, 3, 2, 1};

    pushReals(stack, 3);

    stack += stack;

    check("plus assign self - stack += stack doubles the stack", popsReals(stack, expected, 6));
}

void testMultiply() {
    ComplexStack stack;

    stack.push(ComplexNumber(1, -1));
    stack.push(ComplexNumber(0.5, 2));

    ComplexStack right = stack * 2.0;
    ComplexStack left = 2.0 * stack;

    check("multiply - original untouched", stack.getCount() == 2 && is(stack.peek(), 0.5, 2));
    check("multiply - stack * double, top", is(right.pop(), 1, 4));
    check("multiply - stack * double, bottom", is(right.pop(), 2, -2));
    check("multiply - double * stack, top", is(left.pop(), 1, 4));
    check("multiply - double * stack, bottom", is(left.pop(), 2, -2));
}

void testMultiplyAssign() {
    ComplexStack stack;
    ComplexStack empty;

    stack.push(ComplexNumber(1, -1));
    stack.push(ComplexNumber(0.5, 2));

    (stack *= 2.0) *= 0.5;
    stack *= -1.0;
    empty *= 3.0;

    check("multiply assign - top", is(stack.pop(), -0.5, -2));
    check("multiply assign - bottom", is(stack.pop(), -1, 1));
    check("multiply assign - empty stays empty", empty.isEmpty());
    check("multiply assign - returns *this", &(stack *= 1.0) == &stack);
}

void testCombined() {
    ComplexStack stack1;
    ComplexStack stack2;

    stack1.push(ComplexNumber(1, 1));
    stack2.push(ComplexNumber(0, 2));
    stack2.push(ComplexNumber(-1, 0));

    ComplexStack result = 2.0 * (stack1 + stack2) * 0.5;

    check("combined - count", result.getCount() == 3);
    check("combined - sum", is(result.sum(), 0, 3));
    check("combined - equal to the plain concatenation", result == stack1 + stack2);
}

int main() {

    std::cout<<"===== PART A - ComplexNumber ====="<<std::endl;
    run("testComplexConstructor", testComplexConstructor);
    run("testComplexAddSubtract", testComplexAddSubtract);
    run("testComplexMultiplyDivide", testComplexMultiplyDivide);
    run("testComplexDoubleOnLeft", testComplexDoubleOnLeft);
    run("testComplexCompoundComplex", testComplexCompoundComplex);
    run("testComplexCompoundDouble", testComplexCompoundDouble);
    run("testComplexCompoundSelf", testComplexCompoundSelf);
    run("testComplexCompoundChain", testComplexCompoundChain);
    run("testComplexEqual", testComplexEqual);

    std::cout<<std::endl<<"===== PART B - basic ComplexStack ====="<<std::endl;
    run("testInit", testInit);
    run("testPushPop", testPushPop);
    run("testOrder", testOrder);
    run("testPushedCopy", testPushedCopy);
    run("testResize", testResize);
    run("testUnderflow", testUnderflow);
    run("testSum", testSum);

    std::cout<<std::endl<<"===== PART C - copy semantics ====="<<std::endl;
    run("testCopyConstructor", testCopyConstructor);
    run("testCopyConstructorIndependent", testCopyConstructorIndependent);
    run("testCopyConstructorEmpty", testCopyConstructorEmpty);
    run("testAssignFirstSmaller", testAssignFirstSmaller);
    run("testAssignFirstLarger", testAssignFirstLarger);
    run("testAssignEmpty", testAssignEmpty);
    run("testAssignIndependent", testAssignIndependent);
    run("testAssignSelf", testAssignSelf);
    run("testAssignChain", testAssignChain);
    run("testPassing", testPassing);

    std::cout<<std::endl<<"===== PART D - ComplexStack operators ====="<<std::endl;
    run("testEqual", testEqual);
    run("testNotEqual", testNotEqual);
    run("testPlusStacks", testPlusStacks);
    run("testPlusEmpty", testPlusEmpty);
    run("testPlusAssign", testPlusAssign);
    run("testPlusAssignChain", testPlusAssignChain);
    run("testPlusAssignSelf", testPlusAssignSelf);
    run("testMultiply", testMultiply);
    run("testMultiplyAssign", testMultiplyAssign);
    run("testCombined", testCombined);

    std::cout<<std::endl;
    std::cout<<passed<<" passed, "<<failed<<" failed"<<std::endl;

    if (failed == 0) {
        std::cout<<"All tests passed - mock test PASSED"<<std::endl;
    } else {
        std::cout<<"Mock test FAILED"<<std::endl;
    }

    return failed != 0;
}
