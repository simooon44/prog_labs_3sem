#include <fstream>
#include <iostream>

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
