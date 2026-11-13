#include "MixedFraction.h"

#include <cmath>
#include <cstdio>
#include <cstring>

void MixedFraction::update_whole_part() {
    whole_part_ = get_numerator() / get_denominator();
    update_string_representation();
}

MixedFraction::MixedFraction()
    : Fraction(0, 1), whole_part_(0), string_rep_(nullptr) {
    update_string_representation();
}

MixedFraction::MixedFraction(int num, int den)
    : Fraction(num, den), whole_part_(0), string_rep_(nullptr) {
    update_whole_part();
}

MixedFraction::MixedFraction(int whole, int num, int den)
    : Fraction(0, 1), whole_part_(0), string_rep_(nullptr) {
    set_mixed(whole, num, den);
}

MixedFraction::MixedFraction(const Fraction& f)
    : Fraction(f), whole_part_(0), string_rep_(nullptr) {
    update_whole_part();
}

MixedFraction::~MixedFraction() { delete[] string_rep_; }

MixedFraction::MixedFraction(const MixedFraction& other)
    : Fraction(other), whole_part_(other.whole_part_), string_rep_(nullptr) {
    if (other.string_rep_) {
        string_rep_ = new char[strlen(other.string_rep_) + 1];
        strcpy(string_rep_, other.string_rep_);
    } else {
        update_string_representation();
    }
}

MixedFraction& MixedFraction::operator=(const Fraction& other) {
    Fraction::operator=(other);
    update_whole_part();
    return *this;
}

MixedFraction& MixedFraction::operator=(const MixedFraction& other) {
    if (this == &other) {
        return *this;
    }
    Fraction::operator=(other);
    whole_part_ = other.whole_part_;

    delete[] string_rep_;
    if (other.string_rep_) {
        string_rep_ = new char[strlen(other.string_rep_) + 1];
        strcpy(string_rep_, other.string_rep_);
    } else {
        update_string_representation();
    }
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
    mf.print(os);
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

// 5lab

void MixedFraction::update_string_representation() {
    delete[] string_rep_;
    char buffer[64];
    int whole = get_whole_part();
    int rem_num = get_fractional_numerator();
    int den = get_denominator();

    if (whole != 0) {
        if (rem_num != 0) {
            sprintf(buffer, "%d %d/%d", whole, rem_num, den);
        } else {
            sprintf(buffer, "%d", whole);
        }
    } else {
        sprintf(buffer, "%d/%d", rem_num, den);
    }
    string_rep_ = new char[strlen(buffer) + 1];
    strcpy(string_rep_, buffer);
}

const char* MixedFraction::c_str() const { return string_rep_; }

Fraction* MixedFraction::clone() const { return new MixedFraction(*this); }

void MixedFraction::print(std::ostream& os) const { os << string_rep_; }