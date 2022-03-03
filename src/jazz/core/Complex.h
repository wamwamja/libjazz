//
// Created by jazz on 2022/3/2.
//

#ifndef LIBJAZZ_COMPLEX_H
#define LIBJAZZ_COMPLEX_H

#include "jazz/jazz_config.h"

namespace jazz {
    template<typename T>
    class Complex_ {
    public:
        Complex_() = default;

        explicit Complex_(T real, T imag = T(0)) : re_(real), im_(imag) {};

        ~Complex_() = default;

        T re() const {
            return re_;
        }

        T &re() {
            return re_;
        }

        T im() const {
            return im_;
        }

        T &im() {
            return im_;
        }

        Complex_ conj() const {
            return Complex_{re_, -im_};
        }

        T abs() const {
            return std::sqrt(re_ * re_ + im_ * im_);
        }

        Complex_ &operator+=(const Complex_ &b) {
            this->re_ += b.re_;
            this->im_ += b.im_;
            return *this;
        }

        Complex_ &operator+=(T b) {
            this->re_ += b;
            return *this;
        }

        Complex_ &operator-=(const Complex_ &b) {
            this->re_ -= b.re_;
            this->im_ -= b.im_;
            return *this;
        }

        Complex_ &operator-=(T b) {
            this->re_ -= b;
            return *this;
        }

        Complex_ &operator*=(const Complex_ &b) {
            auto r = this->re_ * b.re_ - this->im_ * b.im_;
            auto i = this->re_ * b.im_ + this->im_ * b.re_;
            this->re_ = r;
            this->im_ = i;
            return *this;
        }

        Complex_ &operator*=(T b) {
            this->re_ *= b;
            this->im_ *= b;
            return *this;
        }

        Complex_ &operator/=(const Complex_ &b) {
            if (b.im_ == T(0)) {
                if (b.re_ != 0) {
                    this->re_ /= b.re_;
                    this->im_ /= b.re_;
                }
            } else {
                this->operator*=(b.conj());
                auto t = b.re_ * b.re_ + b.im_ * b.im_;
                this->im_ /= t;
                this->re_ /= t;
            }
            return *this;
        }

        Complex_ &operator/=(T b) {
            if (b != 0) {
                this->re_ /= b;
                this->im_ /= b;
            }

            return *this;
        }

        Complex_ operator+(const Complex_ &b) const {
            Complex_ res = *this;
            return std::move(res += b);
        }

        Complex_ operator+(T b) const {
            Complex_ res = *this;
            return std::move(res += b);
        }

        friend Complex_ operator+(T a, const Complex_ &b) {
            return b + a;
        }

        Complex_ operator-(const Complex_ &b) const {
            Complex_ res = *this;
            return std::move(res -= b);
        }

        Complex_ operator-(T b) {
            Complex_ res = *this;
            return std::move(res -= b);
        }

        friend Complex_ operator-(T a, const Complex_ &b) {
            return Complex_(a) - b;
        }

        Complex_ operator*(const Complex_ &b) const {
            Complex_ res = *this;
            return std::move(res *= b);
        }

        Complex_ operator*(T b) const {
            Complex_ res = *this;
            return std::move(res *= b);
        }

        friend Complex_ operator*(T a, const Complex_ &b) {
            return b * a;
        }

        Complex_ operator/(const Complex_ &b) const {
            Complex_ res = *this;
            return std::move(res /= b);
        }

        Complex_ operator/(T b) const {
            Complex_ res = *this;
            return std::move(res /= b);
        }

        friend Complex_ operator/(T a, const Complex_ &b) {
            return Complex_(a) / b;
        }

        // inverse
        Complex_ operator-() {
            return Complex_{-re_, -im_};
        }

        // comparison
        bool operator==(const Complex_ &b) const {
            return (re_ == b.re_) && (im_ == b.im_);
        }

    private:
        T re_ = T{0};
        T im_ = T{0};
    };

    using ComplexF = Complex_<float>;
    using ComplexD = Complex_<double>;

    using Complex = ComplexD;
}

#endif //LIBJAZZ_COMPLEX_H
