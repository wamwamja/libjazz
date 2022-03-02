//
// Created by jiazh on 2022-03-02.
//

#include "ValArray.h"

jazz::ValArray::ValArray(double *ptr, std::size_t count) {
    wrap(ptr, count);
}