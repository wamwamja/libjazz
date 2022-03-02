//
// Created by meitu on 2022/3/2.
//

#include "PersistValArray.h"
#include "jazz/core/ByteBuffer.h"

jazz::PersistValArray::PersistValArray(std::size_t size) {
    buffer = new ByteBuffer(ElementSize*size);
    wrap(buffer->reinterpret<ElementType>(), size);
}

jazz::PersistValArray::PersistValArray(std::size_t size, double val) {
    buffer = new ByteBuffer(ElementSize*size);
    wrap(buffer->reinterpret<ElementType>(), size);
    auto ptr = buffer->reinterpret<ElementType>();
    for (int i = 0; i < size; ++i) {
        ptr[i] = val;
    }
}

jazz::PersistValArray::~PersistValArray() {
    delete buffer;
}

