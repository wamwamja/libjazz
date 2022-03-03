//
// Created by meitu on 2022/3/3.
//

#include "Calculator.h"

jazz::Real jazz::Calculator::numerical_derivative(RealFunc func, jazz::Real x, jazz::Real h,
                                                  jazz::Calculator::FirstDerivativeMethod method) {
    Real df = 0;
    switch (method) {
        case FIRST_FORWARD_2_POINT:
            df = func(x + h) - func(x);
            return df / h;
            break;
        case FIRST_BACKWARD_2_POINT:
            df = func(x) - func(x - h);
            return df / h;
            break;
        case FIRST_CENTRAL_3_POINT:
            df = func(x + h) - func(x - h);
            return df / (2.0 * h);
            break;
    }

    return df / h;
}

jazz::Real jazz::Calculator::numerical_derivative_second(RealFunc func, jazz::Real x, jazz::Real h,
                                                         jazz::Calculator::SecondDerivativeMethod method) {

    Real ddf = 0;
    switch (method) {

        case SECOND_CENTRAL_3_POINT:
            ddf = func(x + h) - func(x - h) - 2.0 * func(x);
            return ddf / h / h;
            break;
        case SECOND_CENTRAL_5_POINT:
            auto h2 = 2.0 * h;
            ddf = func(x - h2) - 8.0 * func(x - h) - 8.0 * func(x + h) - func(x + h2);
            return ddf / 12.0 / h;
            break;
    }
    return 0;
}
