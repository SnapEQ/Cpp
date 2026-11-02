#include <iostream>
#include <stdexcept>
#include "LinkedList.h"

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

// Empties the list from the front and checks it held exactly expected[0..n-1].
bool drainEquals(LinkedList& list, const int* expected, int n) {
    if (list.getCount() != n) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (list.popFront() != expected[i]) {
            return false;
        }
    }
    return list.isEmpty();
}

void testInit() {
    LinkedList list;

    check("init - list is empty", list.isEmpty());
    check("init - count is 0", list.getCount() == 0);
}

void testPushBack() {
    LinkedList list;
    int expected[] = {1, 2, 3};

    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);

    check("push back - count is 3", list.getCount() == 3);
    check("push back - front is 1", list.getFront() == 1);
    check("push back - back is 3", list.getBack() == 3);
    check("push back - order", drainEquals(list, expected, 3));
}

void testPushFront() {
    LinkedList list;
    int expected[] = {3, 2, 1};

    list.pushFront(1);
    list.pushFront(2);
    list.pushFront(3);

    check("push front - front is 3", list.getFront() == 3);
    check("push front - back is 1", list.getBack() == 1);
    check("push front - order", drainEquals(list, expected, 3));
}

void testPushMixed() {
    LinkedList list;
    int expected[] = {1, 2, 3, 4};

    list.pushFront(2);
    list.pushBack(3);
    list.pushFront(1);
    list.pushBack(4);

    check("push mixed - order", drainEquals(list, expected, 4));
}

void testPopBack() {
    LinkedList list;

    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);

    check("pop back - returns 3", list.popBack() == 3);
    check("pop back - new back is 2", list.getBack() == 2);
    check("pop back - returns 2", list.popBack() == 2);
    check("pop back - front and back are the same", list.getFront() == 1 && list.getBack() == 1);
    check("pop back - returns 1", list.popBack() == 1);
    check("pop back - list is empty", list.isEmpty());
}

void testReuseAfterEmptying() {
    LinkedList list;
    int expected[] = {7, 8};

    list.pushBack(1);
    list.pushBack(2);
    list.popBack();
    list.popFront();

    list.pushBack(7);
    list.pushBack(8);

    check("reuse after emptying - front is 7", list.getFront() == 7);
    check("reuse after emptying - back is 8", list.getBack() == 8);
    check("reuse after emptying - order", drainEquals(list, expected, 2));
}

void testPushBackAfterPopFront() {
    LinkedList list;
    int expected[] = {9};

    list.pushBack(1);
    list.popFront();
    list.pushBack(9);

    check("push back after pop front - back is 9", list.getBack() == 9);
    check("push back after pop front - only element", drainEquals(list, expected, 1));
}

void testMany() {
    LinkedList list;
    bool correct = true;

    for (int i = 0; i < 1000; i++) {
        list.pushBack(i);
    }

    check("many - count is 1000", list.getCount() == 1000);

    for (int i = 999; i >= 500; i--) {
        if (list.popBack() != i) {
            correct = false;
        }
    }
    for (int i = 0; i < 500; i++) {
        if (list.popFront() != i) {
            correct = false;
        }
    }

    check("many - all elements came back", correct);
    check("many - list is empty", list.isEmpty());
}

void testUnderflow() {
    LinkedList list;
    int thrown = 0;

    try {
        list.popFront();
    } catch (const std::underflow_error&) {
        thrown++;
    }
    try {
        list.popBack();
    } catch (const std::underflow_error&) {
        thrown++;
    }
    try {
        list.getFront();
    } catch (const std::underflow_error&) {
        thrown++;
    }
    try {
        list.getBack();
    } catch (const std::underflow_error&) {
        thrown++;
    }

    check("underflow - all 4 functions throw on empty list", thrown == 4);
    check("underflow - list is still empty", list.isEmpty());
}

void testCopyConstructor() {
    LinkedList list1;
    bool correct = true;

    for (int i = 0; i <= 20; i++) {
        list1.pushBack(i);
    }

    LinkedList list2(list1);

    check("copy constructor - copy has the same count", list2.getCount() == 21);

    for (int i = 0; i <= 20; i++) {
        if (list2.popFront() != i) {
            correct = false;
        }
    }

    check("copy constructor - copy has the same elements", correct);
    check("copy constructor - original count untouched", list1.getCount() == 21);
    check("copy constructor - original front untouched", list1.getFront() == 0);
}

void testCopyConstructorBack() {
    LinkedList list1;

    list1.pushBack(1);
    list1.pushBack(2);

    LinkedList list2(list1);

    list2.pushBack(3);
    list1.pushBack(4);

    check("copy constructor back - copy's back is its own", list2.getBack() == 3);
    check("copy constructor back - original's back is its own", list1.getBack() == 4);
    check("copy constructor back - copy count", list2.getCount() == 3);
    check("copy constructor back - original count", list1.getCount() == 3);
}

void testCopyConstructorEmpty() {
    LinkedList list1;
    LinkedList list2(list1);

    check("copy constructor empty - copy is empty", list2.isEmpty());

    list2.pushBack(5);

    check("copy constructor empty - copy can be pushed to", list2.getBack() == 5);
    check("copy constructor empty - original is still empty", list1.isEmpty());
}

void testAssignFirstSmaller() {
    LinkedList list1;
    LinkedList list2;
    bool correct = true;

    list1.pushBack(7);
    for (int i = 0; i <= 20; i++) {
        list2.pushBack(i * 2);
    }

    list1 = list2;

    check("assign first smaller - count is copied", list1.getCount() == 21);

    for (int i = 0; i <= 20; i++) {
        if (list1.popFront() != i * 2) {
            correct = false;
        }
    }

    check("assign first smaller - all elements copied", correct);
    check("assign first smaller - source is untouched", list2.getCount() == 21);
}

void testAssignFirstLarger() {
    LinkedList list1;
    LinkedList list2;
    int expected[] = {0, 2, 4};

    for (int i = 0; i <= 20; i++) {
        list1.pushBack(i);
    }
    for (int i = 0; i < 3; i++) {
        list2.pushBack(i * 2);
    }

    list1 = list2;

    check("assign first larger - back is the source's back", list1.getBack() == 4);
    check("assign first larger - exactly the source elements", drainEquals(list1, expected, 3));
}

void testAssignEmpty() {
    LinkedList list1;
    LinkedList list2;

    list1.pushBack(1);
    list1.pushBack(2);

    list1 = list2;

    check("assign empty - target is empty", list1.isEmpty());

    list1.pushBack(3);

    check("assign empty - target still usable", list1.getFront() == 3 && list1.getBack() == 3);
}

void testAssignIndependent() {
    LinkedList list1;
    LinkedList list2;
    int expected[] = {1, 2, 3};

    list2.pushBack(1);
    list2.pushBack(2);
    list2.pushBack(3);

    list1 = list2;

    list2.popFront();
    list2.pushBack(99);
    list1.pushBack(4);
    list1.popBack();

    check("assign independent - source is unchanged by target", list2.getBack() == 99 && list2.getCount() == 3);
    check("assign independent - target is unchanged by source", drainEquals(list1, expected, 3));
}

void testAssignSelf() {
    LinkedList list;
    int expected[] = {10, 20};

    list.pushBack(10);
    list.pushBack(20);

    LinkedList& alias = list;
    list = alias;

    check("assign self - elements kept", drainEquals(list, expected, 2));
}

void testAssignChain() {
    LinkedList list1;
    LinkedList list2;
    LinkedList list3;

    list3.pushBack(4);
    list3.pushBack(5);

    list1 = list2 = list3;

    check("assign chain - first target has the elements", list1.getCount() == 2 && list1.getFront() == 4);
    check("assign chain - second target has the elements", list2.getCount() == 2 && list2.getBack() == 5);
    check("assign chain - returns *this", &(list1 = list3) == &list1);
}

int sumByValue(LinkedList list) {
    int sum = 0;
    while (!list.isEmpty()) {
        sum += list.popFront();
    }
    return sum;
}

void addByReference(LinkedList& list) {
    list.pushBack(99);
}

void testPassing() {
    LinkedList list;

    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);

    check("pass by value - function sees the elements", sumByValue(list) == 6);
    check("pass by value - original is untouched", list.getCount() == 3);

    addByReference(list);

    check("pass by reference - original is changed", list.getBack() == 99);
}

void testEqual() {
    LinkedList list1;
    LinkedList list2;
    LinkedList empty1;
    LinkedList empty2;

    list1.pushBack(1);
    list1.pushBack(2);
    list1.pushBack(3);
    list2.pushFront(3);
    list2.pushFront(2);
    list2.pushFront(1);

    check("equal - same elements are equal", list1 == list2);
    check("equal - same elements are not different", !(list1 != list2));
    check("equal - two empty lists are equal", empty1 == empty2);
    check("equal - list equals itself", list1 == list1);
}

void testNotEqual() {
    LinkedList list1;
    LinkedList list2;
    LinkedList list3;
    LinkedList empty;

    list1.pushBack(1);
    list1.pushBack(2);
    list2.pushBack(1);
    list2.pushBack(3);
    list3.pushBack(1);

    check("not equal - different element", list1 != list2);
    check("not equal - different element is not equal", !(list1 == list2));
    check("not equal - different count", list1 != list3);
    check("not equal - shorter is prefix of longer", !(list3 == list1));
    check("not equal - empty vs non-empty", empty != list3);
}

void testPlusLists() {
    LinkedList list1;
    LinkedList list2;
    int expected[] = {1, 2, 3, 4, 5};

    list1.pushBack(1);
    list1.pushBack(2);
    list2.pushBack(3);
    list2.pushBack(4);
    list2.pushBack(5);

    LinkedList result = list1 + list2;

    check("plus lists - left operand untouched", list1.getCount() == 2 && list1.getBack() == 2);
    check("plus lists - right operand untouched", list2.getCount() == 3 && list2.getFront() == 3);
    check("plus lists - result back", result.getBack() == 5);
    check("plus lists - left elements first, then right", drainEquals(result, expected, 5));
}

void testPlusEmpty() {
    LinkedList list;
    LinkedList empty;

    list.pushBack(8);
    list.pushBack(9);

    LinkedList result1 = list + empty;
    LinkedList result2 = empty + list;
    LinkedList result3 = empty + empty;

    check("plus empty - list + empty == list", result1 == list);
    check("plus empty - empty + list == list", result2 == list);
    check("plus empty - empty + empty is empty", result3.isEmpty());
}

void testPlusInt() {
    LinkedList list;
    int expectedBack[] = {1, 2, 3};
    int expectedFront[] = {0, 1, 2};

    list.pushBack(1);
    list.pushBack(2);

    LinkedList back = list + 3;
    LinkedList front = 0 + list;

    check("plus int - original untouched", list.getCount() == 2 && list.getBack() == 2);
    check("plus int - list + x puts x at the back", drainEquals(back, expectedBack, 3));
    check("plus int - x + list puts x at the front", drainEquals(front, expectedFront, 3));
}

void testPlusChain() {
    LinkedList list;
    int expected[] = {0, 1, 2, 3};

    list.pushBack(1);
    list.pushBack(2);

    LinkedList result = 0 + list + 3;

    check("plus chain - 0 + list + 3", drainEquals(result, expected, 4));
}

void testPlusAssignList() {
    LinkedList list1;
    LinkedList list2;
    int expected[] = {1, 2, 3, 4};

    list1.pushBack(1);
    list1.pushBack(2);
    list2.pushBack(3);
    list2.pushBack(4);

    list1 += list2;
    list2.pushBack(5);

    check("plus assign list - right operand only has its own change", list2.getCount() == 3);
    check("plus assign list - elements were copied, not linked", list1.getBack() == 4);
    check("plus assign list - elements appended", drainEquals(list1, expected, 4));
}

void testPlusAssignInt() {
    LinkedList list;
    int expected[] = {5, 6, 7};

    list += 5;
    list += 6;
    list += 7;

    check("plus assign int - works like pushBack", drainEquals(list, expected, 3));
}

void testPlusAssignChain() {
    LinkedList list;
    LinkedList other;
    int expected[] = {1, 2, 3, 2, 3};

    other.pushBack(2);
    other.pushBack(3);

    list += 1;
    (list += other) += other;

    check("plus assign chain - (l += a) += a", drainEquals(list, expected, 5));
    check("plus assign chain - returns *this", &(list += 1) == &list);
}

void testPlusAssignSelf() {
    LinkedList list;
    int expected[] = {1, 2, 3, 1, 2, 3};

    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);

    list += list;

    check("plus assign self - list += list doubles the list", drainEquals(list, expected, 6));
}

void testMinusAssign() {
    LinkedList list;
    int expected[] = {1, 2, 4};

    list.pushBack(3);
    list.pushBack(1);
    list.pushBack(3);
    list.pushBack(3);
    list.pushBack(2);
    list.pushBack(4);

    list -= 3;

    check("minus assign - count after removing every 3", list.getCount() == 3);
    check("minus assign - front updated", list.getFront() == 1);
    check("minus assign - remaining elements", drainEquals(list, expected, 3));
}

void testMinusAssignBack() {
    LinkedList list;
    int expected[] = {1, 2, 9};

    list.pushBack(1);
    list.pushBack(5);
    list.pushBack(2);
    list.pushBack(5);
    list.pushBack(5);

    list -= 5;

    check("minus assign back - back updated", list.getBack() == 2);

    list.pushBack(9);

    check("minus assign back - push back after removing the tail", drainEquals(list, expected, 3));
}

void testMinusAssignEverything() {
    LinkedList list;

    list.pushBack(4);
    list.pushBack(4);
    list.pushBack(4);

    list -= 4;

    check("minus assign everything - list is empty", list.isEmpty());

    list.pushBack(1);

    check("minus assign everything - list still usable", list.getFront() == 1 && list.getBack() == 1);
}

void testMinusAssignMissing() {
    LinkedList list;
    LinkedList empty;
    int expected[] = {1, 2};

    list.pushBack(1);
    list.pushBack(2);

    list -= 42;
    empty -= 42;

    check("minus assign missing - empty stays empty", empty.isEmpty());
    check("minus assign missing - nothing removed", drainEquals(list, expected, 2));
    check("minus assign missing - returns *this", &(list -= 1) == &list);
}

void testMinus() {
    LinkedList list;
    int expectedResult[] = {2, 4};
    int expectedOriginal[] = {1, 2, 1, 4};

    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(1);
    list.pushBack(4);

    LinkedList result = list - 1;

    check("minus - result has every 1 removed", drainEquals(result, expectedResult, 2));
    check("minus - original untouched", drainEquals(list, expectedOriginal, 4));
}

void testTwoLists() {
    LinkedList list1;
    LinkedList list2;

    list1.pushBack(20);
    list1.pushBack(30);
    list2.pushBack(10);
    list2.pushBack(40);

    check("List 1 pop front - returns 20", list1.popFront() == 20);
    check("List 2 pop back - returns 40", list2.popBack() == 40);
    check("List 1 pop back - returns 30", list1.popBack() == 30);
    check("List 2 pop front - returns 10", list2.popFront() == 10);
}

int main() {

    run("testInit", testInit);
    run("testPushBack", testPushBack);
    run("testPushFront", testPushFront);
    run("testPushMixed", testPushMixed);
    run("testPopBack", testPopBack);
    run("testReuseAfterEmptying", testReuseAfterEmptying);
    run("testPushBackAfterPopFront", testPushBackAfterPopFront);
    run("testMany", testMany);
    run("testUnderflow", testUnderflow);
    run("testCopyConstructor", testCopyConstructor);
    run("testCopyConstructorBack", testCopyConstructorBack);
    run("testCopyConstructorEmpty", testCopyConstructorEmpty);
    run("testAssignFirstSmaller", testAssignFirstSmaller);
    run("testAssignFirstLarger", testAssignFirstLarger);
    run("testAssignEmpty", testAssignEmpty);
    run("testAssignIndependent", testAssignIndependent);
    run("testAssignSelf", testAssignSelf);
    run("testAssignChain", testAssignChain);
    run("testPassing", testPassing);
    run("testEqual", testEqual);
    run("testNotEqual", testNotEqual);
    run("testPlusLists", testPlusLists);
    run("testPlusEmpty", testPlusEmpty);
    run("testPlusInt", testPlusInt);
    run("testPlusChain", testPlusChain);
    run("testPlusAssignList", testPlusAssignList);
    run("testPlusAssignInt", testPlusAssignInt);
    run("testPlusAssignChain", testPlusAssignChain);
    run("testPlusAssignSelf", testPlusAssignSelf);
    run("testMinusAssign", testMinusAssign);
    run("testMinusAssignBack", testMinusAssignBack);
    run("testMinusAssignEverything", testMinusAssignEverything);
    run("testMinusAssignMissing", testMinusAssignMissing);
    run("testMinus", testMinus);
    run("testTwoLists", testTwoLists);

    std::cout<<std::endl;
    std::cout<<passed<<" passed, "<<failed<<" failed"<<std::endl;

    if (failed == 0) {
        std::cout<<"All tests passed - mock test PASSED"<<std::endl;
    } else {
        std::cout<<"Mock test FAILED"<<std::endl;
    }

    return failed != 0;
}
