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

// Lagrange Interpolation
// Assume we have N+1 points y_0 = f(x_0), ... , y_N = f(x_N) where all the x_i are distinct 2-by-2.
// Classic formulae : P_N(x) = \sum_{i=0}^{N} \prod_{k \ne i} \frac{x-x_k}{x_i - x_k} y_i
// Write P_N as
// P_N = a_0 + a_1(x-x_0) + a_1(x-x0)(x-x_1) + ... + a_N(x-x_0)...(x-x_{N-1})
// then we get
// a_0 = f(x_0)
// a_0 + a_1(x_1-x_0) = f(x_1)
// a_0 + a_1(x_2-x_0) + a_2(x_2-x_0)(x_2-x_1) = f(x_2)
// ...       ...             ...                ...
// We calculate a_k and f(x) \approx P_N(x), by a recursive method
// a_0 = f(x_0)                                     f_{0x} = (f(x)-f(x_0))/(x-x_0)
// a_1 = (f(x_1)-a_0)/(x_1-x_0) = f_{01}            f_{01x} = (f_{0x} - f_{01})/(x-x_1)
// a_2 = ... = f_{012}                              f_{012x} = (f_{01x} - f_{012})/(x-x_2)
//       ...                                         ...
// Note that P_N(x) = a_0 + f_{01}(x_1-x_0) + f_{012}(x_2-x_0)(x_2-x_1) + ... + f_{012...N}(...)
//
jazz::Real
jazz::Calculator::lagrange_interpolate(jazz::Real *xi, const jazz::Real *yi, int count, jazz::Real x, jazz::Real *dy) {
    auto c = new Real[count];
    auto d = new Real[count];
    auto dif = std::fabs(x - xi[0]);
    Real den, dift, ho, hp, w;
    int ns = 1;
    for (int i = 0; i < count; ++i) {
        dift = std::fabs(x - xi[i]);
        if (dift < dif) {
            ns = i;
            dif = dift;
        }
        c[i] = yi[i];
        d[i] = yi[i];
    }

    Real dy_t;

    auto y = yi[ns--];
    auto M = count - 1;
    for (int m = 0; m < M; ++m) {
        auto N = count - m;
        for (int n = 0; n < N; ++n) {
            ho = xi[n] - x;
            hp = xi[n + m] - x;
            w = c[n + 1] - d[n];
            den = ho - hp;
            if (den < Zero::value) {
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
