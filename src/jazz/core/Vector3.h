//
// Created by jiazh on 2022-03-02.
//

#ifndef LIBJAZZ_VECTOR3_H
#define LIBJAZZ_VECTOR3_H

#include "jazz/jazz_config.h"
#include <algorithm>

namespace jazz {
    template<typename T>
    struct Vector3 {
    public:
        T x{0}, y{0}, z{0};

    public:
        Vector3() = default;

        explicit Vector3(T x_, T y_ = 0, T z_ = 0) : x(x_), y(y_), z(z_) {};

        ~Vector3() = default;

    public: // operator
        Vector3 &operator+=(const Vector3 &b) {
            x += b.x;
            y += b.y;
            z += b.z;
            return *this;
        }

        Vector3 &operator+=(T b) {
            x += b;
            y += b;
            z += b;
            return *this;
        }

        Vector3 operator+(const Vector3 &b) const {
            Vector3 res = *this;
            return std::move(res += b);
        }

        Vector3 operator+(T b) const {
            Vector3 res = *this;
            return std::move(res += b);
        }

        friend Vector3 operator+(T a, const Vector3 &b) {
            return std::move(b + a);
        }

        Vector3 &operator-=(const Vector3 &b) {
            x -= b.x;
            y -= b.y;
            z -= b.z;
            return *this;
        }

        Vector3 &operator-=(T b) {
            x -= b;
            y -= b;
            z -= b;
            return *this;
        }

        Vector3 operator-(const Vector3 &b) const {
            Vector3 res = *this;
            return std::move(res -= b);
        }

        Vector3 operator-(T b) const {
            Vector3 res = *this;
            return std::move(res -= b);
        }

        Vector3 &operator*=(T b) {
            x *= b;
            y *= b;
            z *= b;
            return *this;
        }

        Vector3 operator*(T b) const {
            Vector3 res = *this;
            return std::move(res *= b);
        }

        friend Vector3 operator*(T a, const Vector3 &b) {
            return std::move(b * a);
        }

        Vector3 &operator/=(T b) {
            if (b != T(0)) {
                x /= b;
                y /= b;
                z /= b;
            }
            return *this;
        }

        // algebra
        T dot(const Vector3 &b) const {
            return (x * b.x + y * b.y + z * b.z);
        }

        T operator*(const Vector3 &b) const {
            return dot(b);
        }

        Vector3 cross(const Vector3 &b) {
            return Vector3{y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x};
        }

        Vector3 operator^(const Vector3 &b) {
            return cross(b);
        }

        T norm2() const {
            return dot(*this);
        }

        T norm() const {
            return std::sqrt(norm2());
        }

    };
}

#endif //LIBJAZZ_VECTOR3_H
