//
// Created by meitu on 2022/3/2.
//

#ifndef LIBJAZZ_JAZZ_CONFIG_H
#define LIBJAZZ_JAZZ_CONFIG_H

#include <cstring>
#include <memory>
#include <cmath>

#if defined(_WIN32_) || defined(WIN32) || defined(_WIN64_) || defined(WIN64)
#define JAZZ_EXPORT __declspec(dllexport)
#elif defined(_ADNROID_) || defined(ANDROID) || defined(__APPLE__) || defined(__linux__)
#define JAZZ_EXPORT __attribute__((visibility("default")))
#else
#define JAZZ_EXPORT
#endif

namespace jazz{
    using Real = double;
}

#endif //LIBJAZZ_JAZZ_CONFIG_H
