#include <algorithm>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <unordered_map>
#include <vector>

#include "Fraction.h"

using Clock = std::chrono::steady_clock;
using CompareFractions = bool (*)(const Fraction&, const Fraction&);

bool fraction_less(const Fraction& a, const Fraction& b) {
    return 1LL * a.get_numerator() * b.get_denominator() <
           1LL * b.get_numerator() * a.get_denominator();
}

using HashFraction = std::size_t (*)(const Fraction&);

std::size_t fraction_hash(const Fraction& value) {
    const auto numerator = static_cast<std::uint32_t>(value.get_numerator());
    const auto denominator =
        static_cast<std::uint32_t>(value.get_denominator());
    const auto key = (std::uint64_t{denominator} << 32) | numerator;
    return std::hash<std::uint64_t>{}(key);
}

double elapsed_ns(Clock::time_point start) {
    return std::chrono::duration<double, std::nano>(Clock::now() - start)
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

    const int next_int = size + 1;
    const Fraction next_fraction(next_int, 1000003);

    const int find_int = integers[size / 2];
    const int erase_int = integers[size / 3];
    const Fraction& find_fraction = fractions[size / 2];
    const Fraction& erase_fraction = fractions[size / 3];

    constexpr int measurement_count = 100;
    Clock::time_point start;

    std::queue<int> queue_int;
    for (const auto& key : integers) {
        queue_int.push(key);
    }

    double queue_pop_int = 0;
    double queue_push_int = 0;
    for (int repeat = 0; repeat < measurement_count; repeat++) {
        start = Clock::now();
        queue_int.pop();
        queue_pop_int += elapsed_ns(start);
        queue_int.push(next_int);

        start = Clock::now();
        queue_int.push(next_int);
        queue_push_int += elapsed_ns(start);
        queue_int.pop();
    }

    std::queue<Fraction> queue_fraction;
    for (const auto& key : fractions) {
        queue_fraction.push(key);
    }

    double queue_pop_fraction = 0;
    double queue_push_fraction = 0;
    for (int repeat = 0; repeat < measurement_count; repeat++) {
        start = Clock::now();
        queue_fraction.pop();
        queue_pop_fraction += elapsed_ns(start);
        queue_fraction.push(next_fraction);

        start = Clock::now();
        queue_fraction.push(next_fraction);
        queue_push_fraction += elapsed_ns(start);
        queue_fraction.pop();
    }

    std::map<int, int> map_int;
    int map_int_value = 1;
    for (const auto& key : integers) {
        map_int.emplace(key, map_int_value++);
    }

    double map_insert_int = 0;
    double map_find_int = 0;
    double map_erase_int = 0;
    for (int repeat = 0; repeat < measurement_count; ++repeat) {
        start = Clock::now();
        const auto inserted = map_int.emplace(next_int, next_int);
        map_insert_int += elapsed_ns(start);
        if (!inserted.second) {
            return false;
        }
        map_int.erase(inserted.first);

        start = Clock::now();
        const auto found = map_int.find(find_int);
        map_find_int += elapsed_ns(start);
        if (found == map_int.end() || found->second != size / 2 + 1) {
            return false;
        }

        start = Clock::now();
        const auto erased = map_int.erase(erase_int);
        map_erase_int += elapsed_ns(start);
        if (erased != 1) {
            return false;
        }
        map_int.emplace(erase_int, size / 3 + 1);
    }

    std::map<Fraction, int, CompareFractions> map_fraction(fraction_less);
    int map_fraction_value = 1;
    for (const auto& key : fractions) {
        map_fraction.emplace(key, map_fraction_value++);
    }

    double map_insert_fraction = 0;
    double map_find_fraction = 0;
    double map_erase_fraction = 0;
    for (int repeat = 0; repeat < measurement_count; ++repeat) {
        start = Clock::now();
        const auto inserted = map_fraction.emplace(next_fraction, next_int);
        map_insert_fraction += elapsed_ns(start);
        if (!inserted.second) {
            return false;
        }
        map_fraction.erase(inserted.first);

        start = Clock::now();
        const auto found = map_fraction.find(find_fraction);
        map_find_fraction += elapsed_ns(start);
        if (found == map_fraction.end() || found->second != size / 2 + 1) {
            return false;
        }

        start = Clock::now();
        const auto erased = map_fraction.erase(erase_fraction);
        map_erase_fraction += elapsed_ns(start);
        if (erased != 1) {
            return false;
        }
        map_fraction.emplace(erase_fraction, size / 3 + 1);
    }

    std::unordered_map<int, int> unordered_int;
    int unordered_int_value = 1;
    for (const auto& key : integers) {
        unordered_int.emplace(key, unordered_int_value++);
    }

    double unordered_insert_int = 0;
    double unordered_find_int = 0;
    double unordered_erase_int = 0;
    for (int repeat = 0; repeat < measurement_count; ++repeat) {
        start = Clock::now();
        const auto inserted = unordered_int.emplace(next_int, next_int);
        unordered_insert_int += elapsed_ns(start);
        if (!inserted.second) {
            return false;
        }
        unordered_int.erase(inserted.first);

        start = Clock::now();
        const auto found = unordered_int.find(find_int);
        unordered_find_int += elapsed_ns(start);
        if (found == unordered_int.end() || found->second != size / 2 + 1) {
            return false;
        }

        start = Clock::now();
        const auto erased = unordered_int.erase(erase_int);
        unordered_erase_int += elapsed_ns(start);
        if (erased != 1) {
            return false;
        }
        unordered_int.emplace(erase_int, size / 3 + 1);
    }

    std::unordered_map<Fraction, int, HashFraction> unordered_fraction(
        0, fraction_hash);
    int unordered_fraction_value = 1;
    for (const auto& key : fractions) {
        unordered_fraction.emplace(key, unordered_fraction_value++);
    }

    double unordered_insert_fraction = 0;
    double unordered_find_fraction = 0;
    double unordered_erase_fraction = 0;
    for (int repeat = 0; repeat < measurement_count; ++repeat) {
        start = Clock::now();
        const auto inserted =
            unordered_fraction.emplace(next_fraction, next_int);
        unordered_insert_fraction += elapsed_ns(start);
        if (!inserted.second) {
            return false;
        }
        unordered_fraction.erase(inserted.first);

        start = Clock::now();
        const auto found = unordered_fraction.find(find_fraction);
        unordered_find_fraction += elapsed_ns(start);
        if (found == unordered_fraction.end() ||
            found->second != size / 2 + 1) {
            return false;
        }

        start = Clock::now();
        const auto erased = unordered_fraction.erase(erase_fraction);
        unordered_erase_fraction += elapsed_ns(start);
        if (erased != 1) {
            return false;
        }
        unordered_fraction.emplace(erase_fraction, size / 3 + 1);
    }

    csv << size << ',' << queue_push_int / measurement_count << ','
        << queue_push_fraction / measurement_count << ','
        << queue_pop_int / measurement_count << ','
        << queue_pop_fraction / measurement_count << ','
        << map_insert_int / measurement_count << ','
        << map_insert_fraction / measurement_count << ','
        << map_find_int / measurement_count << ','
        << map_find_fraction / measurement_count << ','
        << map_erase_int / measurement_count << ','
        << map_erase_fraction / measurement_count << ','
        << unordered_insert_int / measurement_count << ','
        << unordered_insert_fraction / measurement_count << ','
        << unordered_find_int / measurement_count << ','
        << unordered_find_fraction / measurement_count << ','
        << unordered_erase_int / measurement_count << ','
        << unordered_erase_fraction / measurement_count << '\n';
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
           "fraction,map_erase_int,map_erase_fraction,"
           "unordered_insert_int,unordered_insert_fraction,unordered_find_int,"
           "unordered_find_fraction,unordered_erase_int,unordered_erase_"
           "fraction\n";
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
