//
// Created by meitu on 2022/3/2.
//

#ifndef LIBJAZZ_PERSISTVALARRAY_H
#define LIBJAZZ_PERSISTVALARRAY_H

#include "ValArray.h"
#include "jazz/jazz_config.h"

namespace jazz {
    class  ByteBuffer;
    class PersistValArray : public ValArray {
    public:
        explicit PersistValArray(std::size_t size);

        PersistValArray(std::size_t size, ElementType val);

        ~PersistValArray() override;

    private:
        enum {
            ElementSize = sizeof(Real)
        };

    private:
        ByteBuffer* buffer = nullptr;
    };
}


#endif //LIBJAZZ_PERSISTVALARRAY_H
