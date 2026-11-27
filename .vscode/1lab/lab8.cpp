#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <vector>

#include "Fraction.h"

using Clock = std::chrono::steady_clock;
using CompareFractions = bool (*)(const Fraction&, const Fraction&);

bool fraction_less(const Fraction& a, const Fraction& b) {
    return 1LL * a.get_numerator() * b.get_denominator() <
           1LL * b.get_numerator() * a.get_denominator();
}

double elapsed_ms(Clock::time_point start) {
    return std::chrono::duration<double, std::milli>(Clock::now() - start)
        .count();
}

bool measure_size(int size, std::ostream& csv) {
    std::vector<int> integers(size);
    for (int i = 0; i < size; ++i) {
        integers[i] = i + 1;
    }
    std::mt19937 generator(42);
    std::shuffle(integers.begin(), integers.end(), generator);

    std::vector<Fraction> fractions;
    fractions.reserve(size);
    for (int number : integers) {
        fractions.emplace_back(number, 1000003);
    }

    auto start = Clock::now();

    std::queue<int> queue_int;
    start = Clock::now();
    for (const auto& key : integers) {
        queue_int.push(key);
    }
    const double queue_push_int = elapsed_ms(start);
    start = Clock::now();
    while (!queue_int.empty()) {
        queue_int.pop();
    }
    const double queue_pop_int = elapsed_ms(start);

    std::queue<Fraction> queue_fraction;
    start = Clock::now();
    for (const auto& key : fractions) {
        queue_fraction.push(key);
    }
    const double queue_push_fraction = elapsed_ms(start);
    start = Clock::now();
    while (!queue_fraction.empty()) {
        queue_fraction.pop();
    }
    const double queue_pop_fraction = elapsed_ms(start);

    std::map<int, int> map_int;
    int value_int = 1;
    start = Clock::now();
    for (const auto& key : integers) {
        map_int.emplace(key, value_int++);
    }
    const double map_insert_int = elapsed_ms(start);
    long long sum_int = 0;
    start = Clock::now();
    for (const auto& key : integers) {
        auto it = map_int.find(key);
        if (it != map_int.end()) {
            sum_int += it->second;
        }
    }
    const double map_find_int = elapsed_ms(start);
    start = Clock::now();
    for (const auto& key : integers) {
        map_int.erase(key);
    }
    const double map_erase_int = elapsed_ms(start);

    std::map<Fraction, int, CompareFractions> map_fraction(fraction_less);
    int value_fraction = 1;
    start = Clock::now();
    for (const auto& key : fractions) {
        map_fraction.emplace(key, value_fraction++);
    }
    const double map_insert_fraction = elapsed_ms(start);
    long long sum_fraction = 0;
    start = Clock::now();
    for (const auto& key : fractions) {
        auto it = map_fraction.find(key);
        if (it != map_fraction.end()) {
            sum_fraction += it->second;
        }
    }
    const double map_find_fraction = elapsed_ms(start);
    start = Clock::now();
    for (const auto& key : fractions) {
        map_fraction.erase(key);
    }
    const double map_erase_fraction = elapsed_ms(start);

    const long long expected = 1LL * size * (size + 1) / 2;
    if (sum_int != expected || sum_fraction != expected || !map_int.empty() ||
        !map_fraction.empty()) {
        return false;
    }

    csv << size << ',' << queue_push_int << ',' << queue_push_fraction << ','
        << queue_pop_int << ',' << queue_pop_fraction << ',' << map_insert_int
        << ',' << map_insert_fraction << ',' << map_find_int << ','
        << map_find_fraction << ',' << map_erase_int << ','
        << map_erase_fraction << '\n';
    return true;
}

int main(int argc, char* argv[]) {
    const char* path = argc > 1 ? argv[1] : "lab8_results.csv";
    std::ofstream csv(path);
    if (!csv) {
        std::cerr << "Cannot open " << path << '\n';
        return 1;
    }

    csv << "size,queue_push_int,queue_push_fraction,queue_pop_int,queue_pop_"
           "fraction,map_insert_int,map_insert_fraction,map_find_int,map_find_"
           "fraction,map_erase_int,map_erase_fraction\n";
    for (int size = 100000; size <= 1000000; size += 50000) {
        if (!measure_size(size, csv)) {
            std::cerr << "Unexpected container result at N = " << size << '\n';
            return 1;
        }
        std::cout << "N = " << size << '\n';
    }

    csv.close();
    if (!csv) {
        std::cerr << "Cannot write " << path << '\n';
        return 1;
    }
}
