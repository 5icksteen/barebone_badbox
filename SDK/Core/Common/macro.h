#pragma once

#include <cstddef>

template<std::size_t N, class T>
consteval std::size_t countof(T(&)[N]) { return N; }

#define __WEAK_ALIAS(X) __attribute__((weak, alias(X)))
#define __SECTION_USED(X) __attribute__((section(X), used))

#define _QUOTE(X)  #X
#define QUOTE(X)   _QUOTE(X)
#define _CAT(X, Y) X##Y
#define CAT(X, Y)  _CAT(X, Y)

#define _GEN_HEADER(X, Y) QUOTE(X##Y.h)
#define GEN_HEADER(X, Y)  _GEN_HEADER(X, Y)