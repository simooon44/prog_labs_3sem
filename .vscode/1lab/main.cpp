#include <fstream>
#include <iostream>

#include "Deque.h"
#include "EvaluatedFraction.h"
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

        switch (choice) {
            case 1: {
                Fraction f;
                cout << "Enter a fraction (format 3/4 or 4): ";
                cin >> f;
                if (cin) {
                    cout << "You entered: " << f << "\n";
                } else {
                    cout << "Error!\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                break;
            }
            case 2: {
                int count;
                cout << "How many fractions do you want to add? ";
                cin >> count;
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
                if (Fraction::save_to_text(current_fractions, current_size,
                                           out)) {
                    cout << "Successfully appended\n";
                } else {
                    cout << "Error!\n";
                }
                break;
            }
            case 4: {
                ifstream in("fractions.txt");
                if (!in) {
                    cout << "Error opening text file!\n";
                    break;
                }
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
                if (Fraction::save_to_binary(current_fractions, current_size,
                                             out)) {
                    cout << "Successfully saved to binary file fractions.bin\n";
                } else {
                    cout << "Error!\n";
                }
                break;
            }
            case 6: {
                ifstream in("fractions.bin", ios::binary);
                if (!in) {
                    cout << "Error opening binary file!\n";
                    break;
                }
                int count = Fraction::load_from_binary(in, current_fractions,
                                                       current_size);
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
            case 0:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Error: Unknown command!\n";
                break;
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
    Deque dq;

    Fraction f(1, 2);
    EvaluatedFraction ef(3, 4);
    MixedFraction mf(2, 1, 3);

    dq.push_back(f);
    dq.push_back(ef);
    dq.push_back(mf);

    EvaluatedFraction ef_front(5, 8);
    dq.push_front(ef_front);

    MixedFraction mf_insert(11, 4);
    dq.insert_at(2, mf_insert);

    cout << "deque elements (polymorphism via c_str):\n";
    dq.print_all();

    int found_idx = dq.find(Fraction(3, 4));
    cout << "find 3/4 index: " << found_idx << "\n";

    dq.remove_at(2);
    dq.pop_front();

    cout << "after remove_at(2) and pop_front:\n";
    dq.print_all();
}