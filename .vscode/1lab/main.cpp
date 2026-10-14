#include <fstream>
#include <iostream>
#include <vector>

#include "Fraction.h"

using namespace std;

void print_menu() {
    cout << "\n=== МЕНЮ ЛАБОРАТОРНОЙ РАБОТЫ №3 ===\n";
    cout << "1. Ввести дробь с клавиатуры и вывести на экран\n";
    cout << "2. Создать массив дробей вручную\n";
    cout << "3. Сохранить текущий массив в ТЕКСТОВЫЙ файл\n";
    cout << "4. Загрузить массив из ТЕКСТОВОГО файла\n";
    cout << "5. Сохранить текущий массив в БИНАРНЫЙ файл\n";
    cout << "6. Загрузить массив из БИНАРНОГО файла\n";
    cout << "7. Вывести текущий массив дробей в консоль\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
}

int main() {
    vector<Fraction> current_fractions;
    int choice = -1;

    while (choice != 0) {
        print_menu();
        if (!(cin >> choice)) {
            cout << "Ошибка ввода числового значения команды!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                Fraction f;
                cout << "Введите дробь (в формате 3/4 или 4): ";
                cin >> f;
                if (cin) {
                    cout << "Вы ввели дробь: " << f
                         << " (внутренняя строка: " << f.c_str() << ")\n";
                } else {
                    cout << "Некорректный формат ввода.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                break;
            }
            case 2: {
                int count;
                cout << "Сколько дробей вы хотите добавить? ";
                cin >> count;
                current_fractions.clear();
                for (int i = 0; i < count; ++i) {
                    Fraction f;
                    cout << "Дробь №" << i + 1 << ": ";
                    cin >> f;
                    current_fractions.push_back(f);
                }
                cout << "Массив из " << current_fractions.size()
                     << " элементов успешно создан.\n";
                break;
            }
            case 3: {
                if (current_fractions.empty()) {
                    cout << "Массив пуст. Нечего сохранять.\n";
                    break;
                }
                ofstream out("fractions.txt");
                if (!out) {
                    cout << "Не удалось открыть файл для записи.\n";
                    break;
                }
                // Записываем количество элементов первой строкой
                out << current_fractions.size() << "\n";
                for (const auto& f : current_fractions) {
                    out << f << "\n";
                }
                cout << "Успешно сохранено в fractions.txt\n";
                break;
            }
            case 4: {
                ifstream in("fractions.txt");
                if (!in) {
                    cout << "Файл fractions.txt не найден.\n";
                    break;
                }
                size_t count = 0;
                if (!(in >> count)) {
                    cout << "Ошибка чтения структуры файла.\n";
                    break;
                }
                current_fractions.clear();
                for (size_t i = 0; i < count; ++i) {
                    Fraction f;
                    in >> f;
                    current_fractions.push_back(f);
                }
                cout << "Успешно загружено " << current_fractions.size()
                     << " объектов из текстового файла.\n";
                break;
            }
            case 5: {
                if (current_fractions.empty()) {
                    cout << "Массив пуст. Нечего сохранять.\n";
                    break;
                }
                ofstream out("fractions.bin", ios::binary);
                if (!out) {
                    cout << "Не удалось открыть бинарный файл для записи.\n";
                    break;
                }
                size_t count = current_fractions.size();
                out.write(reinterpret_cast<const char*>(&count), sizeof(count));

                for (const auto& f : current_fractions) {
                    int num = f.get_numerator();
                    int den = f.get_denominator();
                    out.write(reinterpret_cast<const char*>(&num), sizeof(num));
                    out.write(reinterpret_cast<const char*>(&den), sizeof(den));
                }
                cout << "Успешно сохранено в бинарный файл fractions.bin\n";
                break;
            }
            case 6: {
                ifstream in("fractions.bin", ios::binary);
                if (!in) {
                    cout << "Файл fractions.bin не найден.\n";
                    break;
                }
                size_t count = 0;
                in.read(reinterpret_cast<char*>(&count), sizeof(count));

                current_fractions.clear();
                for (size_t i = 0; i < count; ++i) {
                    int num = 0, den = 1;
                    in.read(reinterpret_cast<char*>(&num), sizeof(num));
                    in.read(reinterpret_cast<char*>(&den), sizeof(den));
                    current_fractions.emplace_back(num, den);
                }
                cout << "Успешно загружено " << current_fractions.size()
                     << " объектов из бинарного файла.\n";
                break;
            }
            case 7: {
                if (current_fractions.empty()) {
                    cout << "Массив в памяти пуст.\n";
                } else {
                    cout << "Текущий массив дробей:\n";
                    for (size_t i = 0; i < current_fractions.size(); ++i) {
                        cout << "[" << i << "]: " << current_fractions[i]
                             << "\n";
                    }
                }
                break;
            }
            case 0:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неизвестная команда!\n";
                break;
        }
    }
    return 0;
}
