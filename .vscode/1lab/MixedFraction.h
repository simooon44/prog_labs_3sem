#ifndef MIXED_FRACTION_H_
#define MIXED_FRACTION_H_

#include <iostream>

#include "Fraction.h"

class MixedFraction : public Fraction {
   public:
    MixedFraction();
    MixedFraction(int num, int den = 1);
    MixedFraction(int whole, int num, int den);
    MixedFraction(const Fraction& f);
    MixedFraction(const MixedFraction& other);
    virtual ~MixedFraction();

    MixedFraction& operator=(const MixedFraction& other);
    MixedFraction& operator=(const Fraction& other);

    int get_whole_part() const;
    int get_fractional_numerator() const;

    void set_mixed(int whole, int num, int den);
    void set_values(int num, int den);

    friend std::ostream& operator<<(std::ostream& os, const MixedFraction& mf);
    friend std::istream& operator>>(std::istream& is, MixedFraction& mf);

    // 5lab

    virtual const char* c_str() const override;
    virtual Fraction* clone() const override;
    virtual void print(std::ostream& os) const override;

   private:
    int whole_part_;
    void update_whole_part();

    char* string_rep_;
    void update_string_representation();
};

#endif