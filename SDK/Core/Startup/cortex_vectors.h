#pragma once
#include <cstdint>

#include "macro.h"

extern uint32_t __stack_top;

uint32_t* __stack_pointer __SECTION_USED(".stack_pointer") = &__stack_top;

extern "C" void Default_Handler();
extern void     Reset_Handler();

void NMI_handler() __WEAK_ALIAS("Default_Handler");
void HardFault_Handler() __WEAK_ALIAS("Default_Handler");
void MemManage_Handler() __WEAK_ALIAS("Default_Handler");
void BusFault_Handler() __WEAK_ALIAS("Default_Handler");
void UsageFault_Handler() __WEAK_ALIAS("Default_Handler");
void SVC_Handler() __WEAK_ALIAS("Default_Handler");
void DebugMon_Handler() __WEAK_ALIAS("Default_Handler");
void PendSV_Handler() __WEAK_ALIAS("Default_Handler");
void SysTick_Handler() __WEAK_ALIAS("Default_Handler");

void (*__cortex_vectors[])() __SECTION_USED(".cortex_vectors") = {
    Reset_Handler,
    NMI_handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,
};

constexpr size_t NUM_CORTEX_VECTORS = countof(__cortex_vectors);