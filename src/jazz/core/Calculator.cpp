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

jazz::Real
jazz::Calculator::lagrange_interpolate(jazz::Real *ax, const jazz::Real *ay, int count, jazz::Real x, jazz::Real *dy) {
    auto c = new Real[count];
    auto d = new Real[count];
    auto dif = std::fabs(x - ax[0]);
    Real den, dift, ho, hp, w;
    int ns = 1;
    for (int i = 0; i < count; ++i) {
        if ((dift = std::fabs(x - ax[i]) < dif)) {
            ns = i;
            dif = dift;
        }
        c[i] = ay[i];
        d[i] = ay[i];
    }

    Real dy_t;

    auto y = ay[ns--];
    auto M = count - 1;
    for (int m = 0; m < M; ++m) {
        auto N = count - m;
        for (int n = 0; n < N; ++n) {
            ho = ax[n] - x;
            hp = ax[n + m] - x;
            w = c[n + 1] - d[n];
            if ((den = ho - hp) < Zero::value) {
                // TODO handle error here.
            }
            den = w / den;
            d[n] = hp * den;
            c[n] = ho * den;
        }

        dy_t = (2 * ns < N) ? c[ns + 1] : d[ns--];
        y += dy_t;
    }

    if (dy != nullptr)
        *dy = dy_t;

    delete[]c;
    delete[]d;
    return 0;
}
