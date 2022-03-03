//
// Created by jazz on 2022/3/2.
//

#ifndef LIBJAZZ_ARRAY_H
#define LIBJAZZ_ARRAY_H

#include "jazz/core/ByteBuffer.h"

namespace jazz {
    template<typename E>
    class Array {
    public:
        using ElementType = E;
    public:
        Array() = default;

        virtual ~Array() = default;

    public:

        std::size_t length() const {
            return elem_count;
        }

        ElementType &at(std::size_t index) {
            if (index < length()) {
                return elem_data[index];
            } else {
                return ElementType();
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
        Array &wrap(ElementType *ptr, std::size_t length) {
            elem_data = ptr;
            elem_count = length;
            return *this;
        }

    private:
        ElementType *elem_data = nullptr;
        std::size_t elem_count = 0;
    };
}


#endif //LIBJAZZ_ARRAY_H
