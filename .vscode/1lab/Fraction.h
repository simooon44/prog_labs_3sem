#ifndef FRACTION_H_
#define FRACTION_H_

class Fraction {
   public:
    Fraction();
    Fraction(int num, int den);
    Fraction(const Fraction& other);
    ~Fraction();

    static int get_object_count();

    int get_numerator() const;
    int get_denominator() const;
    void set_values(int num, int den);

    const char* c_str() const;

    Fraction add(const Fraction& other) const;
    Fraction substract(const Fraction& other) const;
    Fraction multiply(const Fraction& other) const;
    Fraction divide(const Fraction& other) const;

   private:
    int numerator_;
    int denominator_;
    char* string_rep_;

    void update_string_representation();
    int gcd(int a, int b);

    static int object_count_;
};

#endif
