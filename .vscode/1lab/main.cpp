#include <iostream>

#include "Fraction.h"

using namespace std;

void CheckCopyConstructor(Fraction f);

int main() {
    cout << "started number of fractions: " << Fraction::get_object_count()
         << "\n"
         << endl;

    Fraction f1;        // 0/1
    Fraction f2(3, 6);  // 1/2
    Fraction f3(5, 4);  // 5/4

    cout << "Fraction f1: " << f1.c_str() << endl;
    cout << "Fraction f2: " << f2.c_str() << endl;
    cout << "Fraction f3: " << f3.c_str() << endl;
    cout << endl;

    cout << "Copy constructor" << endl;
    CheckCopyConstructor(f2);
    cout << endl;

    cout << "Arithmetic operations" << endl;
    Fraction res_add = f2.add(f3);
    cout << f2.c_str() << " + " << f3.c_str() << " = " << res_add.c_str()
         << endl;

    Fraction res_sub = f2.substract(f3);
    cout << f2.c_str() << " - " << f3.c_str() << " = " << res_sub.c_str()
         << endl;

    Fraction res_mul = f2.multiply(f3);
    cout << f2.c_str() << " * " << f3.c_str() << " = " << res_mul.c_str()
         << endl;

    Fraction res_div = f2.divide(f3);
    cout << f2.c_str() << " / " << f3.c_str() << " = " << res_div.c_str()
         << endl;
    cout << endl;

    cout << "Changing values f1" << endl;
    f1.set_values(7, 14);  // 1/2
    cout << "New value f1: " << f1.c_str() << endl;
    cout << endl;

    cout << "Current number of fractions: " << Fraction::get_object_count()
         << "\n"
         << endl;

    cout << "End" << endl;
    return 0;
}

void CheckCopyConstructor(Fraction f) { cout << "Copy: " << f.c_str() << endl; }
