#include <cstring>
#include <fstream>
#include <sstream>

#include "../googletest/include/gtest/gtest.h"
#include "EvaluatedFraction.h"
#include "Fraction.h"
#include "MixedFraction.h"

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

// 3lab

TEST(FractionTest3, OstreamOutputStandard) {
    Fraction f(3, 4);
    stringstream ss;
    ss << f;
    EXPECT_EQ(ss.str(), "3/4");
}

TEST(FractionTest3, OstreamOutputReduced) {
    Fraction f(6, 8);
    stringstream ss;
    ss << f;
    EXPECT_EQ(ss.str(), "3/4");
}

TEST(FractionTest3, OstreamOutputNegative) {
    Fraction f(-5, 9);
    stringstream ss;
    ss << f;
    EXPECT_EQ(ss.str(), "-5/9");
}

TEST(FractionTest3, IstreamInputStandardFraction) {
    stringstream ss("5/7");
    Fraction f;
    ss >> f;
    EXPECT_EQ(f.get_numerator(), 5);
    EXPECT_EQ(f.get_denominator(), 7);
}

TEST(FractionTest3, IstreamInputSingleInteger) {
    stringstream ss("9");
    Fraction f;
    ss >> f;
    EXPECT_EQ(f.get_numerator(), 9);
    EXPECT_EQ(f.get_denominator(), 1);
}

TEST(FractionTest3, IstreamInputFractionWithSpaces) {
    stringstream ss(" 2 / 3 ");
    Fraction f;
    ss >> f;
    EXPECT_EQ(f.get_numerator(), 2);
    EXPECT_EQ(f.get_denominator(), 3);
}

TEST(FractionTest3, IstreamInputSingleIntegerWithSpaces) {
    stringstream ss("   15   ");
    Fraction f;
    ss >> f;
    EXPECT_EQ(f.get_numerator(), 15);
    EXPECT_EQ(f.get_denominator(), 1);
}

TEST(FractionTest3, IstreamInputReductionOnFly) {
    stringstream ss("10/20");
    Fraction f;
    ss >> f;
    EXPECT_EQ(f.get_numerator(), 1);
    EXPECT_EQ(f.get_denominator(), 2);
}

TEST(FractionTest3, IstreamInputNegativeDenominator) {
    stringstream ss("4/-2");
    Fraction f;
    ss >> f;
    EXPECT_EQ(f.get_numerator(), -2);
    EXPECT_EQ(f.get_denominator(), 1);
}

TEST(FractionTest3, IstreamInputZeroNumerator) {
    stringstream ss("0/45");
    Fraction f;
    ss >> f;
    EXPECT_EQ(f.get_numerator(), 0);
    EXPECT_EQ(f.get_denominator(), 1);
}

TEST(FractionTest3, ChainedOstream) {
    Fraction f1(1, 2), f2(3, 4);
    stringstream ss;
    ss << f1 << " and " << f2;
    EXPECT_EQ(ss.str(), "1/2 and 3/4");
}

TEST(FractionTest3, ChainedIstream) {
    stringstream ss("3/8 7");
    Fraction f1, f2;
    ss >> f1 >> f2;
    EXPECT_EQ(f1.get_numerator(), 3);
    EXPECT_EQ(f1.get_denominator(), 8);
    EXPECT_EQ(f2.get_numerator(), 7);
    EXPECT_EQ(f2.get_denominator(), 1);
}

TEST(FractionTest3, TextFileWriteAndReadSingle) {
    const char* filename = "test_single.txt";
    {
        ofstream out(filename);
        Fraction f(7, 3);
        out << f;
    }
    Fraction f_in;
    {
        ifstream in(filename);
        in >> f_in;
    }
    remove(filename);
    EXPECT_EQ(f_in.get_numerator(), 7);
    EXPECT_EQ(f_in.get_denominator(), 3);
}

TEST(FractionTest3, TextFileWriteAndReadMultiple) {
    const char* filename = "test_multi.txt";
    {
        ofstream out(filename);
        Fraction arr[3] = {Fraction(1, 2), Fraction(5), Fraction(-3, 4)};
        Fraction::save_to_text(arr, 3, out);
    }
    Fraction r1, r2, r3;
    {
        ifstream in(filename);
        in >> r1 >> r2 >> r3;
    }
    remove(filename);
    EXPECT_STREQ(r1.c_str(), "1/2");
    EXPECT_STREQ(r2.c_str(), "5/1");
    EXPECT_STREQ(r3.c_str(), "-3/4");
}

TEST(FractionTest3, BinaryFileWriteAndReadSingle) {
    const char* filename = "test_single.bin";
    {
        Fraction arr[1] = {Fraction(11, 4)};
        ofstream out(filename, ios::binary);
        Fraction::save_to_binary(arr, 1, out);
    }
    int num_in = 0, den_in = 1;
    {
        ifstream in(filename, ios::binary);
        in.read(reinterpret_cast<char*>(&num_in), sizeof(num_in));
        in.read(reinterpret_cast<char*>(&den_in), sizeof(den_in));
    }
    remove(filename);
    Fraction f_res(num_in, den_in);

    EXPECT_EQ(f_res.get_numerator(), 11);
    EXPECT_EQ(f_res.get_denominator(), 4);
}

TEST(FractionTest3, BinaryFileWriteAndReadMultiple) {
    const char* filename = "test_multi_bin.bin";

    {
        Fraction arr[3] = {Fraction(1, 2), Fraction(3, 4), Fraction(5, 6)};
        ofstream out(filename, ios::binary);
        Fraction::save_to_binary(arr, 3, out);
    }

    Fraction* res = nullptr;
    int size = 0;
    int loaded_count = 0;
    {
        ifstream in(filename, ios::binary);
        loaded_count = Fraction::load_from_binary(in, res, size);
    }
    remove(filename);

    EXPECT_EQ(loaded_count, 3);
    EXPECT_EQ(size, 3);
    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(res[0].c_str(), "1/2");
    EXPECT_STREQ(res[1].c_str(), "3/4");
    EXPECT_STREQ(res[2].c_str(), "5/6");

    delete[] res;
}

TEST(FractionTest3, TextFileAppend) {
    const char* filename = "test_append.txt";

    {
        Fraction arr1[2] = {Fraction(1, 2), Fraction(3, 4)};
        ofstream out(filename);
        Fraction::save_to_text(arr1, 2, out);
    }

    {
        Fraction arr2[2] = {Fraction(5, 6), Fraction(7, 8)};
        ofstream out(filename, ios::app);
        int pos = out.tellp();  // put/get
        Fraction::save_to_text(arr2, 2, out);
    }

    Fraction* res = nullptr;
    int size = 0;
    int loaded_count = 0;
    {
        ifstream in(filename);
        loaded_count = Fraction::load_from_text(in, res, size);
    }
    remove(filename);

    EXPECT_EQ(loaded_count, 4);
    EXPECT_EQ(size, 4);
    EXPECT_NE(res, nullptr);
    EXPECT_STREQ(res[0].c_str(), "1/2");
    EXPECT_STREQ(res[1].c_str(), "3/4");
    EXPECT_STREQ(res[2].c_str(), "5/6");
    EXPECT_STREQ(res[3].c_str(), "7/8");

    delete[] res;
}

TEST(FractionTest3, BinaryFileAppend) {
    const char* filename = "test_append.bin";

    {
        Fraction arr1[2] = {Fraction(1, 3), Fraction(2, 3)};
        ofstream out(filename, ios::binary);
        Fraction::save_to_binary(arr1, 2, out);
    }

    {
        Fraction arr2[1] = {Fraction(4, 5)};
        ofstream out(filename, ios::app | ios::binary);
        Fraction::save_to_binary(arr2, 1, out);
    }

    Fraction* res = nullptr;
    int size = 0;
    int loaded_count = 0;
    {
        ifstream in(filename, ios::binary);
        loaded_count = Fraction::load_from_binary(in, res, size);
    }
    remove(filename);

    EXPECT_EQ(loaded_count, 3);
    EXPECT_EQ(size, 3);
    EXPECT_NE(res, nullptr);
    EXPECT_STREQ(res[0].c_str(), "1/3");
    EXPECT_STREQ(res[1].c_str(), "2/3");
    EXPECT_STREQ(res[2].c_str(), "4/5");

    delete[] res;
}

TEST(FractionTest3, ObjectCounterConsistencyInIO) {
    int initial = Fraction::get_object_count();
    {
        stringstream ss("4/5");
        Fraction f;
        ss >> f;
        EXPECT_EQ(Fraction::get_object_count(), initial + 1);
    }
    EXPECT_EQ(Fraction::get_object_count(), initial);
}

TEST(FractionTest3, InvalidInputStreamStateStateIntact) {
    stringstream ss("not_a_fraction");
    Fraction f(2, 3);
    ss >> f;
    EXPECT_EQ(f.get_numerator(), 2);
    EXPECT_EQ(f.get_denominator(), 3);
}

TEST(FractionTest3, IstreamInputZeroDenominatorHandling) {
    stringstream ss("5/0");
    Fraction f;
    ss >> f;
    EXPECT_NE(f.get_denominator(), 0);
}

TEST(FractionTest3, CStrRepresentationPostIstreamUpdate) {
    stringstream ss("7/14");
    Fraction f;
    ss >> f;
    EXPECT_STREQ(f.c_str(), "1/2");
}

// 4 лаба

TEST(FractionTest4, EvaluatedFractionBasic) {
    EvaluatedFraction ef(3, 4);
    EXPECT_EQ(ef.get_numerator(), 3);
    EXPECT_EQ(ef.get_denominator(), 4);
    EXPECT_DOUBLE_EQ(ef.get_value(), 0.75);
}

TEST(FractionTest4, EvaluatedFractionSetValues) {
    EvaluatedFraction ef(1, 2);
    ef.set_values(1, 8);
    EXPECT_EQ(ef.get_numerator(), 1);
    EXPECT_EQ(ef.get_denominator(), 8);
    EXPECT_DOUBLE_EQ(ef.get_value(), 0.125);
}

TEST(FractionTest4, EvaluatedFractionFromBase) {
    Fraction f(5, 2);
    EvaluatedFraction ef = f;
    EXPECT_EQ(ef.get_numerator(), 5);
    EXPECT_EQ(ef.get_denominator(), 2);
    EXPECT_DOUBLE_EQ(ef.get_value(), 2.5);
}

TEST(FractionTest4, EvaluatedFractionCopyAndAssign) {
    EvaluatedFraction ef1(7, 2);
    EvaluatedFraction ef2(ef1);
    EXPECT_DOUBLE_EQ(ef2.get_value(), 3.5);

    EvaluatedFraction ef3;
    ef3 = ef1;
    EXPECT_DOUBLE_EQ(ef3.get_value(), 3.5);
}

TEST(FractionTest4, EvaluatedFractionStreamOutput) {
    EvaluatedFraction ef(1, 4);
    stringstream ss;
    ss << ef;
    EXPECT_EQ(ss.str(), "1/4 (= 0.25)");
}

TEST(FractionTest4, EvaluatedFractionDestructorCount) {
    int start_count = Fraction::get_object_count();
    {
        EvaluatedFraction ef(3, 5);
        EXPECT_EQ(Fraction::get_object_count(), start_count + 1);
    }

    EXPECT_EQ(Fraction::get_object_count(), start_count);
}

TEST(FractionTest4, MixedFractionThreeParams) {
    MixedFraction mf(2, 1, 3);
    EXPECT_EQ(mf.get_whole_part(), 2);
    EXPECT_EQ(mf.get_fractional_numerator(), 1);
    EXPECT_EQ(mf.get_denominator(), 3);
    EXPECT_EQ(mf.get_numerator(), 7);
}

TEST(FractionTest4, MixedFractionTwoParamsAutoReduction) {
    MixedFraction mf(11, 4);
    EXPECT_EQ(mf.get_whole_part(), 2);
    EXPECT_EQ(mf.get_fractional_numerator(), 3);
    EXPECT_EQ(mf.get_denominator(), 4);
    EXPECT_EQ(mf.get_numerator(), 11);
}

TEST(FractionTest4, MixedFractionFromBase) {
    Fraction f(14, 5);
    MixedFraction mf = f;
    EXPECT_EQ(mf.get_whole_part(), 2);
    EXPECT_EQ(mf.get_fractional_numerator(), 4);
    EXPECT_EQ(mf.get_denominator(), 5);
}

TEST(FractionTest4, MixedFractionNegativeHandling) {
    MixedFraction mf(-2, 1, 3);
    EXPECT_EQ(mf.get_whole_part(), -2);
    EXPECT_EQ(mf.get_fractional_numerator(), 1);
    EXPECT_EQ(mf.get_denominator(), 3);
    EXPECT_EQ(mf.get_numerator(), -7);
}

TEST(FractionTest4, MixedFractionCopyAndAssign) {
    MixedFraction mf1(3, 1, 4);
    MixedFraction mf2(mf1);
    EXPECT_EQ(mf2.get_whole_part(), 3);
    EXPECT_EQ(mf2.get_fractional_numerator(), 1);

    MixedFraction mf3;
    mf3 = mf1;
    EXPECT_EQ(mf3.get_whole_part(), 3);
    EXPECT_EQ(mf3.get_fractional_numerator(), 1);
}

TEST(FractionTest4, MixedFractionStreamOutput) {
    MixedFraction mf(3, 2, 5);
    stringstream ss;
    ss << mf;
    EXPECT_EQ(ss.str(), "3 2/5");

    MixedFraction mf_proper(1, 4);
    stringstream ss2;
    ss2 << mf_proper;
    EXPECT_EQ(ss2.str(), "1/4");
}

TEST(FractionTest4, MixedFractionStreamInput) {
    stringstream ss("4 3/7");
    MixedFraction mf;
    ss >> mf;
    EXPECT_EQ(mf.get_whole_part(), 4);
    EXPECT_EQ(mf.get_fractional_numerator(), 3);
    EXPECT_EQ(mf.get_denominator(), 7);

    stringstream ss_simple("9/2");
    MixedFraction mf_simple;
    ss_simple >> mf_simple;
    EXPECT_EQ(mf_simple.get_whole_part(), 4);
    EXPECT_EQ(mf_simple.get_fractional_numerator(), 1);
    EXPECT_EQ(mf_simple.get_denominator(), 2);
}

TEST(FractionTest4, MixedFractionDestructorCount) {
    int start_count = Fraction::get_object_count();
    {
        MixedFraction mf(1, 2, 3);
        EXPECT_EQ(Fraction::get_object_count(), start_count + 1);
    }
    EXPECT_EQ(Fraction::get_object_count(), start_count);
}

TEST(FractionTest4, RelatedTypesSlicingAndAssignment) {
    EvaluatedFraction ef(7, 3);
    MixedFraction mf(2, 1, 3);

    Fraction f1 = ef;
    EXPECT_EQ(f1.get_numerator(), 7);
    EXPECT_EQ(f1.get_denominator(), 3);

    Fraction f2 = mf;
    EXPECT_EQ(f2.get_numerator(), 7);
    EXPECT_EQ(f2.get_denominator(), 3);

    Fraction f_assign;
    f_assign = ef;
    EXPECT_EQ(f_assign.get_numerator(), 7);

    f_assign = mf;
    EXPECT_EQ(f_assign.get_numerator(), 7);
}

TEST(FractionTest4, DynamicArrayWithoutVector) {
    const int count = 3;

    Fraction* arr[count];
    arr[0] = new Fraction(1, 2);
    arr[1] = new EvaluatedFraction(3, 4);
    arr[2] = new MixedFraction(1, 1, 2);

    EXPECT_EQ(arr[0]->get_numerator(), 1);
    EXPECT_EQ(arr[1]->get_numerator(), 3);
    EXPECT_EQ(arr[2]->get_numerator(), 3);

    for (int i = 0; i < count; i++) {
        delete arr[i];
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
