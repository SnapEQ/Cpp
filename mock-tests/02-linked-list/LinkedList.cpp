#include <cstddef>
#include <stdexcept>
#include <string>
#include "LinkedList.h"

// Every stub throws, so TestLinkedList.cpp reports it as FAIL instead of crashing.
// Remove the throwNotImplemented(...) line when you implement a function.
[[noreturn]] static void throwNotImplemented(const char* function) {
    throw std::logic_error(std::string(function) + " is not implemented");
}

void LinkedList::clear() {
    while (head != nullptr) {
        Node* temp = head->next;
        delete head;
        head = temp;
    }

    tail = nullptr;
    count = 0;

}

LinkedList::LinkedList()
: head(nullptr), tail(nullptr), count(0){
}

LinkedList::LinkedList(const LinkedList& other)
: head(nullptr), tail(nullptr), count(0) {

    const Node* dummy = other.head;

    while (dummy != nullptr) {
        this->pushBack(dummy->value);
        dummy = dummy->next;
    }


}

LinkedList& LinkedList::operator=(const LinkedList& other) {

    if (this == &other) {
        return *this;
    }

    clear();

    const Node* dummy = other.head;
    while (dummy != nullptr) {
        pushBack(dummy->value);
        dummy = dummy->next;
    }

    return *this;

}

LinkedList::~LinkedList() {
    clear();
}

bool LinkedList::isEmpty() const {
    return count == 0;
}

int LinkedList::getCount() const {
    return count;
}

void LinkedList::pushFront(int element) {

    Node* newNode = new Node{element, head};
    head = newNode;
    if (tail == nullptr) {
        tail = newNode;
    }
    count++;
}

void LinkedList::pushBack(int element) {
    Node* newNode = new Node{element, nullptr};

    if (head == nullptr) {
        head = newNode;
    } else {
        tail->next = newNode;
    }
    tail = newNode;
    count++;
}

int LinkedList::popFront() {

    if (head == nullptr) {
        throw std::underflow_error("Cannot pop from empty linked list");
    }

    Node* dummy = head;

    head = head->next;
    if(head == nullptr) {
        tail = nullptr;
    }

    count--;
    int res = dummy->value;
    delete dummy;
    return res;
}

int LinkedList::popBack() {

    if (head == nullptr) {
        throw std::underflow_error("Cannot pop from empty linked list");
    }

    Node *dummy = head;
    int res = tail->value;

    if (count == 1) {
        tail = nullptr;
        count--;
        delete head;
        head = nullptr;
        return res;
    }

    while (dummy->next != tail) {
        dummy = dummy->next; 
    }

    delete tail;
    tail = dummy;
    tail->next = nullptr;
    count--;

    return res;
}

int LinkedList::getFront() const {

    if (head == nullptr) {
        throw std::underflow_error("Cannot get front from empty linked list");
    }

    return head->value;
}

int LinkedList::getBack() const {

    if (head == nullptr) {
        throw std::underflow_error("Cannot get back from empty linked list");
    }

    return tail->value;
}

LinkedList LinkedList::operator+(const LinkedList& other) const {
    // TODO
    throwNotImplemented("operator+(const LinkedList&)");
}

LinkedList LinkedList::operator+(int element) const {
    // TODO
    throwNotImplemented("operator+(int)");
}

LinkedList& LinkedList::operator+=(const LinkedList& other) {
    // TODO
    throwNotImplemented("operator+=(const LinkedList&)");
}

LinkedList& LinkedList::operator+=(int element) {
    // TODO
    throwNotImplemented("operator+=(int)");
}

LinkedList LinkedList::operator-(int element) const {
    // TODO
    throwNotImplemented("operator-(int)");
}

LinkedList& LinkedList::operator-=(int element) {
    // TODO
    throwNotImplemented("operator-=(int)");
}

bool LinkedList::operator==(const LinkedList& other) const {
    // TODO
    throwNotImplemented("operator==");
}

bool LinkedList::operator!=(const LinkedList& other) const {
    // TODO
    throwNotImplemented("operator!=");
}

LinkedList operator+(int lhs, const LinkedList& rhs) {
    // TODO
    throwNotImplemented("operator+(int, const LinkedList&)");
}
