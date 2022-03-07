//
// Created by meitu on 2022/3/4.
//

#ifndef LIBJAZZ_VECEXPR_H
#define LIBJAZZ_VECEXPR_H

#include <cstddef>
#include <cassert>

namespace jazz {

    template<typename Vec, typename T = double>
    class VecExpr {

    public:
        using ValueType = T;
    public:
        VecExpr() = default;

        virtual ~VecExpr() = default;

        virtual T operator[](std::size_t i) const {
            return static_cast<Vec const &>(*this)[i];
        }

        virtual std::size_t size() const {
            return static_cast<Vec const &>(*this).size();
        };
    };

    template<typename U, typename V>
    class VecSumExpr : public VecExpr<VecSumExpr<U, V>, decltype(typename U::ValueType(0) + typename V::ValueType(0))> {
        const U &u_;
        const V &v_;
    public:
        VecSumExpr(const U &u, const V &v) : u_(u), v_(v) {
            assert(u.size() == v.size());
        }

        ~VecSumExpr() = default;

        auto operator[](size_t i) const -> decltype(u_[0] + v_[0]) { return u_[i] + v_[i]; }

        size_t size() const { return u_.size(); }
    };

    template<typename U, typename V>
    VecSumExpr<U, V> operator+(const VecExpr<U> &u, const VecExpr<V> &v) {
        return VecSumExpr<U, V>(*reinterpret_cast<const U *>(&u), *reinterpret_cast<const V *>(&v));
    }
}

#endif //LIBJAZZ_VECEXPR_H
