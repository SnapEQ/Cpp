#pragma once

// DO NOT change the public interface - TestQueue.cpp depends on it.
// You MAY change the private section (different members, helper methods).

class Queue {

    private:
        int* queue;
        int size;   // allocated capacity
        int head;   // index of the first (oldest) element
        int count;  // number of stored elements
        void copyElementsTo(int* dest) const;

    public:
        Queue();
        Queue(const Queue& other);
        Queue& operator=(const Queue& other);
        ~Queue();

        bool isEmpty() const;
        int getCount() const;
        void enqueue(int element);
        int dequeue();
        int peek() const;

        Queue operator+(const Queue& other) const;
        Queue operator+(int element) const;
        Queue& operator+=(const Queue& other);
        Queue& operator+=(int element);
        bool operator==(const Queue& other) const;
        bool operator!=(const Queue& other) const;
};

Queue operator+(int lhs, const Queue& rhs);
