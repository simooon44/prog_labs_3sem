#include "EvaluatedFraction.h"

#include <cstdio>

// 4 lab

void EvaluatedFraction::compute_value() {
    if (get_denominator() == 0) {
        throw DivisionByZeroException(
            "EvaluatedFraction::compute_value: denominator is zero");
    }
    value_ = static_cast<double>(get_numerator()) / get_denominator();
}

EvaluatedFraction::EvaluatedFraction() : Fraction(0, 1), value_(0.0) {
    compute_value();
}

EvaluatedFraction::EvaluatedFraction(int num, int den)
    : Fraction(num, den), value_(0.0) {
    compute_value();
}

EvaluatedFraction::EvaluatedFraction(const Fraction& f)
    : Fraction(f), value_(0.0) {
    compute_value();
}

EvaluatedFraction::EvaluatedFraction(const EvaluatedFraction& other)
    : Fraction(other), value_(other.value_) {}

EvaluatedFraction::~EvaluatedFraction() {}

EvaluatedFraction& EvaluatedFraction::operator=(
    const EvaluatedFraction& other) {
    if (this == &other) {
        return *this;
    }
    Fraction::operator=(other);
    value_ = other.value_;
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
    if (!os) {
        throw FileIOException(
            "EvaluatedFraction operator<<: output stream error");
    }
    os << ef.c_str();
    return os;
}

std::istream& operator>>(std::istream& is, EvaluatedFraction& ef) {
    Fraction temp;
    if (is >> temp) {
        ef = temp;
    }
    return is;
}

// 5 lab

const char* EvaluatedFraction::c_str() const {
    char buffer[64];
    sprintf(buffer, "%d/%d (= %g)", get_numerator(), get_denominator(), value_);
    update_string_representation(buffer);
    return string_rep_;
}

Fraction* EvaluatedFraction::clone() const {
    return new EvaluatedFraction(*this);
}