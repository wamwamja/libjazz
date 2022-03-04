//
// Created by meitu on 2022/3/4.
//

#include "jazz/core/PersistRealArray.h"
#include <gtest/gtest.h>

class ArrayTest : public ::testing::Test {
protected:

    void SetUp() override {
        data = {12, 35, 6, 67, 33.8, 77, 64.54};
    }

    std::vector<jazz::Real> data;
};

TEST_F(ArrayTest, ArrayBase) {

    auto length = data.size();
    auto array = jazz::ArrayBase<jazz::Real>::wrap(data.data(), length);
    for (int i = 0; i < length; ++i) {
        EXPECT_EQ(data[i], array.at(i));
        EXPECT_EQ(data[i], array[i]);
    }

    EXPECT_EQ(length, array.length());
}

TEST_F(ArrayTest, PersistRealArray) {
    auto length = data.size();
    auto array = jazz::PersistRealArray(length, data.data());
    for (int i = 0; i < length; ++i) {
        EXPECT_EQ(data[i], array.at(i));
        EXPECT_EQ(data[i], array[i]);
    }

    EXPECT_EQ(length, array.length());
}