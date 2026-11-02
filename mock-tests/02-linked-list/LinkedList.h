#pragma once

// DO NOT change the public interface - TestLinkedList.cpp depends on it.
// You MAY change the private section (different members, helper methods).

class LinkedList {

    private:
        struct Node {
            int value;
            Node* next;
        };

        Node* head;
        Node* tail;
        int count;
        void clear();

    public:
        LinkedList();
        LinkedList(const LinkedList& other);
        LinkedList& operator=(const LinkedList& other);
        ~LinkedList();

        bool isEmpty() const;
        int getCount() const;
        void pushFront(int element);
        void pushBack(int element);
        int popFront();
        int popBack();
        int getFront() const;
        int getBack() const;

        LinkedList operator+(const LinkedList& other) const;
        LinkedList operator+(int element) const;
        LinkedList& operator+=(const LinkedList& other);
        LinkedList& operator+=(int element);
        LinkedList operator-(int element) const;
        LinkedList& operator-=(int element);
        bool operator==(const LinkedList& other) const;
        bool operator!=(const LinkedList& other) const;
};

LinkedList operator+(int lhs, const LinkedList& rhs);
