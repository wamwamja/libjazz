//
// Created by meitu on 2022/3/4.
//

#ifndef LIBJAZZ_VECTORBASE_H
#define LIBJAZZ_VECTORBASE_H

#include "jazz/core/ArrayBase.h"

#include "jazz/core/ExprT.h"

#include "jazz/core/ByteBuffer.h"

namespace jazz {

    template<typename E>
    class VectorBase : public ArrayBase<E>, public VecExpr<VectorBase<E>, E> {
    public:
        using ValueType = E;

    public:
        VectorBase() = default;

        VectorBase(std::size_t size, const ValueType *val_ptr) {
            buffer.set_data(val_ptr, size * sizeof(ValueType));
            bind();
        }

        VectorBase(const VectorBase &rhs);

        template<typename Expr>
        VectorBase(const Expr &expr) {
            auto size = expr.size();
            buffer.resize(size * sizeof(E));
            bind();
            for (int i = 0; i < size; ++i) {
                this->operator[](i) = static_cast<E>(expr[i]);
            }
        }

        virtual ~VectorBase() = default;

    protected:
        void bind() {
            ArrayBase<E>::wrap_raw(buffer.template reinterpret<E>(), buffer.template size_reinterpret<E>());
        }

    private:
        ByteBuffer buffer;
    };

    template<typename E>
    VectorBase<E>::VectorBase(const VectorBase &rhs) {
        buffer = rhs.buffer.clone();
    }
}


#endif //LIBJAZZ_VECTORBASE_H
