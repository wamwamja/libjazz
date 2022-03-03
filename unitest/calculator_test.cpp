//
// Created by jiazhen on 2022/3/3.
//

#include <gtest/gtest.h>
#include <functional>
#include "jazz/core/Calculator.h"

class CalculatorTest : public ::testing::Test {
protected:

    void SetUp() override {

    }

};

TEST_F(CalculatorTest, FirstDerivative) {
    jazz::Real x0 = 1e-3;
    jazz::Real h = 1e-3;
    jazz::Real K = 10;
    auto ub1 = K * h;
    auto ub2 = ub1 * h;
    jazz::Real step = 0.1;
    auto x = x0;
    for (int i = 0; i < 10; ++i) {
        auto d = jazz::Calculator::numerical_derivative(std::exp, x, h,
                                                        jazz::Calculator::FIRST_FORWARD_2_POINT);
        EXPECT_TRUE(std::fabs(d - std::exp(x)) < ub1);
        x += step;
    }

    x = x0;
    for (int i = 0; i < 10; ++i) {
        auto d = jazz::Calculator::numerical_derivative(std::exp, x, h,
                                                        jazz::Calculator::FIRST_BACKWARD_2_POINT);
        EXPECT_TRUE(std::fabs(d - std::exp(x)) < ub1);
        x += step;
    }

    x = x0;
    for (int i = 0; i < 10; ++i) {
        auto d = jazz::Calculator::numerical_derivative(std::exp, x, h,
                                                        jazz::Calculator::FIRST_CENTRAL_3_POINT);
        EXPECT_TRUE(std::fabs(d - std::exp(x)) < ub1);
        x += step;
    }
}

TEST_F(CalculatorTest, SecondDerivative) {
    jazz::Real x0 = 1e-3;
    jazz::Real h = 1e-3;
    jazz::Real K = 10;
    auto ub = K * h * h;
    jazz::Real step = 0.1;
    auto x = x0;
    for (int i = 0; i < 10; ++i) {
        auto d = jazz::Calculator::numerical_derivative_second(std::exp, x, h);
        EXPECT_TRUE(std::fabs(d - std::exp(x)) < ub);
        x += step;
    }
}