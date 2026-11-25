#include <fstream>
#include <iostream>
#include <new>
#include <sstream>

#include "Deque.h"
#include "EvaluatedFraction.h"
#include "Exceptions.h"
#include "Fraction.h"
#include "MixedFraction.h"

using namespace std;

void print_menu() {
    cout << "\nMENU\n";
    cout << "1. Input fraction\n";
    cout << "2. Create array manually\n";
    cout << "3. Save to TEXT file\n";
    cout << "4. Load from TEXT file\n";
    cout << "5. Save to BINARY file\n";
    cout << "6. Load from BINARY file\n";
    cout << "7. Print current array\n";
    cout << "8. Clear current array in memory\n";
    cout << "9. 4lab check\n";
    cout << "10. 5lab check\n";
    cout << "11. 6lab check\n";
    cout << "12. 7lab check\n";
    cout << "0. Exit\n";
    cout << "Select option: ";
}

void add_fraction(Fraction*& arr, int& size, const Fraction& f) {
    Fraction* new_arr = new Fraction[size + 1];
    for (int i = 0; i < size; i++) {
        new_arr[i] = arr[i];
    }
    new_arr[size] = f;

    delete[] arr;
    arr = new_arr;
    size++;
}

void demo_lab4();
void demo_lab5();
void demo_lab6();
void demo_lab7();

int main() {
    Fraction* current_fractions = nullptr;
    int current_size = 0;
    int choice = -1;

    while (choice != 0) {
        print_menu();
        if (!(cin >> choice)) {
            cout << "Error\n";
            choice = 0;
            continue;
        }

        try {
            switch (choice) {
                case 1: {
                    Fraction f;
                    cout << "Enter a fraction (format 3/4 or 4): ";
                    cin >> f;
                    cout << "You entered: " << f << "\n";
                    break;
                }
                case 2: {
                    int count;
                    cout << "How many fractions do you want to add? ";
                    if (!(cin >> count) || count < 0) {
                        throw InputFormatException("Invalid array size");
                    }
                    for (int i = 0; i < count; i++) {
                        Fraction f;
                        cout << "Fraction #" << i + 1 << ": ";
                        cin >> f;
                        add_fraction(current_fractions, current_size, f);
                    }
                    cout << "Array of " << count
                         << " elements successfully created.\n";
                    break;
                }
                case 3: {
                    if (current_size == 0) {
                        cout << "Array is empty. Nothing to save.\n";
                        break;
                    }
                    ofstream out("fractions.txt", ios::app);
                    Fraction::save_to_text(current_fractions, current_size,
                                           out);
                    cout << "Successfully appended\n";
                    break;
                }
                case 4: {
                    ifstream in("fractions.txt");
                    int count = Fraction::load_from_text(in, current_fractions,
                                                         current_size);
                    cout << "Successfully loaded " << count
                         << " objects from text file.\n";
                    break;
                }
                case 5: {
                    if (current_size == 0) {
                        cout << "Array is empty. Nothing to save.\n";
                        break;
                    }
                    ofstream out("fractions.bin", ios::app | ios::binary);
                    Fraction::save_to_binary(current_fractions, current_size,
                                             out);
                    cout << "Successfully saved to binary file fractions.bin\n";
                    break;
                }
                case 6: {
                    ifstream in("fractions.bin", ios::binary);
                    int count = Fraction::load_from_binary(
                        in, current_fractions, current_size);
                    cout << "Successfully loaded " << count
                         << " objects from binary file.\n";
                    break;
                }
                case 7: {
                    if (current_size == 0) {
                        cout << "Array in memory is empty.\n";
                    } else {
                        cout << "Current array of fractions (" << current_size
                             << " elements):\n";
                        for (int i = 0; i < current_size; i++) {
                            cout << "[" << i << "]: " << current_fractions[i]
                                 << "\n";
                        }
                    }
                    break;
                }
                case 8: {
                    delete[] current_fractions;
                    current_fractions = nullptr;
                    current_size = 0;
                    cout << "Memory cleared.\n";
                    break;
                }
                case 9: {
                    demo_lab4();
                    break;
                }
                case 10: {
                    demo_lab5();
                    break;
                }
                case 11: {
                    demo_lab6();
                    break;
                }
                case 12: {
                    demo_lab7();
                    break;
                }
                case 0:
                    cout << "Exiting the program.\n";
                    break;
                default:
                    cout << "Error: Unknown command!\n";
                    break;
            }
        } catch (const DivisionByZeroException& e) {
            cout << "[DivisionByZeroException]: " << e.what() << "\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } catch (const OutOfRangeException& e) {
            cout << "[OutOfRangeException]: " << e.what() << "\n";
        } catch (const FileIOException& e) {
            cout << "[FileIOException]: " << e.what() << "\n";
        } catch (const InputFormatException& e) {
            cout << "[InputFormatException]: " << e.what() << "\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } catch (const AppException& e) {
            cout << "[AppException]: " << e.what() << "\n";
        } catch (const std::bad_alloc& e) {
            cout << "[std::bad_alloc]: " << e.what() << "\n";
        } catch (const std::exception& e) {
            cout << "[std::exception]: " << e.what() << "\n";
        } catch (...) {
            cout << "[Unknown Exception]\n";
        }
    }
    delete[] current_fractions;
    return 0;
}

void demo_lab4() {
    EvaluatedFraction ef1(3, 4);
    cout << "ef1: " << ef1 << "\n";
    cout << "value: " << ef1.get_value() << "\n";

    MixedFraction mf1(2, 1, 3);
    cout << "mf1: " << mf1 << "\n";
    cout << "whole: " << mf1.get_whole_part()
         << ", num: " << mf1.get_fractional_numerator()
         << ", den: " << mf1.get_denominator() << "\n";

    MixedFraction mf2(11, 4);
    cout << "mf2: " << mf2 << "\n";

    Fraction sum = ef1 + Fraction(1, 4);
    cout << "ef1 + 1/4 = " << sum << "\n";

    Fraction base1 = ef1;
    cout << "base from eval: " << base1 << "\n";

    Fraction base2 = mf1;
    cout << "base from mixed: " << base2 << "\n";

    EvaluatedFraction ef2 = base2;
    cout << "eval from base: " << ef2 << "\n";

    MixedFraction mf3 = base1;
    cout << "mixed from base: " << mf3 << "\n";

    Fraction f_assign;
    f_assign = ef1;
    cout << "assign eval: " << f_assign << "\n";
    f_assign = mf1;
    cout << "assign mixed: " << f_assign << "\n";

    const int size = 4;
    Fraction* arr[size];
    arr[0] = new Fraction(1, 2);
    arr[1] = new EvaluatedFraction(7, 8);
    arr[2] = new MixedFraction(3, 1, 4);
    arr[3] = new MixedFraction(13, 5);

    cout << "array:\n";
    for (int i = 0; i < size; i++) {
        cout << "[" << i << "]: " << *(arr[i]) << "\n";
    }

    for (int i = 0; i < size; i++) {
        delete arr[i];
    }
}

void demo_lab5() {
    Deque<Fraction*> dq;

    Fraction* f = new Fraction(1, 2);
    Fraction* ef = new EvaluatedFraction(3, 4);
    Fraction* mf = new MixedFraction(2, 1, 3);

    dq.push_back(f);
    dq.push_back(ef);
    dq.push_back(mf);

    cout << "deque elements:\n";
    for (int i = 0; i < dq.get_size(); i++) {
        cout << "[" << i << "] " << dq.get(i)->c_str() << "\n";
    }

    for (int i = 0; i < dq.get_size(); i++) {
        delete dq.get(i);
    }
}

void demo_lab6() {
    try {
        cout << "1) Creating Fraction(5, 0)...\n";
        Fraction bad(5, 0);
    } catch (const DivisionByZeroException& e) {
        cout << "   Caught DivisionByZeroException: " << e.what() << "\n";
    } catch (const AppException& e) {
        cout << "   Caught AppException: " << e.what() << "\n";
    } catch (...) {
        cout << "   Caught unknown exception\n";
    }

    try {
        cout << "2) Dividing 1/2 by 0/1...\n";
        Fraction f1(1, 2);
        Fraction f2(0, 1);
        Fraction res = f1.divide(f2);
    } catch (const DivisionByZeroException& e) {
        cout << "   Caught DivisionByZeroException: " << e.what() << "\n";
    } catch (const AppException& e) {
        cout << "   Caught AppException: " << e.what() << "\n";
    } catch (...) {
        cout << "   Caught unknown exception\n";
    }

    try {
        cout << "3) Accessing Deque<Fraction>::get(10)...\n";
        Deque<Fraction> dq;
        dq.push_back(Fraction(1, 3));
        cout << dq.get(10) << "\n";
    } catch (const OutOfRangeException& e) {
        cout << "   Caught OutOfRangeException: " << e.what() << "\n";
    } catch (const AppException& e) {
        cout << "   Caught AppException: " << e.what() << "\n";
    } catch (...) {
        cout << "   Caught unknown exception\n";
    }

    try {
        cout << "4) Calling pop_front() on empty Deque<int>...\n";
        Deque<int> empty_dq;
        empty_dq.pop_front();
    } catch (const OutOfRangeException& e) {
        cout << "   Caught OutOfRangeException: " << e.what() << "\n";
    } catch (...) {
        cout << "   Caught unknown exception\n";
    }

    try {
        cout << "5) Loading from nonexistent file...\n";
        ifstream bad_file("nonexistent_file_12345.txt");
        Fraction* arr = nullptr;
        int sz = 0;
        Fraction::load_from_text(bad_file, arr, sz);
    } catch (const FileIOException& e) {
        cout << "   Caught FileIOException: " << e.what() << "\n";
    } catch (const AppException& e) {
        cout << "   Caught AppException: " << e.what() << "\n";
    } catch (...) {
        cout << "   Caught unknown exception\n";
    }

    try {
        cout << "6) Parsing invalid stream \"abc\"...\n";
        stringstream ss("abc");
        Fraction f;
        ss >> f;
    } catch (const InputFormatException& e) {
        cout << "   Caught InputFormatException: " << e.what() << "\n";
    } catch (const AppException& e) {
        cout << "   Caught AppException: " << e.what() << "\n";
    } catch (...) {
        cout << "   Caught unknown exception\n";
    }

    try {
        cout << "7) Simulating std::bad_alloc...\n";
        throw std::bad_alloc();
    } catch (const AppException& e) {
        cout << "   Caught AppException: " << e.what() << "\n";
    } catch (const std::bad_alloc& e) {
        cout << "   Caught std::bad_alloc: " << e.what() << "\n";
    } catch (const std::exception& e) {
        cout << "   Caught std::exception: " << e.what() << "\n";
    } catch (...) {
        cout << "   Caught unknown exception\n";
    }
}

void demo_lab7() {
    cout << "--- Deque<int> ---\n";
    Deque<int> dq_int;
    dq_int.push_back(10);
    dq_int.push_back(20);
    dq_int.push_front(5);
    dq_int.insert_at(2, 15);
    dq_int.print_all();
    cout << "find 20 index: " << dq_int.find(20) << "\n";
    dq_int.remove_at(1);
    dq_int.pop_front();
    cout << "after remove_at(1) and pop_front:\n";
    dq_int.print_all();

    cout << "--- Deque<float> ---\n";
    Deque<float> dq_float;
    dq_float.push_back(1.5f);
    dq_float.push_back(2.75f);
    dq_float.push_front(0.25f);
    dq_float.print_all();
    cout << "element at 1: " << dq_float.get(1) << "\n";

    cout << "--- Deque<Fraction> ---\n";
    Deque<Fraction> dq_frac;
    dq_frac.push_back(Fraction(1, 2));
    dq_frac.push_back(Fraction(3, 4));
    dq_frac.push_front(Fraction(5, 8));
    dq_frac.insert_at(2, Fraction(2, 3));
    dq_frac.print_all();
    cout << "find 3/4 index: " << dq_frac.find(Fraction(3, 4)) << "\n";
}