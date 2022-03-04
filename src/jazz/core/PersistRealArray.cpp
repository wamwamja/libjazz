//
// Created by meitu on 2022/3/2.
//

#include "PersistRealArray.h"
#include "jazz/core/ByteBuffer.h"

jazz::PersistRealArray::PersistRealArray(std::size_t size) {
    buffer = new ByteBuffer(ElementSize * size);
    bind();
}

jazz::PersistRealArray::PersistRealArray(std::size_t size, double val) {
    buffer = new ByteBuffer(ElementSize * size);
    wrap_raw(buffer->reinterpret<ElementType>(), size);
    auto ptr = buffer->reinterpret<ElementType>();
    for (int i = 0; i < size; ++i) {
        ptr[i] = val;
    }
}

jazz::PersistRealArray::~PersistRealArray() {
    delete buffer;
}

jazz::PersistRealArray::PersistRealArray(std::size_t size, double *val_ptr) {
    buffer = new ByteBuffer(val_ptr, ElementSize * size);
    bind();
}

void jazz::PersistRealArray::bind() {
    if (buffer != nullptr)
        wrap_raw(buffer->reinterpret<ElementType>(), buffer->size_reinterpret<ElementType>());
    else
        wrap_raw(nullptr, 0);
}

jazz::PersistRealArray::PersistRealArray(const jazz::PersistRealArray &rhs) : RealArray(rhs) {
    buffer = new ByteBuffer(rhs.buffer->clone());
    bind();
}

jazz::PersistRealArray::PersistRealArray(jazz::PersistRealArray &&rhs) noexcept {
    buffer = rhs.buffer;
    bind();

    rhs.buffer = nullptr;
    rhs.bind();
}

jazz::PersistRealArray &jazz::PersistRealArray::operator=(const jazz::PersistRealArray &rhs) {
    if (this != &rhs) {
        buffer->set_data(rhs.buffer->data(), rhs.buffer->size());
        bind();
    }

    return *this;
}

jazz::PersistRealArray &jazz::PersistRealArray::operator=(jazz::PersistRealArray &&rhs) noexcept {
    if (this != &rhs) {
        delete buffer;
        buffer = rhs.buffer;
        bind();

        rhs.buffer = nullptr;
        rhs.bind();
    }

    return *this;
}

