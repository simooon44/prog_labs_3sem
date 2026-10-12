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

TEST(FractionTest2, AssignmentBasic) {
    Fraction f1(3, 4);
    Fraction f2;
    f2 = f1;
    EXPECT_EQ(f2.get_numerator(), 3);
    EXPECT_EQ(f2.get_denominator(), 4);
    EXPECT_STREQ(f2.c_str(), "3/4");
}

TEST(FractionTest2, AssignmentSelfAssignment) {
    Fraction f1(2, 5);
    f1 = f1;
    EXPECT_EQ(f1.get_numerator(), 2);
    EXPECT_EQ(f1.get_denominator(), 5);
    EXPECT_STREQ(f1.c_str(), "2/5");
}

TEST(FractionTest2, AssignmentChain) {
    Fraction f1(1, 3);
    Fraction f2;
    Fraction f3;
    f3 = f2 = f1;
    EXPECT_STREQ(f3.c_str(), "1/3");
    EXPECT_STREQ(f2.c_str(), "1/3");
}

TEST(FractionTest2, AssignmentObjectCounter) {
    int start_count = Fraction::get_object_count();
    Fraction f1(1, 2);
    Fraction f2(3, 4);
    EXPECT_EQ(Fraction::get_object_count(), start_count + 2);
    f2 = f1;
    EXPECT_EQ(Fraction::get_object_count(), start_count + 2);
}

TEST(FractionTest2, FloatConversionPositive) {
    Fraction f(1, 2);
    float val = static_cast<float>(f);
    EXPECT_FLOAT_EQ(val, 0.5f);
}

TEST(FractionTest2, FloatConversionNegative) {
    Fraction f(-3, 4);
    float val = static_cast<float>(f);
    EXPECT_FLOAT_EQ(val, -0.75f);
}

TEST(FractionTest2, FloatConversionZero) {
    Fraction f(0, 5);
    float val = static_cast<float>(f);
    EXPECT_FLOAT_EQ(val, 0.0f);
}

TEST(FractionTest2, FloatConversionWholeNumber) {
    Fraction f(5, 1);
    float val = static_cast<float>(f);
    EXPECT_FLOAT_EQ(val, 5.0f);
}

TEST(FractionTest2, OpAddFractionsStandard) {
    Fraction f1(1, 4);
    Fraction f2(2, 4);
    Fraction res = f1 + f2;
    EXPECT_STREQ(res.c_str(), "3/4");
}

TEST(FractionTest2, OpAddFractionsNegative) {
    Fraction f1(-1, 3);
    Fraction f2(2, 3);
    Fraction res = f1 + f2;
    EXPECT_STREQ(res.c_str(), "1/3");
}

TEST(FractionTest2, OpAddFractionsReduction) {
    Fraction f1(1, 6);
    Fraction f2(1, 6);
    Fraction res = f1 + f2;
    EXPECT_STREQ(res.c_str(), "1/3");
}

TEST(FractionTest2, OpSubFractionsStandard) {
    Fraction f1(3, 4);
    Fraction f2(1, 4);
    Fraction res = f1 - f2;
    EXPECT_STREQ(res.c_str(), "1/2");
}

TEST(FractionTest2, OpSubFractionsToNegative) {
    Fraction f1(1, 5);
    Fraction f2(3, 5);
    Fraction res = f1 - f2;
    EXPECT_STREQ(res.c_str(), "-2/5");
}

TEST(FractionTest2, OpSubFractionsToZero) {
    Fraction f1(4, 7);
    Fraction f2(4, 7);
    Fraction res = f1 - f2;
    EXPECT_STREQ(res.c_str(), "0/1");
}

TEST(FractionTest2, OpFractionPlusInt) {
    Fraction f(1, 4);
    Fraction res = f + 2;
    EXPECT_STREQ(res.c_str(), "9/4");
}

TEST(FractionTest2, OpIntPlusFraction) {
    Fraction f(2, 3);
    Fraction res = 1 + f;
    EXPECT_STREQ(res.c_str(), "5/3");
}

TEST(FractionTest2, OpFractionMinusInt) {
    Fraction f(7, 2);
    Fraction res = f - 3;
    EXPECT_STREQ(res.c_str(), "1/2");
}

TEST(FractionTest2, OpIntMinusFraction) {
    Fraction f(1, 4);
    Fraction res = 2 - f;
    EXPECT_STREQ(res.c_str(), "7/4");
}

TEST(FractionTest2, OpFractionPlusIntNegative) {
    Fraction f(3, 2);
    Fraction res = f + (-1);
    EXPECT_STREQ(res.c_str(), "1/2");
}

TEST(FractionTest2, OpIntMinusFractionNegative) {
    Fraction f(-1, 4);
    Fraction res = 1 - f;
    EXPECT_STREQ(res.c_str(), "5/4");
}