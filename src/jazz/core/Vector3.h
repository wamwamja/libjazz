//
// Created by jiazh on 2022-03-02.
//

#ifndef LIBJAZZ_VECTOR3_H
#define LIBJAZZ_VECTOR3_H

#include "jazz/jazz_config.h"
#include <algorithm>

namespace jazz {
    template<typename T>
    struct Vector3_ {
    public:
        using RealType = T;
    public:
        T x{0}, y{0}, z{0};

    public:
        Vector3_() = default;

        explicit Vector3_(T x_, T y_ = 0, T z_ = 0) : x(x_), y(y_), z(z_) {};

        ~Vector3_() = default;

    public: // operator
        Vector3_ &operator+=(const Vector3_ &b) {
            x += b.x;
            y += b.y;
            z += b.z;
            return *this;
        }

        Vector3_ &operator+=(T b) {
            x += b;
            y += b;
            z += b;
            return *this;
        }

        Vector3_ operator+(const Vector3_ &b) const {
            Vector3_ res = *this;
            return std::move(res += b);
        }

        Vector3_ operator+(T b) const {
            Vector3_ res = *this;
            return std::move(res += b);
        }

        friend Vector3_ operator+(T a, const Vector3_ &b) {
            return std::move(b + a);
        }

        Vector3_ &operator-=(const Vector3_ &b) {
            x -= b.x;
            y -= b.y;
            z -= b.z;
            return *this;
        }

        Vector3_ &operator-=(T b) {
            x -= b;
            y -= b;
            z -= b;
            return *this;
        }

        Vector3_ operator-(const Vector3_ &b) const {
            Vector3_ res = *this;
            return std::move(res -= b);
        }

        Vector3_ operator-(T b) const {
            Vector3_ res = *this;
            return std::move(res -= b);
        }

        Vector3_ &operator*=(T b) {
            x *= b;
            y *= b;
            z *= b;
            return *this;
        }

        Vector3_ operator*(T b) const {
            Vector3_ res = *this;
            return std::move(res *= b);
        }

        friend Vector3_ operator*(T a, const Vector3_ &b) {
            return std::move(b * a);
        }

        Vector3_ &operator/=(T b) {
            if (b != T(0)) {
                x /= b;
                y /= b;
                z /= b;
            }
            return *this;
        }

        Vector3_ operator/(T b) const {
            Vector3_ res = *this;
            return std::move(res /= b);
        }

        bool operator==(const Vector3_ &b) const {
            return x == b.x && y == b.y && z == b.z;
        }

        // algebra
        T dot(const Vector3_ &b) const {
            return (x * b.x + y * b.y + z * b.z);
        }

        T operator*(const Vector3_ &b) const {
            return dot(b);
        }

        Vector3_ cross(const Vector3_ &b) {
            return Vector3_{y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x};
        }

        Vector3_ operator^(const Vector3_ &b) {
            return cross(b);
        }

        T norm2() const {
            return dot(*this);
        }

        T norm() const {
            return std::sqrt(norm2());
        }

    };

    using Vector3F = Vector3_<float>;
    using Vector3D = Vector3_<double>;

    using Vector3 = Vector3_<Real>;
}

#endif //LIBJAZZ_VECTOR3_H
