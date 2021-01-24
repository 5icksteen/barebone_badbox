#pragma once

#include <cstddef>
#include <cstdint>
#include <numbers>

#include "target.h"

// using std::numbers::pi;

static inline int32_t limit(int32_t data, int32_t min, int32_t max) {
    return data < min ? min : max < data ? max : data;
}

template <typename T, size_t N>
static inline T ssat(T value, size_t N) { __SSAT(value, N); }