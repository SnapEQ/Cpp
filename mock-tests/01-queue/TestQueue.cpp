#include <iostream>
#include <stdexcept>
#include "Queue.h"

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

// Empties the queue and checks it held exactly expected[0..n-1] in FIFO order.
bool drainEquals(Queue& queue, const int* expected, int n) {
    if (queue.getCount() != n) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (queue.dequeue() != expected[i]) {
            return false;
        }
    }
    return queue.isEmpty();
}

void testInit() {
    Queue queue;

    check("init - queue is empty", queue.isEmpty());
    check("init - count is 0", queue.getCount() == 0);
}

void testEnqueueDequeue() {
    Queue queue;

    queue.enqueue(50);

    check("enqueue - queue is not empty", !queue.isEmpty());
    check("enqueue - count is 1", queue.getCount() == 1);
    check("peek - returns the element", queue.peek() == 50);
    check("peek - does not remove the element", queue.getCount() == 1);
    check("dequeue - returns enqueued element", queue.dequeue() == 50);
    check("dequeue - queue is empty again", queue.isEmpty());
}

void testOrder() {
    Queue queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    check("order - peek returns the oldest element", queue.peek() == 1);
    check("order - first dequeue returns 1", queue.dequeue() == 1);
    check("order - second dequeue returns 2", queue.dequeue() == 2);
    check("order - third dequeue returns 3", queue.dequeue() == 3);
    check("order - queue is empty", queue.isEmpty());
}

void testResize() {
    Queue queue;
    bool correct = true;

    for (int i = 0; i < 100; i++) {
        queue.enqueue(i * 10);
    }

    check("resize - count is 100", queue.getCount() == 100);

    for (int i = 0; i < 100; i++) {
        if (queue.dequeue() != i * 10) {
            correct = false;
        }
    }

    check("resize - elements survived resizing", correct);
    check("resize - queue is empty", queue.isEmpty());
}

void testInterleaved() {
    Queue queue;
    bool correct = true;

    queue.enqueue(0);
    queue.enqueue(1);
    queue.enqueue(2);

    // keeps 3 elements inside while the front keeps moving forward
    for (int i = 3; i < 1000; i++) {
        queue.enqueue(i);
        if (queue.dequeue() != i - 3) {
            correct = false;
        }
    }

    check("interleaved - every dequeue returned the right element", correct);
    check("interleaved - count is 3", queue.getCount() == 3);
    check("interleaved - peek returns 997", queue.peek() == 997);
}

void testResizeAfterDequeue() {
    Queue queue;
    int expected[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.dequeue();
    queue.dequeue();

    for (int i = 4; i <= 12; i++) {
        queue.enqueue(i);
    }

    check("resize after dequeue - order is kept", drainEquals(queue, expected, 10));
}

void testUnderflow() {
    Queue queue;
    bool dequeueThrown = false;
    bool peekThrown = false;

    try {
        queue.dequeue();
    } catch (const std::underflow_error&) {
        dequeueThrown = true;
    }

    try {
        queue.peek();
    } catch (const std::underflow_error&) {
        peekThrown = true;
    }

    check("underflow - dequeue on empty queue throws", dequeueThrown);
    check("underflow - peek on empty queue throws", peekThrown);
    check("underflow - queue is still empty", queue.isEmpty());
}

void testUnderflowAfterDequeue() {
    Queue queue;
    bool thrown = false;

    queue.enqueue(10);
    queue.dequeue();

    try {
        queue.dequeue();
    } catch (const std::underflow_error&) {
        thrown = true;
    }

    check("underflow after dequeue - throws", thrown);

    queue.enqueue(20);

    check("underflow after dequeue - queue still usable", queue.dequeue() == 20);
}

void testCopyConstructor() {
    Queue queue1;
    bool correct = true;

    for (int i = 0; i <= 20; i++) {
        queue1.enqueue(i);
    }

    Queue queue2(queue1);

    check("copy constructor - copy has the same count", queue2.getCount() == 21);

    for (int i = 0; i <= 20; i++) {
        if (queue2.dequeue() != i) {
            correct = false;
        }
    }

    check("copy constructor - copy has the same elements", correct);
    check("copy constructor - copy is empty after dequeuing", queue2.isEmpty());
    check("copy constructor - original count untouched", queue1.getCount() == 21);
    check("copy constructor - original front untouched", queue1.dequeue() == 0);
}

void testCopyConstructorAfterDequeue() {
    Queue queue1;
    int expected[] = {3, 4, 5, 6, 7};

    for (int i = 0; i < 8; i++) {
        queue1.enqueue(i);
    }
    queue1.dequeue();
    queue1.dequeue();
    queue1.dequeue();

    Queue queue2(queue1);

    queue1.dequeue();
    queue1.enqueue(100);

    check("copy constructor after dequeue - copy is independent", drainEquals(queue2, expected, 5));
}

void testCopyConstructorEmpty() {
    Queue queue1;
    Queue queue2(queue1);

    check("copy constructor empty - copy is empty", queue2.isEmpty());

    queue2.enqueue(5);

    check("copy constructor empty - copy can be enqueued to", queue2.dequeue() == 5);
    check("copy constructor empty - original is still empty", queue1.isEmpty());
}

void testAssignFirstSmaller() {
    Queue queue1;
    Queue queue2;
    bool correct = true;

    queue1.enqueue(7);
    for (int i = 0; i <= 20; i++) {
        queue2.enqueue(i * 2);
    }

    queue1 = queue2;

    check("assign first smaller - count is copied", queue1.getCount() == 21);

    for (int i = 0; i <= 20; i++) {
        if (queue1.dequeue() != i * 2) {
            correct = false;
        }
    }

    check("assign first smaller - all elements copied", correct);
    check("assign first smaller - source is untouched", queue2.getCount() == 21);
}

void testAssignFirstLarger() {
    Queue queue1;
    Queue queue2;
    int expected[] = {0, 2, 4};

    for (int i = 0; i <= 20; i++) {
        queue1.enqueue(i);
    }
    for (int i = 0; i < 3; i++) {
        queue2.enqueue(i * 2);
    }

    queue1 = queue2;

    check("assign first larger - exactly the source elements", drainEquals(queue1, expected, 3));
}

void testAssignEmpty() {
    Queue queue1;
    Queue queue2;

    queue1.enqueue(1);
    queue1.enqueue(2);

    queue1 = queue2;

    check("assign empty - target is empty", queue1.isEmpty());

    queue1.enqueue(3);

    check("assign empty - target still usable", queue1.dequeue() == 3);
}

void testAssignIndependent() {
    Queue queue1;
    Queue queue2;
    int expected[] = {1, 2, 3};

    queue2.enqueue(1);
    queue2.enqueue(2);
    queue2.enqueue(3);

    queue1 = queue2;

    queue2.dequeue();
    queue2.enqueue(99);

    check("assign independent - changing source does not change target", drainEquals(queue1, expected, 3));
}

void testAssignSelf() {
    Queue queue;
    int expected[] = {10, 20};

    queue.enqueue(10);
    queue.enqueue(20);

    Queue& alias = queue;
    queue = alias;

    check("assign self - elements kept", drainEquals(queue, expected, 2));
}

void testAssignChain() {
    Queue queue1;
    Queue queue2;
    Queue queue3;

    queue3.enqueue(4);
    queue3.enqueue(5);

    queue1 = queue2 = queue3;

    check("assign chain - first target has the elements", queue1.getCount() == 2 && queue1.peek() == 4);
    check("assign chain - second target has the elements", queue2.getCount() == 2 && queue2.peek() == 4);
    check("assign chain - returns *this", &(queue1 = queue3) == &queue1);
}

int sumByValue(Queue queue) {
    int sum = 0;
    while (!queue.isEmpty()) {
        sum += queue.dequeue();
    }
    return sum;
}

void addByReference(Queue& queue) {
    queue.enqueue(99);
}

void testPassing() {
    Queue queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    check("pass by value - function sees the elements", sumByValue(queue) == 6);
    check("pass by value - original is untouched", queue.getCount() == 3);

    addByReference(queue);

    check("pass by reference - original is changed", queue.getCount() == 4);
}

void testEqual() {
    Queue queue1;
    Queue queue2;
    Queue empty1;
    Queue empty2;

    for (int i = 0; i < 5; i++) {
        queue1.enqueue(i);
    }
    // same elements, but reached in a different way (after some dequeues)
    queue2.enqueue(-2);
    queue2.enqueue(-1);
    for (int i = 0; i < 5; i++) {
        queue2.enqueue(i);
    }
    queue2.dequeue();
    queue2.dequeue();

    check("equal - same elements are equal", queue1 == queue2);
    check("equal - same elements are not different", !(queue1 != queue2));
    check("equal - two empty queues are equal", empty1 == empty2);
    check("equal - queue equals itself", queue1 == queue1);
}

void testNotEqual() {
    Queue queue1;
    Queue queue2;
    Queue queue3;
    Queue empty;

    queue1.enqueue(1);
    queue1.enqueue(2);
    queue2.enqueue(1);
    queue2.enqueue(3);
    queue3.enqueue(1);

    check("not equal - different element", queue1 != queue2);
    check("not equal - different element is not equal", !(queue1 == queue2));
    check("not equal - different count", queue1 != queue3);
    check("not equal - shorter is prefix of longer", !(queue3 == queue1));
    check("not equal - empty vs non-empty", empty != queue3);
}

void testPlusQueues() {
    Queue queue1;
    Queue queue2;
    int expected[] = {1, 2, 3, 4, 5};

    queue1.enqueue(1);
    queue1.enqueue(2);
    queue2.enqueue(3);
    queue2.enqueue(4);
    queue2.enqueue(5);

    Queue result = queue1 + queue2;

    check("plus queues - left operand untouched", queue1.getCount() == 2 && queue1.peek() == 1);
    check("plus queues - right operand untouched", queue2.getCount() == 3 && queue2.peek() == 3);
    check("plus queues - left elements first, then right", drainEquals(result, expected, 5));
}

void testPlusEmpty() {
    Queue queue;
    Queue empty;

    queue.enqueue(8);
    queue.enqueue(9);

    Queue result1 = queue + empty;
    Queue result2 = empty + queue;
    Queue result3 = empty + empty;

    check("plus empty - queue + empty == queue", result1 == queue);
    check("plus empty - empty + queue == queue", result2 == queue);
    check("plus empty - empty + empty is empty", result3.isEmpty());
}

void testPlusInt() {
    Queue queue;
    int expectedBack[] = {1, 2, 3};
    int expectedFront[] = {0, 1, 2};

    queue.enqueue(1);
    queue.enqueue(2);

    Queue back = queue + 3;
    Queue front = 0 + queue;

    check("plus int - original untouched", queue.getCount() == 2);
    check("plus int - queue + x puts x at the back", drainEquals(back, expectedBack, 3));
    check("plus int - x + queue puts x at the front", drainEquals(front, expectedFront, 3));
}

void testPlusChain() {
    Queue queue;
    int expected[] = {0, 1, 2, 3};

    queue.enqueue(1);
    queue.enqueue(2);

    Queue result = 0 + queue + 3;

    check("plus chain - 0 + queue + 3", drainEquals(result, expected, 4));
}

void testPlusAssignQueue() {
    Queue queue1;
    Queue queue2;
    int expected[] = {1, 2, 3, 4};

    queue1.enqueue(1);
    queue1.enqueue(2);
    queue2.enqueue(3);
    queue2.enqueue(4);

    queue1 += queue2;

    check("plus assign queue - right operand untouched", queue2.getCount() == 2 && queue2.peek() == 3);
    check("plus assign queue - elements appended", drainEquals(queue1, expected, 4));
}

void testPlusAssignInt() {
    Queue queue;
    int expected[] = {5, 6, 7};

    queue += 5;
    queue += 6;
    queue += 7;

    check("plus assign int - works like enqueue", drainEquals(queue, expected, 3));
}

void testPlusAssignChain() {
    Queue queue;
    Queue other;
    int expected[] = {1, 2, 3, 2, 3};

    other.enqueue(2);
    other.enqueue(3);

    queue += 1;
    (queue += other) += other;

    check("plus assign chain - (q += a) += a", drainEquals(queue, expected, 5));
    check("plus assign chain - returns *this", &(queue += 1) == &queue);
}

void testPlusAssignSelf() {
    Queue queue;
    int expected[] = {1, 2, 3, 1, 2, 3};

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    queue += queue;

    check("plus assign self - queue += queue doubles the queue", drainEquals(queue, expected, 6));
}

void testTwoQueues() {
    Queue queue1;
    Queue queue2;

    queue1.enqueue(20);
    queue1.enqueue(30);
    queue2.enqueue(10);
    queue2.enqueue(40);

    check("Queue 1 dequeue - returns 20", queue1.dequeue() == 20);
    check("Queue 2 dequeue - returns 10", queue2.dequeue() == 10);
    check("Queue 1 dequeue - returns 30", queue1.dequeue() == 30);
    check("Queue 2 dequeue - returns 40", queue2.dequeue() == 40);
}

int main() {

    run("testInit", testInit);
    run("testEnqueueDequeue", testEnqueueDequeue);
    run("testOrder", testOrder);
    run("testResize", testResize);
    run("testInterleaved", testInterleaved);
    run("testResizeAfterDequeue", testResizeAfterDequeue);
    run("testUnderflow", testUnderflow);
    run("testUnderflowAfterDequeue", testUnderflowAfterDequeue);
    run("testCopyConstructor", testCopyConstructor);
    run("testCopyConstructorAfterDequeue", testCopyConstructorAfterDequeue);
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
    run("testPlusQueues", testPlusQueues);
    run("testPlusEmpty", testPlusEmpty);
    run("testPlusInt", testPlusInt);
    run("testPlusChain", testPlusChain);
    run("testPlusAssignQueue", testPlusAssignQueue);
    run("testPlusAssignInt", testPlusAssignInt);
    run("testPlusAssignChain", testPlusAssignChain);
    run("testPlusAssignSelf", testPlusAssignSelf);
    run("testTwoQueues", testTwoQueues);

    std::cout<<std::endl;
    std::cout<<passed<<" passed, "<<failed<<" failed"<<std::endl;

    if (failed == 0) {
        std::cout<<"All tests passed - mock test PASSED"<<std::endl;
    } else {
        std::cout<<"Mock test FAILED"<<std::endl;
    }

    return failed != 0;
}
