//
// Created by jazz on 2022/3/2.
//

#ifndef LIBJAZZ_PERSISTREALARRAY_H
#define LIBJAZZ_PERSISTREALARRAY_H

#include "ArrayBase.h"
#include "jazz/jazz_config.h"

namespace jazz {
    class ByteBuffer;

    using RealArray = ArrayBase<Real>;

    class PersistRealArray : public RealArray {
    public:
        explicit PersistRealArray(std::size_t size);

        PersistRealArray(std::size_t size, ElementType val);

        PersistRealArray(std::size_t size, ElementType *val_ptr);

        PersistRealArray(const PersistRealArray& rhs);
        PersistRealArray(PersistRealArray&& rhs) noexcept ;

        PersistRealArray& operator=(const PersistRealArray& rhs);
        PersistRealArray& operator=(PersistRealArray&& rhs) noexcept;

        ~PersistRealArray() override;

    protected:
        enum {
            ElementSize = sizeof(Real)
        };

        void bind();

    private:
        ByteBuffer *buffer = nullptr;
    };
}


#endif //LIBJAZZ_PERSISTREALARRAY_H
