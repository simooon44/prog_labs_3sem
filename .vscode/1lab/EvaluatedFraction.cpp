#include "EvaluatedFraction.h"

#include <cstdio>
#include <cstring>

void EvaluatedFraction::compute_value() {
    if (get_denominator() != 0) {
        value_ = static_cast<double>(get_numerator()) / get_denominator();
    } else {
        value_ = 0.0;
    }
    update_string_representation();
}

EvaluatedFraction::EvaluatedFraction()
    : Fraction(0, 1), value_(0.0), string_rep_(nullptr) {
    update_string_representation();
}

EvaluatedFraction::EvaluatedFraction(int num, int den)
    : Fraction(num, den), value_(0.0), string_rep_(nullptr) {
    compute_value();
}

EvaluatedFraction::EvaluatedFraction(const Fraction& f)
    : Fraction(f), value_(0.0), string_rep_(nullptr) {
    compute_value();
}

EvaluatedFraction::EvaluatedFraction(const EvaluatedFraction& other)
    : Fraction(other), value_(other.value_), string_rep_(nullptr) {
    if (other.string_rep_) {
        string_rep_ = new char[strlen(other.string_rep_) + 1];
        strcpy(string_rep_, other.string_rep_);
    } else {
        update_string_representation();
    }
}

EvaluatedFraction::~EvaluatedFraction() { delete[] string_rep_; }

EvaluatedFraction& EvaluatedFraction::operator=(
    const EvaluatedFraction& other) {
    if (this == &other) {
        return *this;
    }
    Fraction::operator=(other);
    value_ = other.value_;

    delete[] string_rep_;
    if (other.string_rep_) {
        string_rep_ = new char[strlen(other.string_rep_) + 1];
        strcpy(string_rep_, other.string_rep_);
    } else {
        update_string_representation();
    }
    return *this;
}

EvaluatedFraction& EvaluatedFraction::operator=(const Fraction& other) {
    Fraction::operator=(other);
    compute_value();
    return *this;
}

double EvaluatedFraction::get_value() const { return value_; }

void EvaluatedFraction::set_values(int num, int den) {
    Fraction::set_values(num, den);
    compute_value();
}

std::ostream& operator<<(std::ostream& os, const EvaluatedFraction& ef) {
    ef.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, EvaluatedFraction& ef) {
    Fraction temp;
    if (is >> temp) {
        ef = temp;
    }
    return is;
}

// 5lab

void EvaluatedFraction::update_string_representation() {
    delete[] string_rep_;
    char buffer[64];
    sprintf(buffer, "%d/%d (= %g)", get_numerator(), get_denominator(), value_);
    string_rep_ = new char[strlen(buffer) + 1];
    strcpy(string_rep_, buffer);
}

const char* EvaluatedFraction::c_str() const { return string_rep_; }

Fraction* EvaluatedFraction::clone() const {
    return new EvaluatedFraction(*this);
}

void EvaluatedFraction::print(std::ostream& os) const { os << string_rep_; }