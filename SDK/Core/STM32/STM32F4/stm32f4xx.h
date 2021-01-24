#pragma once

#if !defined  (STM32F4)
#define STM32F4
#endif /* STM32F4 */

#if defined(STM32F405xx)
  #include "stm32f405xx.h"
#elif defined(STM32F415xx)
  #include "stm32f415xx.h"
#elif defined(STM32F407xx)
  #include "stm32f407xx.h"
#elif defined(STM32F417xx)
  #include "stm32f417xx.h"
#elif defined(STM32F427xx)
  #include "stm32f427xx.h"
#elif defined(STM32F437xx)
  #include "stm32f437xx.h"
#elif defined(STM32F429xx)
  #include "stm32f429xx.h"
#elif defined(STM32F439xx)
  #include "stm32f439xx.h"
#elif defined(STM32F401xC)
  #include "stm32f401xc.h"
#elif defined(STM32F401xE)
  #include "stm32f401xe.h"
#elif defined(STM32F410Tx)
  #include "stm32f410tx.h"
#elif defined(STM32F410Cx)
  #include "stm32f410cx.h"
#elif defined(STM32F410Rx)
  #include "stm32f410rx.h"
#elif defined(STM32F411xE)
  #include "stm32f411xe.h"
#elif defined(STM32F446xx)
  #include "stm32f446xx.h"
#elif defined(STM32F469xx)
  #include "stm32f469xx.h"
#elif defined(STM32F479xx)
  #include "stm32f479xx.h"
#elif defined(STM32F412Cx)
  #include "stm32f412cx.h"
#elif defined(STM32F412Zx)
  #include "stm32f412zx.h"
#elif defined(STM32F412Rx)
  #include "stm32f412rx.h"
#elif defined(STM32F412Vx)
  #include "stm32f412vx.h"
#elif defined(STM32F413xx)
  #include "stm32f413xx.h"
#elif defined(STM32F423xx)
  #include "stm32f423xx.h"
#else
 #error "Please select first the target STM32F4xx device used in your application (in stm32f4xx.h file)"
#endif
