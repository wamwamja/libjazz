//
// Created by meitu on 2022/3/2.
//

#ifndef LIBJAZZ_BYTEBUFFER_H
#define LIBJAZZ_BYTEBUFFER_H

#include <cstddef>

namespace jazz{
    /**
     * @brief A buffer data structure.
     *
     * For efficiency, this buffer is designed as move only. Implicit copy is not allowed.
     */
    class ByteBuffer {
    public:
        using size_type = std::size_t;
    public:
        /// @brief Default constructor.
        ByteBuffer() = default;

        /**
         * @brief Construction with size initialization.
         * @param size Size of buffer.
         */
        explicit ByteBuffer(size_type size);

        /**
         * @brief Construction with data initialization.
         * @param data  Initial data.
         * @param size  Size of data.
         */
        explicit ByteBuffer(const void *data, size_type size);

        /// @brief Disable copy constructor.
        /// In order to get a copy, please use clone() instead.
        ByteBuffer(const ByteBuffer &rhs) = delete;

        /// @brief Move constructor.
        ByteBuffer(ByteBuffer &&rhs) noexcept;

        /// @brief Destructor.
        ~ByteBuffer();

        /**
         * @brief Append data.
         * @param data
         * @param size
         */
        void append(void *data, size_type size);

        /**
         * @brief Resize the buffer.
         *
         * If the the required size can not be allocated, the function does nothing.
         * @param size New size of the buffer.
         * @return The new size resize or it may be the old size because of memory lack.
         */
        size_type resize(size_type size);

        /**
         * @brief Size reservation.
         * @param size
         * @return The new capacity or it may be the old one because of memory lack.
         */
        size_type reserve(size_type size);

        /// @brief Get the size of data stored in the buffer.
        size_type size() const;

        /// @brief Get the size that the buffer can hold.
        size_type capacity() const;

        /// @brief Get buffer data.
        char *data();

        /// @brief Get buffer data.
        const char *data() const;

        /// @brief Copy data to buffer.
        void set_data(const void *data, size_type size);

        /// @brief Check whether the buffer is empty.
        bool empty() const;

        /// @brief Clear buffer data, it's equivalent to call resize(0).
        ///
        /// To release the memory held by the buffer, call release() instead.
        void clear();

        /// @brief Release the memory managed by the buffer.
        void release();

        /// @brief Get a deep copy of the buffer.
        jazz::ByteBuffer clone() const;

        /// Disable copy assignment.
        ByteBuffer &operator=(const ByteBuffer &rhs) = delete;

        /// @brief Move assignment.
        ByteBuffer &operator=(ByteBuffer &&rhs) noexcept;

        /// @brief Warp std::memset().
        void memset(char b);

        template<class T>
        T *reinterpret() {
            return (T *) m_buffer_begin;
        }

        template<class T>
        size_type size_reinterpret() const {
            return size() / sizeof(T);
        }

    private:
        char *m_buffer_begin = nullptr;
        char *m_buffer_end = nullptr;
        char *m_ptr = nullptr;
    };
}





#endif //LIBJAZZ_BYTEBUFFER_H
