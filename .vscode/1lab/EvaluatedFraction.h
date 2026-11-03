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
    ~EvaluatedFraction();

    EvaluatedFraction& operator=(const EvaluatedFraction& other);
    EvaluatedFraction& operator=(const Fraction& other);

    double get_value() const;
    void set_values(int num, int den);

    friend std::ostream& operator<<(std::ostream& os,
                                    const EvaluatedFraction& ef);
    friend std::istream& operator>>(std::istream& is, EvaluatedFraction& ef);

   private:
    double value_;
    void compute_value();
};

#endif