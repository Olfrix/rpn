#include <gtest/gtest.h>
#include "calculator.h"

TEST(Calculator, Plus)
{
    double result = calculate("5 5 +").second;
    EXPECT_DOUBLE_EQ(result, 10.0);
}

TEST(Calculator, Minus)
{
    double result = calculate("10 5 -").second;
    EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST(Calculator, Divide)
{
    double result = calculate("10 5 /").second;
    EXPECT_DOUBLE_EQ(result, 2.0);
}

TEST(Calculator, Multiply)
{
    double result = calculate("10 5 *").second;
    EXPECT_DOUBLE_EQ(result, 50.0);
}

TEST(Calculator, LongNotation)
{
    double result = calculate("2 4 + 5 * 2 /").second;
    EXPECT_DOUBLE_EQ(result, 15);
}

TEST(Calculator, DivideByZero)
{
    tResultType result = calculate("2 4 + 5 * 0 /").first;
    EXPECT_EQ(false, result);
}

TEST(Calculator, WrongOrder)
{
    tResultType result = calculate("+ 2 4 + 5").first;
    EXPECT_EQ(false, result);
}

TEST(Calculator, RandomString)
{
    tResultType result = calculate("zysopejrl@(#@($#@38283482348282gzlsqwktyjghbp").first;
    EXPECT_EQ(false, result);
}

TEST(Calculator, InvalidArguments)
{
    tResultType result = calculate("2 2 + 5 - zysopejrlgzlsqwktyjghbp").first;
    EXPECT_EQ(false, result);
}

TEST(Calculator, ComplexExpr)
{
    double result = calculate("15 7 1 1 + - / 3 * 2 1 1 + + -").second;
    EXPECT_DOUBLE_EQ(result, 5);
}

TEST(Calculator, WrongOperation)
{
    tResultType result = calculate("2 2 + 5 %").first;
    EXPECT_EQ(false, result);
}

TEST(Calculator, EmptyString)
{
    tResultType result = calculate("").first;
    EXPECT_EQ(false, result);
}

TEST(Calculator, BigNumber)
{
    double result = calculate("145 145 +").second;
    EXPECT_DOUBLE_EQ(result, 290.0);
}

TEST(Calculator, NegativeNumber)
{
    double result = calculate("-145 146 +").second;
    EXPECT_DOUBLE_EQ(result, 1.0);
}

//numeric limits with + - / *
