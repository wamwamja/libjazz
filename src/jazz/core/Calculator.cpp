//
// Created by meitu on 2022/3/3.
//

#include "Calculator.h"
#include "jazz/core/VectorBase.h"

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
        case FIRST_CENTRAL_5_POINT:
            auto h2 = 2.0 * h;
            df = func(x - h2) - 8.0 * func(x - h) + 8.0 * func(x + h) - func(x + h2);
            return df / 12.0 / h;
    }

    return df / h;
}

jazz::Real jazz::Calculator::numerical_derivative_second(RealFunc func, jazz::Real x, jazz::Real h,
                                                         jazz::Calculator::SecondDerivativeMethod method) {

    Real ddf = 0;
    switch (method) {

        case SECOND_CENTRAL_3_POINT:
            ddf = func(x + h) + func(x - h) - 2.0 * func(x);
            return ddf / h / h;
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
// It has a better way to improve the
// Here comes the Neville's algorithm. See https://en.wikipedia.org/wiki/Neville%27s_algorithm
//
// In short, the algorithm can be understood with the following triangle table.
// x_0 y_0 = P_0
//                P_{01}
// x_1 y_1 = P_1          P_{012}
//                P_{12}            P_{0123}
// x_2 y_2 = P_2          P_{123}
//                P_{23}
// x_3 y_3 = P_3
// The table shows an example for calculate the polynomial passing 4 points, where x_i and y_i has the same meaning
// as previous; P_{(i)(i+1)..(j)} is the polynomial passing through points (x_i,y_i) ... (x_j, y_j).
// There is a relationship between the son and its two parents,
// P_{i)(i+1)..(i+m)} = \frac{ (x-x_{i+m})P_{i(i+1)...(i+m)-1} - (x - x_i)P_{(i+1)(i+2)...(i_m)} } { x_i - x_{i+m}} (*)
// A further improvement is keep track of the small differences between parents and sons, namely to define
// C_{m,i} = P_{i...(i+m)} - P_{i...(i+m-1)}
// D_{m,i} = P_{i...(i+m)} - P_{(i+1)...(i+m)}
// One can easily derive from (*) that
// D_{m+1,i} = \frac{ (x_{i+m+1-x} - x)(C_{m,i+1} - D_{m,i})}{ x_i - x_{i+m+1}}
// C_{m+1,i} = \frac{ (x_i - x)(C_{m,i+1}-D_{m,i})} { x_i - x_{i+m+1}}
//
// The final answer P_{0...(N-1)} is equal to the sum of any y_i plus a set of
// C’s and/or D’s that form a path through the family tree to the rightmost son.
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
    return y;
}
