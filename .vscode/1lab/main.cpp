#include <fstream>
#include <iostream>
#include <vector>

#include "Fraction.h"

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
    cout << "0. Exit\n";
    cout << "Select option: ";
}

int main() {
    vector<Fraction> current_fractions;
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
                current_fractions.clear();
                for (int i = 0; i < count; i++) {
                    Fraction f;
                    cout << "Fraction #" << i + 1 << ": ";
                    cin >> f;
                    current_fractions.push_back(f);
                }
                cout << "Array of " << (int)current_fractions.size()
                     << " elements successfully created.\n";
                break;
            }
            case 3: {
                if (current_fractions.empty()) {
                    cout << "Array is empty. Nothing to save.\n";
                    break;
                }
                ofstream out("fractions.txt");
                if (!out) {
                    cout << "Error!\n";
                    break;
                }
                int count = (int)current_fractions.size();
                out << count << "\n";
                for (const auto& f : current_fractions) {
                    out << f << "\n";
                }
                cout << "Successfully saved to fractions.txt\n";
                break;
            }
            case 4: {
                ifstream in("fractions.txt");
                if (!in) {
                    cout << "Error!\n";
                    break;
                }
                int count = 0;
                if (!(in >> count)) {
                    cout << "Error!\n";
                    break;
                }
                current_fractions.clear();
                for (int i = 0; i < count; i++) {
                    Fraction f;
                    in >> f;
                    current_fractions.push_back(f);
                }
                cout << "Successfully loaded " << (int)current_fractions.size()
                     << " objects from text file.\n";
                break;
            }
            case 5: {
                if (current_fractions.empty()) {
                    cout << "Array is empty. Nothing to save.\n";
                    break;
                }
                ofstream out("fractions.bin", ios::binary);
                if (!out) {
                    cout << "Error!\n";
                    break;
                }
                int count = (int)current_fractions.size();
                out.write(reinterpret_cast<const char*>(&count), sizeof(count));

                for (const auto& f : current_fractions) {
                    int num = f.get_numerator();
                    int den = f.get_denominator();
                    out.write(reinterpret_cast<const char*>(&num), sizeof(num));
                    out.write(reinterpret_cast<const char*>(&den), sizeof(den));
                }
                cout << "Successfully saved to binary file fractions.bin\n";
                break;
            }
            case 6: {
                ifstream in("fractions.bin", ios::binary);
                if (!in) {
                    cout << "Error!\n";
                    break;
                }
                int count = 0;
                in.read(reinterpret_cast<char*>(&count), sizeof(count));

                current_fractions.clear();
                for (int i = 0; i < count; i++) {
                    int num = 0, den = 1;
                    in.read(reinterpret_cast<char*>(&num), sizeof(num));
                    in.read(reinterpret_cast<char*>(&den), sizeof(den));
                    current_fractions.push_back(Fraction(num, den));
                }
                cout << "Successfully loaded " << (int)current_fractions.size()
                     << " objects from binary file.\n";
                break;
            }
            case 7: {
                if (current_fractions.empty()) {
                    cout << "Array in memory is empty.\n";
                } else {
                    cout << "Current array of fractions:\n";
                    int count = (int)current_fractions.size();
                    for (int i = 0; i < count; ++i) {
                        cout << "[" << i << "]: " << current_fractions[i]
                             << "\n";
                    }
                }
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
    return 0;
}
