//
// Created by jiazh on 2022-03-02.
//

#ifndef LIBJAZZ_VALARRAY_H
#define LIBJAZZ_VALARRAY_H

#include "jazz/core/Array.h"
#include "jazz/jazz_config.h"

namespace jazz {
    class ValArray : public Array<Real> {
    public:
        ValArray() = default;
        ValArray(ElementType* ptr, std::size_t count);
        ~ValArray() override = default;
    };
}


#endif //LIBJAZZ_VALARRAY_H
