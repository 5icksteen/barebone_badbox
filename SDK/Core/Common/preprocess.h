#pragma once

#define _QUOTE(X)  #X
#define QUOTE(X)   _QUOTE(X)
#define _CAT(X, Y) X##Y
#define CAT(X, Y)  _CAT(X, Y)

#define _GEN_STM32_HEADER(X, Y) QUOTE(stm32##X##xx##Y.h)
#define GEN_STM32_HEADER(X, Y)  _GEN_STM32_HEADER(X, Y)