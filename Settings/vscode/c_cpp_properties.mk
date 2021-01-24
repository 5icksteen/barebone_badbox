include Settings/platform.mk

define C_CPP_PROP
{
    "configurations": [
        {
            "name": "GCC_ARM",
            "includePath": [
                $(subst $(SPACE),$(COMMA),$(strip $(addprefix "$${workspaceFolder}/,$(addsuffix ",$(dir $(filter %.h,$(INCLUDES)))))))
            ],
            "defines": [
				$(subst $(SPACE),$(COMMA),$(strip $(addprefix ",$(addsuffix ",$(CORE_DEFS)))))
            ],
            "macFrameworkPath": [],
            "compilerPath": "$(CC)",
            "compilerArgs": [
                $(subst $(SPACE),$(COMMA),$(strip $(addprefix ",$(addsuffix ",$(COMPILER_ARGS)))))
            ],
            "cStandard": "$(subst -std=,,$(C_VERSION))",
            "cppStandard": "$(subst -std=,,$(CXX_VERSION))",
            "intelliSenseMode": "gcc-arm"
        }
    ],
    "version": 4
}

endef

.PHONY: all

all: $(OUTFILE)

$(OUTFILE):
	$(file >$@,$(C_CPP_PROP))