#include "Fraction.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int Fraction::object_count_ = 0;

int Fraction::gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return abs(a);
}

void Fraction::update_string_representation() {
    delete[] string_rep_;

    char buffer[64];
    sprintf(buffer, "%d/%d", numerator_, denominator_);

    string_rep_ = new char[strlen(buffer) + 1];
    strcpy(string_rep_, buffer);
}

Fraction::Fraction() : Fraction(0, 1) {}

Fraction::Fraction(int num, int den)
    : numerator_(num), denominator_(den), string_rep_(nullptr) {
    if (denominator_ == 0) {
        denominator_ = 1;
    }

    int common_div = gcd(numerator_, denominator_);
    numerator_ /= common_div;
    denominator_ /= common_div;

    if (denominator_ < 0) {
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }

    update_string_representation();
    object_count_++;
}

Fraction::Fraction(const Fraction& other)
    : numerator_(other.numerator_),
      denominator_(other.denominator_),
      string_rep_(nullptr) {
    // можно и как обычно, но меня удивил метод
    if (other.string_rep_) {
        string_rep_ = new char[strlen(other.string_rep_) + 1];
        strcpy(string_rep_, other.string_rep_);
    } else {
        update_string_representation();
    }
    object_count_++;
}

Fraction::~Fraction() {
    delete[] string_rep_;
    object_count_--;
}

int Fraction::get_object_count() { return object_count_; }

int Fraction::get_numerator() const { return numerator_; }
int Fraction::get_denominator() const { return denominator_; }

const char* Fraction::c_str() const { return string_rep_; }

void Fraction::set_values(int num, int den) {
    if (den == 0) return;
    numerator_ = num;
    denominator_ = den;

    int common_div = gcd(numerator_, denominator_);
    numerator_ /= common_div;
    denominator_ /= common_div;

    if (denominator_ < 0) {
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }

    update_string_representation();
}

Fraction Fraction::add(const Fraction& other) const {
    return Fraction(
        numerator_ * other.denominator_ + other.numerator_ * denominator_,
        denominator_ * other.denominator_);
}

Fraction Fraction::substract(const Fraction& other) const {
    return Fraction(
        numerator_ * other.denominator_ - other.numerator_ * denominator_,
        denominator_ * other.denominator_);
}

Fraction Fraction::multiply(const Fraction& other) const {
    return Fraction(numerator_ * other.numerator_,
                    denominator_ * other.denominator_);
}

Fraction Fraction::divide(const Fraction& other) const {
    if (other.numerator_ == 0) return Fraction(0, 1);
    return Fraction(numerator_ * other.denominator_,
                    denominator_ * other.numerator_);
}

// 2 lab

Fraction& Fraction::operator=(const Fraction& other) {
    if (this == &other) {
        return *this;
    }

    numerator_ = other.numerator_;
    denominator_ = other.denominator_;

    delete[] string_rep_;
    if (other.string_rep_) {
        string_rep_ = new char[strlen(other.string_rep_) + 1];
        strcpy(string_rep_, other.string_rep_);
    } else {
        string_rep_ = nullptr;
    }

    return *this;
}

Fraction::operator float() const {
    return static_cast<float>(numerator_) / static_cast<float>(denominator_);
}

Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(
        lhs.numerator_ * rhs.denominator_ + rhs.numerator_ * lhs.denominator_,
        lhs.denominator_ * rhs.denominator_);
}
Fraction operator-(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(
        lhs.numerator_ * rhs.denominator_ - rhs.numerator_ * lhs.denominator_,
        lhs.denominator_ * rhs.denominator_);
}

// 3lab

ostream& operator<<(ostream& os, const Fraction& fraction) {
    os << fraction.numerator_ << "/" << fraction.denominator_;
    return os;
}

istream& operator>>(istream& is, Fraction& fraction) {
    int num = 0;
    int den = 1;

    if (!(is >> num)) {
        return is;
    }

    while (is.peek() == ' ' || is.peek() == '\t') {
        is.get();
    }

    if (is.peek() == '/') {
        is.get();
        is >> den;
    }

    fraction.set_values(num, den);
    return is;
}