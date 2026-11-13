#ifndef EVALUATED_FRACTION_H_
#define EVALUATED_FRACTION_H_

#include <iostream>

#include "Fraction.h"

class EvaluatedFraction : public Fraction {
   public:
    EvaluatedFraction();
    EvaluatedFraction(int num, int den = 1);
    EvaluatedFraction(const Fraction& f);
    EvaluatedFraction(const EvaluatedFraction& other);
    virtual ~EvaluatedFraction() override;

    EvaluatedFraction& operator=(const EvaluatedFraction& other);
    EvaluatedFraction& operator=(const Fraction& other);

    double get_value() const;
    void set_values(int num, int den);

    friend std::ostream& operator<<(std::ostream& os,
                                    const EvaluatedFraction& ef);
    friend std::istream& operator>>(std::istream& is, EvaluatedFraction& ef);

    // 5lab

    virtual const char* c_str() const override;
    virtual Fraction* clone() const override;
    virtual void print(std::ostream& os) const override;

   private:
    double value_;
    void compute_value();
    // 5lab
    char* string_rep_;
    void update_string_representation();
};

#endif