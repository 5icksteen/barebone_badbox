
#include <cstdint>

// extern "C"
// {
//     extern uint32_t SystemCoreClock;        /*!< System Clock Frequency (Core Clock) */
//     extern const uint8_t AHBPrescTable[16]; /*!< AHB prescalers table values */
//     extern const uint8_t APBPrescTable[8];  /*!< APB prescalers table values */
//     extern void SystemInit(void);
//     extern void SystemCoreClockUpdate(void);
// }

enum class FlashLatency
{
  _0WS,
  _1WS,
  _2WS,
  _3WS,
  _4WS,
  _5WS,
  _6WS,
  _7WS,
  _8WS,
  _9WS,
  _10WS,
  _11WS,
  _12WS,
  _13WS,
  _14WS,
  _15WS
};
void FLASH_SetLatency(FlashLatency Latency)
{
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (uint32_t)Latency);
}