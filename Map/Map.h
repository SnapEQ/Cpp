#pragma once

#include <iostream>

template <typename Key, typename Value>
class Map {
    private:
        struct Node {
            Key key;
            Value value;
            Node *next;

            Node(const Key& key, const Value& value) : key(key), value(value), next(nullptr) {}
        };

    Node* head;


    public:

    Map() : head(nullptr) {} 

    Map(const Map& other) : head(copyList(other.head)) {}

    void add(const Key& key, const Value& value) {

        Node* last = nullptr;

        for (Node* current = head; current != nullptr; current = current->next) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            last = current;
        }

        Node* newNode = new Node(key, value);
        if (last == nullptr) head = newNode;
        else last->next = newNode;
    }

    const Value* find(const Key& key) const {
        Node* current = head;
        while (current != nullptr) {
            if (current -> key == key) return &current->value;
            current = current->next;
        }
        return nullptr;
    }

    Value* find(const Key& key) {
        return const_cast<Value*>(static_cast<const Map*>(this)->find(key));
    }

    ~Map() {
        clear();
    }

    Map& operator=(const Map& other) {
        if (this == &other) {
            return *this;
        }
        Node* newHead = copyList(other.head);
        clear();
        head = newHead;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Map& map) {
        Node* curr = map.head;
        while(curr != nullptr) {
            os << curr->key << " : " << curr->value <<std::endl;
            curr = curr->next;
        }
        return os;
    }

    private:

    void clear() {
        deleteList(head);
        head = nullptr;
    }

    static void deleteList(Node* node) {
        while (node != nullptr) {
            Node* next = node->next;
            delete node;
            node = next;
        }
    }

    static Node* copyList(const Node* source) {
        Node* newHead = nullptr;
        Node* tail = nullptr;
        try {
            for (; source != nullptr; source = source->next) {
                Node* newNode = new Node(source->key, source->value);
                if (tail == nullptr) newHead = newNode;
                else tail->next = newNode;
                tail = newNode;
            }
        } catch (...) {
            deleteList(newHead);
            throw;
        }
        return newHead;
    }
};
