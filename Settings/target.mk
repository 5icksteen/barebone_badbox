ROM_START ?= 0x08000000
ROM_SIZE ?= 16K
RAM_START ?= 0x20000000
RAM_SIZE ?= 16K
ROM_ALIGN ?= 0x4

CORE_PARAMS += ROM_START=$(ROM_START)
CORE_PARAMS += ROM_SIZE=$(ROM_SIZE)
CORE_PARAMS += RAM_START=$(RAM_START)
CORE_PARAMS += RAM_SIZE=$(RAM_SIZE)
CORE_PARAMS += ROM_ALIGN=$(ROM_ALIGN)

# FLASH_SIZE += $(findstring x4, $(TARGET))
# FLASH_SIZE += $(findstring x6, $(TARGET))
# FLASH_SIZE += $(findstring x8, $(TARGET))
# FLASH_SIZE += $(findstring xB, $(TARGET))
# FLASH_SIZE += $(findstring xC, $(TARGET))
# FLASH_SIZE += $(findstring xD, $(TARGET))
# FLASH_SIZE += $(findstring xE, $(TARGET))
# FLASH_SIZE += $(findstring xF, $(TARGET))
# FLASH_SIZE += $(findstring xG, $(TARGET))
# FLASH_SIZE += $(findstring xI, $(TARGET))

SVD_NAME = $(patsubst %$(strip $(FLASH_SIZE)),%.svd,$(TARGET))
SVD_FILE = ./SDK/Core/SVD/$(SVD_NAME)

ifeq ($(findstring x4, $(TARGET)), x4)
ROM_SIZE := 16K
FLASH_SIZE := x4
else ifeq ($(findstring x6, $(TARGET)), x6)
ROM_SIZE := 32K
FLASH_SIZE := x6
else ifeq ($(findstring x8, $(TARGET)), x8)
ROM_SIZE := 64K
FLASH_SIZE := x8
else ifeq ($(findstring xB, $(TARGET)), xB)
ROM_SIZE :=128K
FLASH_SIZE := xB
else ifeq ($(findstring xC, $(TARGET)), xC)
ROM_SIZE := 256K
FLASH_SIZE := xC
else ifeq ($(findstring xD, $(TARGET)), xD)
ROM_SIZE := 384K
FLASH_SIZE := xD
else ifeq ($(findstring xE, $(TARGET)), xE)
ROM_SIZE := 512K
FLASH_SIZE := xE
else ifeq ($(findstring xF, $(TARGET)), xF)
ROM_SIZE := 768K
FLASH_SIZE := xF
else ifeq ($(findstring xG, $(TARGET)), xG)
ROM_SIZE := 1M
FLASH_SIZE := xG
else ifeq ($(findstring xI, $(TARGET)), xI)
ROM_SIZE := 1M
FLASH_SIZE := xI
endif

SVD_NAME = $(patsubst %$(strip $(FLASH_SIZE)),%.svd,$(TARGET))
SVD_FILE = ./SDK/Core/SVD/$(SVD_NAME)

# ifeq ($(findstring STM32, $(CORE_DEFS)), STM32)
# endif
ifeq ($(findstring STM32F0, $(TARGET)), STM32F0)
CORE_FLAGS := -mthumb -mcpu=cortex-m0 -mfloat-abi=soft
CORE_DEFS = $(TARGET) STM32F0 TARGET_SERIES=f0
endif
ifeq ($(findstring STM32F1, $(TARGET)), STM32F1)
CORE_FLAGS := -mthumb -mcpu=cortex-m3 -mfloat-abi=soft
CORE_DEFS = $(TARGET) STM32F1 TARGET_SERIES=f1
endif
ifeq ($(findstring STM32F2, $(TARGET)), STM32F2)
CORE_FLAGS := -mthumb -mcpu=cortex-m3 -mfloat-abi=soft
CORE_DEFS = $(TARGET) STM32F2 TARGET_SERIES=f2
endif
ifeq ($(findstring STM32F3, $(TARGET)), STM32F3)
CORE_FLAGS := -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
CORE_DEFS = $(TARGET) STM32F3 TARGET_SERIES=f3
endif
ifeq ($(findstring STM32F4, $(TARGET)), STM32F4)
CORE_FLAGS := -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
CORE_DEFS = $(TARGET) STM32F4 TARGET_SERIES=f4 USE_FULL_LL_DRIVER
endif
ifeq ($(findstring STM32F7, $(TARGET)), STM32F7)
CORE_FLAGS := -mthumb -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-sp-d16
CORE_DEFS = $(TARGET) STM32F7 TARGET_SERIES=f7
endif
ifeq ($(findstring STM32G0, $(TARGET)), STM32G0)
CORE_FLAGS := -mthumb -mcpu=cortex-m0plus -mfloat-abi=soft
CORE_DEFS = $(TARGET) STM32G0 TARGET_SERIES=g0
endif
ifeq ($(findstring STM32G4, $(TARGET)), STM32G4)
CORE_FLAGS := -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
CORE_DEFS = $(TARGET) STM32G4 TARGET_SERIES=g4
endif
ifeq ($(findstring STM32H7, $(TARGET)), STM32H7)
CORE_FLAGS := -mthumb -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-sp-d16
CORE_DEFS = $(TARGET) STM32H7 TARGET_SERIES=h7
endif
ifeq ($(findstring STM32L0, $(TARGET)), STM32L0)
CORE_FLAGS := -mthumb -mcpu=cortex-m0plus -mfloat-abi=soft
CORE_DEFS = $(TARGET) STM32L0 TARGET_SERIES=l0
endif
ifeq ($(findstring STM32L1, $(TARGET)), STM32L1)
CORE_FLAGS := -mthumb -mcpu=cortex-m3 -mfloat-abi=soft
CORE_DEFS = $(TARGET) STM32L1 TARGET_SERIES=l1
endif
ifeq ($(findstring STM32L4, $(TARGET)), STM32L4)
CORE_FLAGS := -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
CORE_DEFS = $(TARGET) STM32L4 TARGET_SERIES=l4
endif
ifeq ($(findstring STM32l5, $(TARGET)), STM32L5)
CORE_FLAGS := -mthumb -mcpu=cortex-m33 -mfloat-abi=hard -mfpu=fpv5-sp-d16
CORE_DEFS = $(TARGET) STM32L5 TARGET_SERIES=l5
endif