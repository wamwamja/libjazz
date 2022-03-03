//
// Created by jazz on 2022/3/2.
//

#ifndef LIBJAZZ_FUNCTION_H
#define LIBJAZZ_FUNCTION_H

namespace jazz{

    class ValArray;

    class Function {
    public:
        Function() = default;
        virtual ~Function() = default;

    public:
        virtual void eval(const ValArray* x, ValArray* fx) = 0;
    };
}



#endif //LIBJAZZ_FUNCTION_H
