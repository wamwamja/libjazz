//
// Created by meitu on 2022/3/2.
//

#include "ByteBuffer.h"

#include <cstdlib>
#include <cstring>
#include <algorithm>

jazz::ByteBuffer::size_type jazz::ByteBuffer::resize(jazz::ByteBuffer::size_type size) {
    if (reserve(size) >= size) {
        m_ptr = m_buffer_begin + size;
    }
    return this->size();
}

jazz::ByteBuffer::ByteBuffer(jazz::ByteBuffer::size_type size) {
    resize(size);
}

jazz::ByteBuffer::~ByteBuffer() {
    release();
}

jazz::ByteBuffer::size_type jazz::ByteBuffer::size() const {
    if (m_buffer_begin == nullptr)
        return 0;
    else
        return m_ptr - m_buffer_begin;
}

jazz::ByteBuffer::size_type jazz::ByteBuffer::capacity() const {
    if (m_buffer_begin == nullptr)
        return 0;
    else
        return m_buffer_end - m_buffer_begin;
}

char *jazz::ByteBuffer::data() {
    return m_buffer_begin;
}

void jazz::ByteBuffer::set_data(const void *data, jazz::ByteBuffer::size_type size) {
    resize(size);
    std::memcpy(m_buffer_begin, data, size);
}

jazz::ByteBuffer::size_type jazz::ByteBuffer::reserve(size_type size) {
    if (capacity() < size) {
        auto temp = (char *) malloc(size);
        auto old_size = this->size();
        if (temp != nullptr) {
            std::memcpy(temp, m_buffer_begin, old_size);
            free(m_buffer_begin);
            m_buffer_begin = temp;
            m_buffer_end = m_buffer_begin + size;
            m_ptr = m_buffer_begin + old_size;
        }
    }
    return capacity();
}

bool jazz::ByteBuffer::empty() const {
    return capacity() == 0;
}

void jazz::ByteBuffer::clear() {
    resize(0);
}

void jazz::ByteBuffer::release() {
    free(m_buffer_begin);
    m_buffer_begin = nullptr;
    m_buffer_end = nullptr;
    m_ptr = nullptr;
}

jazz::ByteBuffer::ByteBuffer(jazz::ByteBuffer &&rhs) noexcept {
    m_buffer_begin = rhs.m_buffer_begin;
    m_buffer_end = rhs.m_buffer_end;
    m_ptr = rhs.m_ptr;
    rhs.m_buffer_begin = nullptr;
    rhs.release();
}

jazz::ByteBuffer &jazz::ByteBuffer::operator=(jazz::ByteBuffer &&rhs) noexcept {
    if (&rhs != this) {
        release();
        m_buffer_begin = rhs.m_buffer_begin;
        m_buffer_end = rhs.m_buffer_end;
        m_ptr = rhs.m_ptr;
        rhs.m_buffer_begin = nullptr;
        rhs.release();
    }

    return *this;
}

jazz::ByteBuffer jazz::ByteBuffer::clone() const {
    return std::move(ByteBuffer(data(), size()));
}

const char *jazz::ByteBuffer::data() const {
    return m_buffer_begin;
}

jazz::ByteBuffer::ByteBuffer(const void *data, jazz::ByteBuffer::size_type size) {
    set_data(data, size);
}

void jazz::ByteBuffer::append(void *data, jazz::ByteBuffer::size_type size) {
    auto required_size = size + this->size();
    if (required_size >= capacity())
        reserve(2 * required_size);
    std::memcpy(m_ptr, data, size);
    m_ptr += size;
}

void jazz::ByteBuffer::memset(char b) {
    std::memset(m_buffer_begin, b, size());
}

