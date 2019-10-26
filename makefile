# Main settings
PROJECT_NAME = elrond-ino
SRC_DIR_ROOT = src
INCLUDE_DIR_ROOT = include

# Search for all srcs and includes files
SRC_FILES = $(shell find $(SRC_DIR_ROOT) -type f \( -name "*.cpp" -or -name "*.c" \) )
INCLUDE_FILES = $(shell find $(INCLUDE_DIR_ROOT) -type f \( -name "*.hpp" -or -name "*.h" \) )

# Defines src path and source file extensions
VPATH = src: $(SRC_DIR_ROOT)
vpath %.hpp $(INCLUDE_DIR_ROOT)
vpath %.h $(INCLUDE_DIR_ROOT)
vpath %.cpp $(SRC_DIR_ROOT)
vpath %.c $(SRC_DIR_ROOT)

.PHONY: all clean clean-all
.DEFAULT_GOAL := all

# *********************************** RULES ************************************
include Arduino.mk

# $(PROJECT_NAME): all

all: arduino-zip
clean: clean-dist
clean-all: clean-dist
