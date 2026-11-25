#include "Fraction.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
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

void Fraction::update_string_representation(const char* str) const {
    delete[] string_rep_;
    string_rep_ = new char[strlen(str) + 1];
    strcpy(string_rep_, str);
}

void Fraction::update_string_representation() const {
    char buffer[64];
    sprintf(buffer, "%d/%d", numerator_, denominator_);
    update_string_representation(buffer);
}

Fraction::Fraction() : Fraction(0, 1) {}

Fraction::Fraction(int num, int den)
    : numerator_(num), denominator_(den), string_rep_(nullptr) {
    if (denominator_ == 0) {
        throw DivisionByZeroException("Fraction: denominator cannot be zero");
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

const char* Fraction::c_str() const {
    update_string_representation();
    return string_rep_;
}

void Fraction::set_values(int num, int den) {
    if (den == 0) {
        throw DivisionByZeroException(
            "Fraction::set_values: denominator cannot be zero");
    }
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
    if (other.numerator_ == 0) {
        throw DivisionByZeroException("Fraction::divide: division by zero");
    }
    return Fraction(numerator_ * other.denominator_,
                    denominator_ * other.numerator_);
}

// 2 lab

Fraction& Fraction::operator=(const Fraction& other) {
    if (this == &other) {
        return *this;
    }

    char* new_rep = nullptr;
    if (other.string_rep_) {
        new_rep = new char[strlen(other.string_rep_) + 1];
        strcpy(new_rep, other.string_rep_);
    }

    delete[] string_rep_;
    string_rep_ = new_rep;
    numerator_ = other.numerator_;
    denominator_ = other.denominator_;

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

// 3 lab

ostream& operator<<(ostream& os, const Fraction& fraction) {
    if (!os) {
        throw FileIOException("operator<<: output stream is in invalid state");
    }
    os << fraction.c_str();
    return os;
}

istream& operator>>(istream& is, Fraction& fraction) {
    int num = 0;
    int den = 1;

    is >> std::ws;
    if (is.peek() == EOF) {
        is.setstate(std::ios::eofbit | std::ios::failbit);
        return is;
    }

    if (!(is >> num)) {
        throw InputFormatException("Fraction input: expected numerator");
    }

    while (is.peek() == ' ' || is.peek() == '	') {
        is.get();
    }

    if (is.peek() == '/') {
        is.get();
        if (!(is >> den)) {
            throw InputFormatException(
                "Fraction input: expected denominator after '/'");
        }
    }

    fraction.set_values(num, den);
    return is;
}

bool Fraction::save_to_text(const Fraction* fractions, int size,
                            std::ostream& out) {
    if (!out) {
        throw FileIOException("save_to_text: output stream is not open or bad");
    }
    for (int i = 0; i < size; i++) {
        out << fractions[i] << "\n";
        if (!out) {
            throw FileIOException("save_to_text: write error");
        }
    }
    return true;
}

bool Fraction::save_to_binary(const Fraction* fractions, int size,
                              std::ostream& out) {
    if (!out) {
        throw FileIOException(
            "save_to_binary: output stream is not open or bad");
    }
    for (int i = 0; i < size; i++) {
        int num = fractions[i].get_numerator();
        int den = fractions[i].get_denominator();
        out.write(reinterpret_cast<const char*>(&num), sizeof(num));
        out.write(reinterpret_cast<const char*>(&den), sizeof(den));
        if (!out) {
            throw FileIOException("save_to_binary: write error");
        }
    }
    return true;
}

int Fraction::load_from_text(std::istream& in, Fraction*& arr, int& size) {
    if (!in) {
        throw FileIOException(
            "load_from_text: input stream is not open or bad");
    }
    int loaded_count = 0;
    Fraction f;
    while (in >> f) {
        Fraction* new_arr = new Fraction[size + 1];
        for (int i = 0; i < size; i++) {
            new_arr[i] = arr[i];
        }
        new_arr[size] = f;
        delete[] arr;
        arr = new_arr;
        size++;
        loaded_count++;
    }
    return loaded_count;
}

int Fraction::load_from_binary(std::istream& in, Fraction*& arr, int& size) {
    if (!in) {
        throw FileIOException(
            "load_from_binary: input stream is not open or bad");
    }
    int loaded_count = 0;
    int num = 0, den = 1;
    while (in.read(reinterpret_cast<char*>(&num), sizeof(num))) {
        if (!in.read(reinterpret_cast<char*>(&den), sizeof(den))) {
            throw FileIOException(
                "load_from_binary: unexpected end of file (corrupted record)");
        }
        Fraction f(num, den);
        Fraction* new_arr = new Fraction[size + 1];

        for (int i = 0; i < size; i++) {
            new_arr[i] = arr[i];
        }

        new_arr[size] = f;
        delete[] arr;
        arr = new_arr;
        size++;
        loaded_count++;
    }
    return loaded_count;
}

// 5 lab

Fraction* Fraction::clone() const { return new Fraction(*this); }