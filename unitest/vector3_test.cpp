//
// Created by jiazh on 2022-03-02.
//

#include "jazz/core/Vector3.h"
#include <gtest/gtest.h>

class Vector3Test : public ::testing::Test {
protected:
    using Vector3 = jazz::Vector3;

    void SetUp() override {
        a = Vector3(12.34, 87.5, 35.8);
        b = Vector3(8348.6, 7059.534, 346.25);
        c = Vector3(36.808, 124.7, 89.54);
        t = 9946.456;
    }

    Vector3 a, b, c;
    Vector3::RealType t{};
};

TEST_F(Vector3Test, Add) {
    EXPECT_EQ(a + b, Vector3(a.x + b.x, a.y + b.y, a.z + b.z));
    EXPECT_EQ(b + c, Vector3(b.x + c.x, b.y + c.y, b.z + c.z));
    EXPECT_EQ(c + a, Vector3(c.x + a.x, c.y + a.y, c.z + a.z));
    EXPECT_EQ(c + t, Vector3(c.x + t, c.y + t, c.z + t));
    EXPECT_EQ(c + t, t + c);
}

TEST_F(Vector3Test, Minus) {
    EXPECT_EQ(a - b, Vector3(a.x - b.x, a.y - b.y, a.z - b.z));
    EXPECT_EQ(b - c, Vector3(b.x - c.x, b.y - c.y, b.z - c.z));
    EXPECT_EQ(c - a, Vector3(c.x - a.x, c.y - a.y, c.z - a.z));
    EXPECT_EQ(c - t, Vector3(c.x - t, c.y - t, c.z - t));
}

TEST_F(Vector3Test, Mul) {
    EXPECT_EQ(a * t, Vector3(a.x * t, a.y * t, a.z * t));
    EXPECT_EQ(b * t, t * b);
}

TEST_F(Vector3Test, Div) {
    EXPECT_EQ(a / t, Vector3(a.x / t, a.y / t, a.z / t));
}

TEST_F(Vector3Test, Dot) {
    EXPECT_EQ(a * b, b * a);
    EXPECT_EQ(b * c, b.x * c.x + b.y * c.y + b.z * c.z);
}

TEST_F(Vector3Test, Cross) {
    auto crossProduct = [](const Vector3 &a, const Vector3 &b) {
        return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
    };
    EXPECT_EQ(a ^ b, crossProduct(a, b));
    EXPECT_EQ(b.cross(c), crossProduct(b, c));
}