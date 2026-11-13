#include "Deque.h"

Deque::Node::Node(const Fraction& obj, Node* n) : data(obj.clone()), next(n) {}

Deque::Node::~Node() { delete data; }

Deque::Deque() : head_(nullptr), tail_(nullptr), size_(0) {}

Deque::Deque(const Deque& other) : head_(nullptr), tail_(nullptr), size_(0) {
    Node* curr = other.head_;
    while (curr != nullptr) {
        push_back(*(curr->data));
        curr = curr->next;
    }
}

Deque::~Deque() { clear(); }

Deque& Deque::operator=(const Deque& other) {
    if (this == &other) {
        return *this;
    }
    clear();
    Node* curr = other.head_;
    while (curr != nullptr) {
        push_back(*(curr->data));
        curr = curr->next;
    }
    return *this;
}

void Deque::push_front(const Fraction& obj) {
    Node* new_node = new Node(obj, head_);
    head_ = new_node;
    if (tail_ == nullptr) {
        tail_ = head_;
    }
    size_++;
}

void Deque::push_back(const Fraction& obj) {
    Node* new_node = new Node(obj, nullptr);
    if (tail_ != nullptr) {
        tail_->next = new_node;
        tail_ = new_node;
    } else {
        head_ = tail_ = new_node;
    }
    size_++;
}

bool Deque::pop_front() {
    if (head_ == nullptr) {
        return false;
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

bool Deque::insert_at(int index, const Fraction& obj) {
    if (index < 0 || index > size_) {
        return false;
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

bool Deque::remove_at(int index) {
    if (index < 0 || index >= size_) {
        return false;
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

int Deque::find(const Fraction& target) const {
    Node* curr = head_;
    int idx = 0;
    while (curr != nullptr) {
        if (curr->data->get_numerator() == target.get_numerator() &&
            curr->data->get_denominator() == target.get_denominator()) {
            return idx;
        }
        curr = curr->next;
        idx++;
    }
    return -1;
}

const Fraction* Deque::get(int index) const {
    if (index < 0 || index >= size_) {
        return nullptr;
    }
    Node* curr = head_;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr->data;
}

void Deque::print_all(std::ostream& os) const {
    Node* curr = head_;
    int idx = 0;
    while (curr != nullptr) {
        os << "[" << idx << "] " << curr->data->c_str() << '\n';
        curr = curr->next;
        idx++;
    }
}

int Deque::get_size() const { return size_; }

bool Deque::is_empty() const { return size_ == 0; }

void Deque::clear() {
    while (pop_front()) {
    }
}