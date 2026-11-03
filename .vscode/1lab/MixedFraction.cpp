#include "MixedFraction.h"

#include <cmath>
#include <cstring>

void MixedFraction::update_whole_part() {
    whole_part_ = get_numerator() / get_denominator();
}

MixedFraction::MixedFraction() : Fraction(0, 1), whole_part_(0) {}

MixedFraction::MixedFraction(int num, int den) : Fraction(num, den) {
    update_whole_part();
}

MixedFraction::MixedFraction(int whole, int num, int den) {
    set_mixed(whole, num, den);
}

MixedFraction::MixedFraction(const Fraction& f) : Fraction(f) {
    update_whole_part();
}

MixedFraction::MixedFraction(const MixedFraction& other)
    : Fraction(other), whole_part_(other.whole_part_) {}

MixedFraction::~MixedFraction() {}

MixedFraction& MixedFraction::operator=(const MixedFraction& other) {
    if (this == &other) {
        return *this;
    }
    Fraction::operator=(other);
    whole_part_ = other.whole_part_;
    return *this;
}

MixedFraction& MixedFraction::operator=(const Fraction& other) {
    Fraction::operator=(other);
    update_whole_part();
    return *this;
}

int MixedFraction::get_whole_part() const { return whole_part_; }

int MixedFraction::get_fractional_numerator() const {
    if (whole_part_ == 0) {
        return get_numerator();
    }
    return std::abs(get_numerator()) % get_denominator();
}

void MixedFraction::set_mixed(int whole, int num, int den) {
    if (den == 0) {
        den = 1;
    }
    if (den < 0) {
        num = -num;
        den = -den;
    }
    int total_num;
    if (whole < 0) {
        total_num = -(std::abs(whole) * den + std::abs(num));
    } else if (whole > 0) {
        total_num = whole * den + num;
    } else {
        total_num = num;
    }

    Fraction::set_values(total_num, den);
    update_whole_part();
}

void MixedFraction::set_values(int num, int den) {
    Fraction::set_values(num, den);
    update_whole_part();
}

std::ostream& operator<<(std::ostream& os, const MixedFraction& mf) {
    int whole = mf.get_whole_part();
    int rem_num = mf.get_fractional_numerator();
    int den = mf.get_denominator();

    if (whole != 0) {
        os << whole;
        if (rem_num != 0) {
            os << " " << rem_num << "/" << den;
        }
    } else {
        os << rem_num << "/" << den;
    }
    return os;
}

std::istream& operator>>(std::istream& is, MixedFraction& mf) {
    int part1 = 0;
    if (!(is >> part1)) {
        return is;
    }

    while (is.peek() == ' ' || is.peek() == '\t') {
        is.get();
    }

    if (is.peek() == '/') {
        is.get();
        int den = 1;
        is >> den;
        mf.set_values(part1, den);
    } else if ((is.peek() >= '0' && is.peek() <= '9') || is.peek() == '+' ||
               is.peek() == '-') {
        int num = 0;
        is >> num;
        while (is.peek() == ' ' || is.peek() == '\t') {
            is.get();
        }
        if (is.peek() == '/') {
            is.get();
            int den = 1;
            is >> den;
            mf.set_mixed(part1, num, den);
        } else {
            mf.set_mixed(part1, num, 1);
        }
    } else {
        mf.set_values(part1, 1);
    }
    return is;
}