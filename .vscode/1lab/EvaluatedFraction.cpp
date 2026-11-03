#include "EvaluatedFraction.h"

void EvaluatedFraction::compute_value() {
    if (get_denominator() != 0) {
        value_ = static_cast<double>(get_numerator()) / get_denominator();
    } else {
        value_ = 0.0;
    }
}

EvaluatedFraction::EvaluatedFraction() : Fraction(0, 1), value_(0.0) {}

EvaluatedFraction::EvaluatedFraction(int num, int den) : Fraction(num, den) {
    compute_value();
}

EvaluatedFraction::EvaluatedFraction(const Fraction& f) : Fraction(f) {
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
    os << static_cast<const Fraction&>(ef) << " (= " << ef.value_ << ")";
    return os;
}

std::istream& operator>>(std::istream& is, EvaluatedFraction& ef) {
    Fraction temp;
    if (is >> temp) {
        ef = temp;
    }
    return is;
}