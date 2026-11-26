#ifndef DEQUE_H_
#define DEQUE_H_

#include <cmath>
#include <iostream>

#include "Exceptions.h"

template <typename T>
class Deque {
   public:
    Deque();
    Deque(const Deque<T>& other);
    ~Deque();
    Deque<T>& operator=(const Deque<T>& other);

    void push_front(const T& obj);
    void push_back(const T& obj);
    bool pop_front();

    bool insert_at(int index, const T& obj);
    bool remove_at(int index);

    int find(const T& target) const;
    const T& get(int index) const;

    void print_all(std::ostream& os = std::cout) const;

    int get_size() const;
    bool is_empty() const;
    void clear();

   private:
    struct Node {
        T data;
        Node* next;

        Node(const T& obj, Node* n = nullptr);
    };

    Node* head_;
    Node* tail_;
    int size_;
};

template <typename T>
Deque<T>::Node::Node(const T& obj, Node* n) : data(obj), next(n) {}

template <typename T>
Deque<T>::Deque() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
Deque<T>::Deque(const Deque<T>& other)
    : head_(nullptr), tail_(nullptr), size_(0) {
    try {
        Node* curr = other.head_;
        while (curr != nullptr) {
            push_back(curr->data);
            curr = curr->next;
        }
    } catch (...) {
        clear();
        throw;
    }
}

template <typename T>
Deque<T>::~Deque() {
    clear();
}

template <typename T>
Deque<T>& Deque<T>::operator=(const Deque<T>& other) {
    if (this == &other) {
        return *this;
    }
    Deque<T> temp(other);
    Node* old_head = head_;
    Node* old_tail = tail_;
    int old_size = size_;

    head_ = temp.head_;
    tail_ = temp.tail_;
    size_ = temp.size_;

    temp.head_ = old_head;
    temp.tail_ = old_tail;
    temp.size_ = old_size;
    return *this;
}

template <typename T>
void Deque<T>::push_front(const T& obj) {
    Node* new_node = new Node(obj, head_);
    head_ = new_node;
    if (tail_ == nullptr) {
        tail_ = head_;
    }
    size_++;
}

template <typename T>
void Deque<T>::push_back(const T& obj) {
    Node* new_node = new Node(obj, nullptr);
    if (tail_ != nullptr) {
        tail_->next = new_node;
        tail_ = new_node;
    } else {
        head_ = tail_ = new_node;
    }
    size_++;
}

template <typename T>
bool Deque<T>::pop_front() {
    if (head_ == nullptr) {
        throw OutOfRangeException("Deque::pop_front: deque is empty");
    }
    Node* temp = head_;
    head_ = head_->next;
    if (head_ == nullptr) {
        tail_ = nullptr;
    }
    delete temp;
    size_--;
    return true;
}

template <typename T>
bool Deque<T>::insert_at(int index, const T& obj) {
    if (index < 0 || index > size_) {
        throw OutOfRangeException("Deque::insert_at: index out of range");
    }
    if (index == 0) {
        push_front(obj);
        return true;
    }
    if (index == size_) {
        push_back(obj);
        return true;
    }

    Node* prev = head_;
    for (int i = 0; i < index - 1; i++) {
        prev = prev->next;
    }
    Node* new_node = new Node(obj, prev->next);
    prev->next = new_node;
    size_++;
    return true;
}

template <typename T>
bool Deque<T>::remove_at(int index) {
    if (index < 0 || index >= size_) {
        throw OutOfRangeException("Deque::remove_at: index out of range");
    }
    if (index == 0) {
        return pop_front();
    }

    Node* prev = head_;
    for (int i = 0; i < index - 1; i++) {
        prev = prev->next;
    }
    Node* to_delete = prev->next;
    prev->next = to_delete->next;
    if (to_delete == tail_) {
        tail_ = prev;
    }
    delete to_delete;
    size_--;
    return true;
}

template <typename T>
int Deque<T>::find(const T& target) const {
    Node* curr = head_;
    int idx = 0;
    while (curr != nullptr) {
        if (curr->data == target) {
            return idx;
        }
        curr = curr->next;
        idx++;
    }
    return -1;
}

template <typename T>
const T& Deque<T>::get(int index) const {
    if (index < 0 || index >= size_) {
        throw OutOfRangeException("Deque::get: index out of range");
    }
    Node* curr = head_;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr->data;
}

template <typename T>
void Deque<T>::print_all(std::ostream& os) const {
    Node* curr = head_;
    int idx = 0;
    while (curr != nullptr) {
        os << "[" << idx << "] " << curr->data << '\n';
        curr = curr->next;
        idx++;
    }
}

template <typename T>
int Deque<T>::get_size() const {
    return size_;
}

template <typename T>
bool Deque<T>::is_empty() const {
    return size_ == 0;
}

template <typename T>
void Deque<T>::clear() {
    while (!is_empty()) {
        pop_front();
    }
}

// специализация метода
template <>
inline int Deque<float>::find(const float& target) const {
    const float eps = 1e-5f;
    Node* curr = head_;
    int idx = 0;
    while (curr != nullptr) {
        if (std::fabs(curr->data - target) < eps) {
            return idx;
        }
        curr = curr->next;
        idx++;
    }
    return -1;
}

// частичная специализация класса

template <typename T>
class Deque<T*> {
   public:
    Deque() : head_(nullptr), tail_(nullptr), size_(0) {}
    ~Deque() { clear(); }

    Deque(const Deque&) = delete;
    Deque& operator=(const Deque&) = delete;

    void push_front(T* const& obj) {
        Node* n = new Node(obj, head_);
        head_ = n;
        if (tail_ == nullptr) {
            tail_ = head_;
        }
        size_++;
    }

    void push_back(T* const& obj) {
        Node* n = new Node(obj, nullptr);
        if (tail_ != nullptr) {
            tail_->next = n;
            tail_ = n;
        } else {
            head_ = tail_ = n;
        }
        size_++;
    }

    bool pop_front() {
        if (head_ == nullptr) {
            throw OutOfRangeException("Deque<T*>::pop_front: deque is empty");
        }
        Node* temp = head_;
        head_ = head_->next;
        if (head_ == nullptr) {
            tail_ = nullptr;
        }
        delete temp;  // удаляется только узел, не объект
        size_--;
        return true;
    }

    T* const& get(int index) const {
        if (index < 0 || index >= size_) {
            throw OutOfRangeException("Deque<T*>::get: index out of range");
        }
        Node* curr = head_;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr->data;
    }

    int find(T* const& target) const {
        Node* curr = head_;
        int idx = 0;
        while (curr != nullptr) {
            if (curr->data != nullptr && target != nullptr &&
                *(curr->data) == *target) {
                return idx;
            }
            curr = curr->next;
            idx++;
        }
        return -1;
    }

    void print_all(std::ostream& os = std::cout) const {
        Node* curr = head_;
        int idx = 0;
        while (curr != nullptr) {
            os << "[" << idx << "] " << *(curr->data) << '\n';
            curr = curr->next;
            idx++;
        }
    }

    int get_size() const { return size_; }
    bool is_empty() const { return size_ == 0; }

    void clear() {
        while (!is_empty()) {
            pop_front();
        }
    }

   private:
    struct Node {
        T* data;
        Node* next;
        Node(T* d, Node* n) : data(d), next(n) {}
    };

    Node* head_;
    Node* tail_;
    int size_;
};

#endif