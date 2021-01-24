include Settings/platform.mk
include Settings/toolchain.mk
include Settings/target.mk
include Settings/logo.mk

PROJECT ?= $(notdir $(CURDIR))
BUILD_DIR = .build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
LD_DIR = $(BUILD_DIR)/ld
C_CPP_PROP = .vscode/c_cpp_properties.json
TASKS = .vscode/tasks.json
LAUNCH = .vscode/launch.json

# ifndef FLASH_SIZE
# $(error FLASH_SIZE undefined)
# endif

# ------------------------------------------------------------------------------
# make all
# ------------------------------------------------------------------------------
all: $(BIN_DIR)/$(PROJECT).elf $(BIN_DIR)/$(PROJECT).bin

# ------------------------------------------------------------------------------
# Debug
# ------------------------------------------------------------------------------
debug: OPT_FLAGS = -Og -ggdb3
debug: all
	@echo
	@printf "\033[92mDebug Option Enabled.\n\033[0m"
	@printf "\033[92mDebug interfce [$(DEBUG_TOOL)] is selected\n\033[0m"

# ------------------------------------------------------------------------------
# Make Directories
# ------------------------------------------------------------------------------
$(BUILD_DIR):
	@mkdir $@

$(VSCODE_DIR):
	@mkdir $@

$(OBJ_DIR) $(BIN_DIR) $(LD_DIR): | $(BUILD_DIR)
	@cd $(BUILD_DIR) && mkdir $(lastword $(subst /, ,$@)) && cd ..

# ------------------------------------------------------------------------------
# Compile objects
# ------------------------------------------------------------------------------
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo compiling $<
	@$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: %.cc | $(OBJ_DIR)
	@echo compiling $<
	@$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

# ------------------------------------------------------------------------------
# Create binaries
# ------------------------------------------------------------------------------
$(BIN_DIR)/$(PROJECT).elf: $(OBJECTS) | $(BIN_DIR) $(LD_DIR)/script.ld
	@echo creating $@
	@echo --------------------------------------------------------------------------------
	@$(CXX) $(OBJECTS) $(LDFLAGS) $(CFLAGS) $(CXXFLAGS) -o $@
	@echo --------------------------------------------------------------------------------
	@$(SZ) $@
	@echo --------------------------------------------------------------------------------


$(BIN_DIR)/%.bin: $(BIN_DIR)/%.elf | $(BIN_DIR)
	@echo creating $@
	@$(BIN) $< $@
	@printf "\033[92mBuild completed.\n\033[0m"
	@printf "\033[35m$(DIGILOGTOKYO)\033[0m"

# ------------------------------------------------------------------------------
# Generate linker script
# ------------------------------------------------------------------------------
$(LD_DIR)/script.ld: | $(LD_DIR)
	@echo generating $@
	@$(MAKE) -s -f Settings/ldscript.mk $(CORE_PARAMS) OUTFILE=$(LD_DIR)/script.ld

# ------------------------------------------------------------------------------
# Generate c_cpp_properties.json
# ------------------------------------------------------------------------------
c_cpp: | $(VSCODE_DIR)
	@echo cleaning $(C_CPP_PROP)
	@$(RM) $(C_CPP_PROP)
	@echo generating $@
	@$(MAKE) -s -f Settings/vscode/c_cpp_properties.mk \
	INCLUDES='$(INCLUDES)' CORE_DEFS='$(CORE_DEFS)' COMPILER_ARGS='$(COMPILER_ARGS)' \
	CC=$(CC) C_VERSION='$(C_VERSION)' CXX_VERSION='$(CXX_VERSION)' \
	OUTFILE=$(C_CPP_PROP)

# ------------------------------------------------------------------------------
# Generate tasks.json
# ------------------------------------------------------------------------------
tasks: | $(VSCODE_DIR)
	@echo cleaning $(TASKS)
	@$(RM) $(TASKS)
	@echo generating $@
	@$(MAKE) -s -f Settings/vscode/tasks.mk OUTFILE=$(TASKS)

# ------------------------------------------------------------------------------
# Generate launch.json
# ------------------------------------------------------------------------------
launch: | $(VSCODE_DIR)
	@echo cleaning $(LAUNCH)
	@$(RM) $(LAUNCH)
	@echo generating $@
	@$(MAKE) -s -f Settings/vscode/launch.mk DEBUG_TOOL=$(DEBUG_TOOL) TARGET=$(TARGET) OUTFILE=$(LAUNCH)

# ------------------------------------------------------------------------------
# Clean
# ------------------------------------------------------------------------------
clean:
	@echo cleaning $(BUILD_DIR)
	@$(RM) $(BUILD_DIR)

# ------------------------------------------------------------------------------
# Flash
# ------------------------------------------------------------------------------
ifndef FLASH_TOOL
FLASH_TOOL = $(DEBUG_TOOL)
endif

ifeq ($(FLASH_TOOL), stlink)
define FLASH_CMD
-STM32_Programmer_CLI -c port=SWD reset=HWrst -d $(BIN_DIR)/$(PROJECT).bin $(ROM_START) -s
# openocd -s tcl -f interface/stlink-v2-1.cfg -f target/stm32f4x.cfg -c "program $(BIN_DIR)/$(PROJECT).bin verify reset exit $(ROM_START)"
# pyocd flash -t $(TARGET) --base-address $(ROM_START) $(BIN_DIR)/$(PROJECT).bin
# st-flash --reset --flash=$(ROM_SIZE) write $(BIN_DIR)/$(PROJECT).bin $(ROM_START)
endef
else ifeq ($(FLASH_TOOL), jlink)
define FLASH_CMD
# openocd -f interface/jlink.cfg -c "transport select swd" -f target/stm32f4x.cfg -c "program $(BIN_DIR)/$(PROJECT).bin $(ROM_START) verify reset exit"
# openocd -f interface/jlink.cfg -c "transport select swd" -f target/stm32f4x.cfg -c "program $(BIN_DIR)/$(PROJECT).bin $(ROM_START) verify reset exit"
touch .tmp && echo "r\nloadfile $(BIN_DIR)/$(PROJECT).bin $(ROM_START)\nq" > .tmp
JLinkExe -device $(TARGET) -if SWD -speed 4500 -autoconnect 1 -CommanderScript .tmp
@$(RM) .tmp
endef
else ifeq ($(FLASH_TOOL), dfu)
define FLASH_CMD
dfu-util -a0 -d 0x0483:0xdf11 -s $(ROM_START):leave -D $(BIN_DIR)/$(PROJECT).bin
# dfu-util -a0 -d 0xDEAD:0xBEAF -D $(BIN_DIR)/$(PROJECT).bin -R
# dfu-util -a0 -d 0x0483:0xdf11 -s $(ROM_START) -D $(BIN_DIR)/$(PROJECT).bin -R
endef
endif

flash: | all
	@printf "\033[92mFlash interfce [$(DEBUG_TOOL)] is selected\n\033[0m"
	$(FLASH_CMD)
	@echo $(FLASH_CMD)
	@printf "\033[92m[$(DEBUG_TOOL)] Flash process completed.\n\033[0m"
	@printf "\033[35m$(DIGILOGTOKYO)\033[0m"

# ------------------------------------------------------------------------------
# Information
# ------------------------------------------------------------------------------
info:
	@printf "\033[92mTARGET = $(TARGET)\n\033[0m"
	@printf "\033[92mROM_START = $(ROM_START)\n\033[0m"
	@printf "\033[92mROM_SIZE = $(ROM_SIZE)\n\033[0m"
	@printf "\033[92mRAM_SIZE = $(RAM_SIZE)\n\033[0m"
	@printf "\033[92mOPT_FLAGS = $(OPT_FLAGS)\n\033[0m"
	@printf "\033[92mC_VERSION = $(C_VERSION)\n\033[0m"
	@printf "\033[92mCXX_VERSION = $(CXX_VERSION)\n\033[0m"
	@printf "\033[92mCORE_DEFS = $(CORE_DEFS)\n\033[0m"
	@printf "\033[35m$(DIGILOGTOKYO)\033[0m"

.PHONY: clean flash debug info c_cpp launch task