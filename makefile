# Main settings
PROJECT_NAME = elrond-ino
SRC_DIR = src
INCLUDE_DIR = include

# Search for all srcs and includes files
SRC_FILES = $(shell find $(SRC_DIR) -type f \( -name "*.cpp" -or -name "*.c" \) )
INCLUDE_FILES = $(shell find $(INCLUDE_DIR) -type f \( -name "*.hpp" -or -name "*.h" \) )

# Defines src path and source file extensions
VPATH = src: $(SRC_DIR)
vpath %.hpp $(INCLUDE_DIR)
vpath %.h $(INCLUDE_DIR)
vpath %.cpp $(SRC_DIR)
vpath %.c $(SRC_DIR)

.PHONY: all clean clean-all
.DEFAULT_GOAL := all

# *********************************** RULES ************************************
include Arduino.mk

all: arduino-zip
clean: clean-dist
clean-all: clean-dist clean-test

test:
	@$(MAKE) -f tests.mk build/tests/$(notdir $(basename $(t)))
	./build/tests/$(notdir $(basename $(t)))

clean-test:
	@$(MAKE) --no-print-directory -f tests.mk clean-build

clean-test-all:
	@$(MAKE) --no-print-directory -f tests.mk clean-build-all
