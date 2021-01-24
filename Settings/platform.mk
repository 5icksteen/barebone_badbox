ifeq ($(OS),Windows_NT)
	NPROCS := $(shell grep -c ^processor /proc/cpuinfo)
	# RM = del /Q
	# FixPath = $(subst /,\, $1)
	RM := rm -rf
	FixPath := $1
endif

ifeq ($(shell uname),Linux)
    NPROCS := $(shell grep -c ^processor /proc/cpuinfo)
	RM := rm -rf
	FixPath := $1
endif

ifeq ($(shell uname),Darwin)
    NPROCS := $(shell sysctl hw.ncpu | awk '{print $$2}')
	RM := rm -rf
	FixPath := $1
endif

SPACE := $(null) #
COMMA := ,
