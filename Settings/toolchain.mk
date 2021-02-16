TOOLS := arm-none-eabi-
AR := $(TOOLS)ar
AS := $(TOOLS)as
# AS := $(TOOLS)g++ -x assembler-with-cpp
CC := $(TOOLS)gcc
CXX := $(TOOLS)g++
CPP := $(CC) -E
CP := $(TOOLS)objcopy
SZ := $(TOOLS)size
HEX := $(CP) -O ihex
BIN := $(CP) -O binary -S

C_SOURCES += $(wildcard *.c)
C_SOURCES += $(wildcard */*.c)
C_SOURCES += $(wildcard */*/*.c)
C_SOURCES += $(wildcard */*/*/*.c)
C_SOURCES += $(wildcard */*/*/*/*.c)
C_SOURCES += $(wildcard */*/*/*/*/*.c)
C_SOURCES += $(wildcard */*/*/*/*/*/*.c)
C_SOURCES += $(wildcard */*/*/*/*/*/*/*.c)
OBJECTS += $(addprefix $(OBJ_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

CXX_SOURCES += $(wildcard *.cc)
CXX_SOURCES += $(wildcard */*.cc)
CXX_SOURCES += $(wildcard */*/*.cc)
CXX_SOURCES += $(wildcard */*/*/*.cc)
CXX_SOURCES += $(wildcard */*/*/*/*.cc)
CXX_SOURCES += $(wildcard */*/*/*/*/*.cc)
CXX_SOURCES += $(wildcard */*/*/*/*/*/*.cc)
CXX_SOURCES += $(wildcard */*/*/*/*/*/*/*.cc)
OBJECTS += $(addprefix $(OBJ_DIR)/,$(notdir $(CXX_SOURCES:.cc=.o)))
vpath %.cc $(sort $(dir $(CXX_SOURCES)))

INCLUDES += $(wildcard *.h)
INCLUDES += $(wildcard */*.h)
INCLUDES += $(wildcard */*/*.h)
INCLUDES += $(wildcard */*/*/*.h)
INCLUDES += $(wildcard */*/*/*/*.h)
INCLUDES += $(wildcard */*/*/*/*/*.h)
INCLUDES += $(wildcard */*/*/*/*/*/*.h)
INCLUDES += $(wildcard */*/*/*/*/*/*/*.h)
INC_PATH := $(addprefix -I,$(dir $(filter %.h,$(INCLUDES))))

OPT_FLAGS ?= -O3
C_VERSION ?= -std=gnu17
CXX_VERSION ?= -std=gnu++20

OTHER_FLAGS	+= -ffunction-sections
OTHER_FLAGS	+= -fdata-sections
OTHER_FLAGS	+= -ffreestanding
OTHER_FLAGS	+= -fno-exceptions
OTHER_FLAGS	+= -fno-rtti
OTHER_FLAGS	+= -fno-use-cxa-atexit
OTHER_FLAGS	+= -fpermissive
OTHER_FLAGS	+= -fsingle-precision-constant
OTHER_FLAGS	+= -funroll-loops
OTHER_FLAGS	+= -flto
# OTHER_FLAGS	+= -fmodules-ts
# OTHER_FLAGS	+= -fmodules-header
# OTHER_FLAGS	+= -fcoroutines
# OTHER_FLAGS	+= -fno-non-call-exceptions
# OTHER_FLAGS	+= -fno-unwind-tables
# OTHER_FLAGS	+= -fstack-protector-strong
# OTHER_FLAGS	+= -fno-stack-protector
# OTHER_FLAGS	+= -fstack-usage
# OTHER_FLAGS	+= -fno-common
# OTHER_FLAGS	+= -fno-threadsafe-statics
# OTHER_FLAGS	+= -fmessage-length=0
# OTHER_FLAGS	+= -funsigned-char

WARNING_OPTIONS += -Wall
WARNING_OPTIONS += -Wextra
WARNING_OPTIONS += -Wno-literal-suffix
# WARNING_OPTIONS += -Werror=double-promotion
# WARNING_OPTIONS += -Werror=float-conversion
# WARNING_OPTIONS += -Wunsuffixed-float-constants
# WARNING_OPTIONS += -Wno-volatile

LINK_OPTIONS +=	-nostartfiles
# LINK_OPTIONS +=	-lstdc++ -lc
# LINK_OPTIONS +=	-nodefaultlibs
# LINK_OPTIONS +=	-nostdlib
LINK_OPTIONS +=	--specs=nano.specs
LINK_OPTIONS +=	-Wl,--gc-sections
LINK_OPTIONS +=	-Wl,--print-memory-usage
LINK_OPTIONS +=	-Wl,-Map=$(BIN_DIR)/$(PROJECT).map

# ARFLAGS =
# ASFLAGS =
CFLAGS = $(C_VERSION) $(CORE_FLAGS)
CXXFLAGS = $(CXX_VERSION) $(CORE_FLAGS) $(OTHER_FLAGS) $(WARNING_OPTIONS)
CPPFLAGS = $(INC_PATH) $(addprefix -D,$(CORE_DEFS)) $(OPT_FLAGS)
LDFLAGS = -T $(LD_DIR)/script.ld $(LINK_OPTIONS)
COMPILER_ARGS = $(C_VERSION) $(CXX_VERSION) $(CORE_FLAGS) $(OTHER_FLAGS) $(WARNING_OPTIONS)
