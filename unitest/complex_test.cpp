//
// Created by meitu on 2022/3/2.
//

#include "jazz/core/Complex.h"
#include <gtest/gtest.h>

class ComplexTest : public ::testing::Test {
protected:

    using Complex = jazz::Complex_<float>;

    void SetUp() override {
        a = Complex(1.2, 3.4);
        b = Complex(3.3, 4.4);
        c = Complex(256.7, -234.4);
        d = 0.083;
        dd = Complex(d);
    }

    Complex a, b, c, dd;
    float d;
};

TEST_F(ComplexTest, ComplexAdd) {
    EXPECT_EQ(a + b, Complex(a.re() + b.re(), a.im() + b.im()));
    EXPECT_EQ(b + c, Complex(b.re() + c.re(), b.im() + c.im()));
    EXPECT_EQ(c + a, Complex(c.re() + a.re(), c.im() + a.im()));
    EXPECT_EQ(c + dd, c + d);
    EXPECT_EQ(c + dd, d + c);
}

TEST_F(ComplexTest, ComplexMinus) {
    EXPECT_EQ(a - b, Complex(a.re() - b.re(), a.im() - b.im()));
    EXPECT_EQ(b - c, Complex(b.re() - c.re(), b.im() - c.im()));
    EXPECT_EQ(c - a, Complex(c.re() - a.re(), c.im() - a.im()));
    EXPECT_EQ(c - d, Complex(c.re() - d, c.im()));
    EXPECT_EQ(c - dd, c - d);
    EXPECT_EQ(c - dd, -(d - c));
}

TEST_F(ComplexTest, ComplexMul) {
    EXPECT_EQ(a * b, Complex(a.re() * b.re() - a.im() * b.im(), a.re() * b.im() + a.im() * b.re()));
    EXPECT_EQ(b * c, Complex(b.re() * c.re() - b.im() * c.im(), b.re() * c.im() + b.im() * c.re()));
    EXPECT_EQ(c * a, Complex(c.re() * a.re() - c.im() * a.im(), c.re() * a.im() + c.im() * a.re()));
    EXPECT_EQ(c * dd, c * d);
    EXPECT_EQ(c * dd, d * c);
}


TEST_F(ComplexTest, ComplexDiv) {
    auto div = [](const Complex &a, const Complex &b) {
        auto t = b.re() * b.re() + b.im() * b.im();
        auto re = (a.re() * b.re() + a.im() * b.im()) / t;
        auto im = (-a.re() * b.im() + a.im() * b.re()) / t;
        return Complex(re, im);
    };

    EXPECT_EQ(a / b, div(a, b));
    EXPECT_EQ(b / c, div(b, c));
    EXPECT_EQ(c / a, div(c, a));
    EXPECT_EQ(c / dd, c / d);
    EXPECT_TRUE(((c / dd) * (d / c) - 1).abs() < 1e-6);
}