include Settings/target.mk

ifeq ($(DEBUG_TOOL), jlink)
SERVER_TYPE := jlink
DEBUG_NAME := J-Link Debug
else ifeq ($(FLASH_TOOL), stlink)
SERVER_TYPE := stutil
DEBUG_NAME := ST-Link Debug
endif

define TASKS
{
    "version": "2.0.0",
    "configurations": [
        {
            "name": "$(DEBUG_NAME)",
            "type": "cortex-debug",
            "request": "launch",
            "cwd": "$${workspaceRoot}",
            "executable": "./.build/bin/$${workspaceRootFolderName}.elf",
            "servertype": "$(SERVER_TYPE)",
            "interface": "swd",
            "device": "$(TARGET)",
            "svdFile": "$(SVD_FILE)",
            "preLaunchTask": "Pre-Launch",
        }
    ]
}

endef

.PHONY: all

all: $(OUTFILE)

$(OUTFILE):
	$(file >$@,$(TASKS))
