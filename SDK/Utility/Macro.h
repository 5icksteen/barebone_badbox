#pragma once

// #define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
template<std::size_t N, class T>
consteval std::size_t countof(T(&)[N]) { return N; }