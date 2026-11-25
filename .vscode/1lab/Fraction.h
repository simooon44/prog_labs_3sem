#ifndef FRACTION_H_
#define FRACTION_H_
#include <iostream>

#include "Exceptions.h"

class Fraction {
   public:
    Fraction();
    Fraction(int num, int den = 1);
    Fraction(const Fraction& other);
    virtual ~Fraction();  // 5 lab

    static int get_object_count();

    int get_numerator() const;
    int get_denominator() const;
    void set_values(int num, int den);

    virtual const char* c_str() const;  // 5 lab

    Fraction add(const Fraction& other) const;
    Fraction substract(const Fraction& other) const;
    Fraction multiply(const Fraction& other) const;
    Fraction divide(const Fraction& other) const;

    // 2 lab

    Fraction& operator=(const Fraction& other);

    explicit operator float() const;

    friend Fraction operator+(const Fraction& lhs, const Fraction& rhs);
    friend Fraction operator-(const Fraction& lhs, const Fraction& rhs);

    // 3 lab

    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction);
    friend std::istream& operator>>(std::istream& is, Fraction& fraction);

    static bool save_to_text(const Fraction* fractions, int size,
                             std::ostream& out);
    static bool save_to_binary(const Fraction* fractions, int size,
                               std::ostream& out);

    static int load_from_text(std::istream& in, Fraction*& arr, int& size);
    static int load_from_binary(std::istream& in, Fraction*& arr, int& size);

    // 5 lab

    virtual Fraction* clone() const;

    // 7 lab

    bool operator==(const Fraction& other) const;

   protected:
    mutable char* string_rep_;
    void update_string_representation() const;
    void update_string_representation(const char* str) const;

   private:
    int numerator_;
    int denominator_;

    int gcd(int a, int b);

    static int object_count_;
};

#endif