#pragma once

extern unsigned __stack_top;
__attribute__((section(".stack_pointer"), used)) unsigned *__stack_pointer = &__stack_top;

extern "C" void Default_Handler();
extern "C" void Reset_Handler();

__attribute__((weak, alias("Default_Handler"))) void NMI_handler();
__attribute__((weak, alias("Default_Handler"))) void HardFault_Handler();
__attribute__((weak, alias("Default_Handler"))) void MemManage_Handler();
__attribute__((weak, alias("Default_Handler"))) void BusFault_Handler();
__attribute__((weak, alias("Default_Handler"))) void UsageFault_Handler();
__attribute__((weak, alias("Default_Handler"))) void SVC_Handler();
__attribute__((weak, alias("Default_Handler"))) void DebugMon_Handler();
__attribute__((weak, alias("Default_Handler"))) void PendSV_Handler();
__attribute__((weak, alias("Default_Handler"))) void SysTick_Handler();

__attribute__((section(".cortex_vectors"), used)) void (*__cortex_vectors[])() = {
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
