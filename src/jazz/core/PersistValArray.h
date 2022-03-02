//
// Created by meitu on 2022/3/2.
//

#ifndef LIBJAZZ_PERSISTVALARRAY_H
#define LIBJAZZ_PERSISTVALARRAY_H

#include "Array.h"
#include "jazz/core/jazz_config.h"
#include "jazz/core/ByteBuffer.h"

namespace jazz {
    class PersistValArray : public Array<Real> {
    public:
        explicit PersistValArray(std::size_t size);

        PersistValArray(std::size_t size, ElementType val);

    private:
        enum {
            ElementSize = sizeof(Real)
        };

    private:
        ByteBuffer buffer;
    };
}


#endif //LIBJAZZ_PERSISTVALARRAY_H
