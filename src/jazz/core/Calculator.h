//
// Created by meitu on 2022/3/3.
//

#ifndef LIBJAZZ_CALCULATOR_H
#define LIBJAZZ_CALCULATOR_H

#include "jazz/jazz_config.h"

namespace jazz {
    class Calculator {
    public:
        using RealFunc = Real(*)(Real);
        enum FirstDerivativeMethod {
            FIRST_FORWARD_2_POINT, FIRST_BACKWARD_2_POINT, FIRST_CENTRAL_3_POINT,
        };

        enum SecondDerivativeMethod {
            SECOND_CENTRAL_3_POINT, SECOND_CENTRAL_5_POINT
        };

        static Real numerical_derivative(RealFunc func, Real x, Real h, FirstDerivativeMethod method = FIRST_CENTRAL_3_POINT);

        static Real
        numerical_derivative_second(RealFunc func, Real x, Real h, SecondDerivativeMethod method = SECOND_CENTRAL_3_POINT);


    };
}


#endif //LIBJAZZ_CALCULATOR_H