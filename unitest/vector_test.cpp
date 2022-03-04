//
// Created by meitu on 2022/3/4.
//

#include "jazz/core/VectorBase.h"
#include "jazz/jazz_config.h"
#include <gtest/gtest.h>

class VectorTest : public ::testing::Test {
protected:

    void SetUp() override {
        a = {12, 35, 6, 45, 33.8, 5435, 64.54};
        b = {236, 34, 4, 54, 33.8, 46, 345.54};
        c = {43, 45, 54, 45, 33.8, 43, 346.3654};
        d = {23};
    }

    std::vector<jazz::Real> a;
    std::vector<jazz::Real> b;
    std::vector<jazz::Real> c;
    std::vector<jazz::Real> d;

    using Vector = jazz::VectorBase<jazz::Real>;

};

TEST_F(VectorTest, OperatorPlus) {
    Vector va(a.size(), a.data());
    Vector vb(b.size(), b.data());
    Vector vc(c.size(), c.data());
    Vector sum = va + vb + vc;
    auto size = va.size();
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(sum[i], va[i] + vb[i] + vc[i]);
    }
}