#include <stdlib.h>
#include <stdexcept>
#include <string>
#include "Queue.h"

// Every stub throws, so TestQueue.cpp reports it as FAIL instead of crashing.
// Remove the throwNotImplemented(...) line when you implement a function.
[[noreturn]] static void throwNotImplemented(const char* function) {
    throw std::logic_error(std::string(function) + " is not implemented");
}

void Queue::copyElementsTo(int *dest) const {
    for (int i = 0; i < count; ++i) {
        dest[i] = queue[(head + i)% size];
    }
}

Queue::Queue() {
    this->queue = new int[2];
    this->size = 2;
    this->head = 0;
    this->count = 0;
}

Queue::Queue(const Queue& other)
:queue(new int[other.size]), size(other.size), head(0), count(other.count) {
    other.copyElementsTo(queue);
}

Queue& Queue::operator=(const Queue& other) {

    if (this == &other) {
        return *this;
    }

    int *temp = new int[other.size];

    other.copyElementsTo(temp);

    delete[] queue;
    queue = temp;
    size = other.size;
    count = other.count;
    head = 0;

    return *this;
}

Queue::~Queue() {
    delete[] queue;
}

bool Queue::isEmpty() const {
    return count == 0;
}

int Queue::getCount() const {
    return count;
}

void Queue::enqueue(int element) {
    if (count == size) {
        int *temp = new int[size * 2];
        this->copyElementsTo(temp);
        delete[] queue;
        queue = temp;
        head = 0;
        size *= 2;
    }

    int idx = (head + count) % size;
    queue[idx] = element;
    count++;
}

int Queue::dequeue() {
    if (isEmpty()) {
        throw std::underflow_error("dequeue on an empty queue");
    }
    int temp = queue[head];
    head = (head + 1) % size;
    count--;
    return temp;
}

int Queue::peek() const {
    if (isEmpty()) {
        throw std::underflow_error("peek on an empty queue");
    }
    return queue[head];
}

Queue Queue::operator+(const Queue& other) const {
    Queue res(*this);
    res += other;
    return res;
}

Queue Queue::operator+(int element) const {
    Queue res;
    res += *this;
    res.enqueue(element);
    return res;
}

Queue& Queue::operator+=(const Queue& other) {

    int n = other.count;

    for (int i = 0; i < n; ++i) {
        this->enqueue(other.queue[(other.head+i)%other.size]);
    }
    return *this;
}

Queue& Queue::operator+=(int element) {
    this->enqueue(element);
    return *this;
}

bool Queue::operator==(const Queue& other) const {
    if (count != other.count) {
        return false;
    }

    for (int i = 0; i < count; ++i) {
        if (queue[(head+i)%size] != other.queue[(other.head+i)%other.size]) {
            return false;
        }
    }

    return true;
}

bool Queue::operator!=(const Queue& other) const {
    return !(*this == other);
}

Queue operator+(int lhs, const Queue& rhs) {
    Queue res;

    res.enqueue(lhs);
    res += rhs;

    return res;
}
