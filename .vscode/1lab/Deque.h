#ifndef DEQUE_H_
#define DEQUE_H_

#include <iostream>

#include "Fraction.h"

class Deque {
   public:
    Deque();
    Deque(const Deque& other);
    ~Deque();
    Deque& operator=(const Deque& other);

    void push_front(const Fraction& obj);
    void push_back(const Fraction& obj);

    bool pop_front();

    bool insert_at(int index, const Fraction& obj);
    bool remove_at(int index);

    int find(const Fraction& target) const;
    const Fraction* get(int index) const;

    void print_all(std::ostream& os = std::cout) const;

    int get_size() const;
    bool is_empty() const;
    void clear();

   private:
    struct Node {
        Fraction* data;
        Node* next;

        Node(const Fraction& obj, Node* n = nullptr);
        ~Node();
    };

    Node* head_;
    Node* tail_;
    int size_;
};

#endif