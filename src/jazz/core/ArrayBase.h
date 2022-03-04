//
// Created by jazz on 2022/3/2.
//

#ifndef LIBJAZZ_ARRAYBASE_H
#define LIBJAZZ_ARRAYBASE_H

#include "jazz/core/ByteBuffer.h"
#include <algorithm>
#include <exception>

namespace jazz {
    template<typename E>
    class ArrayBase {
    public:
        using ElementType = E;
    public:
        ArrayBase() = default;

        virtual ~ArrayBase() = default;

    public:
        static ArrayBase<ElementType> wrap(ElementType *ptr, std::size_t length) {
            ArrayBase<ElementType> array;
            array.wrap_raw(ptr, length);
            return std::move(array);
        }

    public:

        std::size_t length() const {
            return elem_count;
        }

        ElementType &at(std::size_t index) {
            if (index < length()) {
                return elem_data[index];
            } else {
                throw std::overflow_error("Index overflow.");
            }
        }

        ElementType at(std::size_t index) const {
            if (index < length()) {
                return elem_data[index];
            } else {
                return ElementType();
            }
        }

        ElementType &operator[](std::size_t index) {
            return elem_data[index];
        }

        ElementType operator[](std::size_t index) const {
            return elem_data[index];
        }

    protected:
        ArrayBase &wrap_raw(ElementType *ptr, std::size_t length) {
            elem_data = ptr;
            elem_count = length;
            return *this;
        }

    private:
        ElementType *elem_data = nullptr;
        std::size_t elem_count = 0;
    };
}


#endif //LIBJAZZ_ARRAYBASE_H
