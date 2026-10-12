#include <cstring>

#include "../googletest/include/gtest/gtest.h"
#include "Fraction.h"

using namespace std;

// 1 лаба

TEST(FractionTest, DefaultConstructor) {
    Fraction f;
    EXPECT_EQ(f.get_numerator(), 0);
    EXPECT_EQ(f.get_denominator(), 1);
    EXPECT_STREQ(f.c_str(), "0/1");
}

TEST(FractionTest, ReductionConstructor) {
    Fraction f(4, 8);
    EXPECT_EQ(f.get_numerator(), 1);
    EXPECT_EQ(f.get_denominator(), 2);
    EXPECT_STREQ(f.c_str(), "1/2");
}

TEST(FractionTest, NegativeDenominatorHandling) {
    Fraction f(5, -3);
    EXPECT_EQ(f.get_numerator(), -5);
    EXPECT_EQ(f.get_denominator(), 3);
    EXPECT_STREQ(f.c_str(), "-5/3");
}

TEST(FractionTest, SetterValidation) {
    Fraction f(1, 2);
    f.set_values(6, 9);
    EXPECT_EQ(f.get_numerator(), 2);
    EXPECT_EQ(f.get_denominator(), 3);
    EXPECT_STREQ(f.c_str(), "2/3");
}

TEST(FractionTest, addition) {
    Fraction f1(1, 2);
    Fraction f2(1, 3);

    Fraction sum = f1.add(f2);
    EXPECT_STREQ(sum.c_str(), "5/6");
}

TEST(FractionTest, substraction) {
    Fraction f1(1, 2);
    Fraction f2(1, 3);

    Fraction diff = f1.substract(f2);
    EXPECT_STREQ(diff.c_str(), "1/6");
}

TEST(FractionTest, Multiplication) {
    Fraction f1(2, 3);
    Fraction f2(3, 4);

    Fraction prod = f1.multiply(f2);
    EXPECT_STREQ(prod.c_str(), "1/2");
}

TEST(FractionTest, Division) {
    Fraction f1(2, 3);
    Fraction f2(3, 4);

    Fraction quot = f1.divide(f2);
    EXPECT_STREQ(quot.c_str(), "8/9");
}

TEST(FractionTest, ObjectCounterValidation) {
    int start_count = Fraction::get_object_count();

    {
        Fraction temp1(1, 2);
        Fraction temp2(3, 4);
        EXPECT_EQ(Fraction::get_object_count(), start_count + 2);
    }

    EXPECT_EQ(Fraction::get_object_count(), start_count);
}

TEST(FractionTest, DoubleNegativeHandling) {
    Fraction f(-2, -4);
    EXPECT_EQ(f.get_numerator(), 1);
    EXPECT_EQ(f.get_denominator(), 2);
    EXPECT_STREQ(f.c_str(), "1/2");
}

TEST(FractionTest, ZeroNumeratorConstructor) {
    Fraction f(0, 5);
    EXPECT_EQ(f.get_numerator(), 0);
    EXPECT_EQ(f.get_denominator(), 1);
    EXPECT_STREQ(f.c_str(), "0/1");
}

TEST(FractionTest, ZeroDenominatorHandling) {
    Fraction f(3, 0);
    EXPECT_EQ(f.get_denominator(), 1);
    EXPECT_STREQ(f.c_str(), "3/1");
}

TEST(FractionTest, additionWithNegative) {
    Fraction f1(3, 4);
    Fraction f2(-1, 4);
    Fraction sum = f1.add(f2);
    EXPECT_STREQ(sum.c_str(), "1/2");
}

TEST(FractionTest, MultiplicationByZero) {
    Fraction f1(5, 7);
    Fraction f2(0, 1);
    Fraction prod = f1.multiply(f2);
    EXPECT_STREQ(prod.c_str(), "0/1");
}

TEST(FractionTest, substractSelf) {
    Fraction f(4, 5);
    Fraction diff = f.substract(f);
    EXPECT_STREQ(diff.c_str(), "0/1");
}

TEST(FractionTest, CopyConstructorValues) {
    Fraction original(3, 7);
    Fraction copy(original);
    EXPECT_EQ(copy.get_numerator(), 3);
    EXPECT_EQ(copy.get_denominator(), 7);
    EXPECT_STREQ(copy.c_str(), "3/7");
}

TEST(FractionTest, SetterZeroDenominatorProtection) {
    Fraction f(2, 3);
    f.set_values(5, 0);
    EXPECT_NE(f.get_denominator(), 0);
}

// 2 лаба

TEST(FractionTest2, Division) {}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
