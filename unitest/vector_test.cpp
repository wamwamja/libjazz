//
// Created by meitu on 2022/3/4.
//

#include "jazz/core/VectorBase.h"
#include "jazz/jazz_config.h"
#include <gtest/gtest.h>

class VectorTest : public ::testing::Test {
protected:

    void SetUp() override {
        a = {12, 35, 6, 67, 33.8, 77, 64.54};
        b = {12, 35, 6, 67, 33.8, 77, 64.54};
        c = {12, 35, 6, 67, 33.8, 77, 64.54};
        d = {23};
    }

    std::vector<jazz::Real> a;
    std::vector<jazz::Real> b;
    std::vector<jazz::Real> c;
    std::vector<jazz::Real> d;

    using Vector = jazz::VectorBase<jazz::Real>;

};

TEST_F(VectorTest, OperatorPlus) {
    Vector va(a.size(),a.data());
    Vector vb(b.size(),b.data());
    Vector vc(c.size(),c.data());
    Vector sum = va + vb + vc;
}