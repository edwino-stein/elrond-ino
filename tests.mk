# General settings
SRC_DIR = src
INCLUDE_DIR = include
TESTS_SRC_DIR = tests
BUILD_DIR = build
OBJ_EXTENSION = .o
DEPENDENCE_EXTENSION = .d
RT_INO_LIB = lib-elrond-ino.a

# Compiler and linker settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -MMD
CXXLFLAGS = -std=c++11 -Wall
AR = ar
ARFLAGS = rvs

# Params lists
INCLUDES = $(INCLUDE_DIR)
MACROS = GENERIC_STD_PLATFORM USE_LINKED_NODES WITHOUT_DESTRUCTORS
STATIC_LIBRARIES =
DYNAMIC_LIBRARIES =
RAW_DLIBRARIES =

# Elrond Common library setup
COMMON_DIR = elrond
COMMON_NAME_LIB = lib-elrond-common
COMMON_LIB = build/$(COMMON_NAME_LIB).a

# if has a dev common version in the project, use it
ifeq ($(shell test -L $(COMMON_DIR)-dev -o -d $(COMMON_DIR)-dev; echo $$?), 0)
    COMMON_DIR := $(COMMON_DIR)-dev
endif
INCLUDES += $(COMMON_DIR)/include

VPATH = src: $(SRC_DIR) $(TESTS_SRC_DIR)
vpath %.cpp $(SRC_DIR)
vpath %.c $(SRC_DIR_ROOT)
vpath %.hpp $(INCLUDE_DIR)
vpath %.h $(INCLUDE_DIR_ROOT)
vpath %.cpp $(TESTS_SRC_DIR)

# Elrond Runtime Ino library setup
SRC_FILES = $(shell find $(SRC_DIR) -type f \( -name "*.cpp" -or -name "*.c" \) )
INCLUDE_FILES = $(shell find $(INCLUDE_DIR) -type f \( -name "*.hpp" -or -name "*.h" \) )
OBJS_FILES = $(subst $(SRC_DIR)/,$(BUILD_DIR)/,$(SRC_FILES))
OBJS := $(addsuffix $(OBJ_EXTENSION), $(OBJS_FILES))
DEPS = $(OBJS:$(OBJ_EXTENSION)=$(DEPENDENCE_EXTENSION))

# Add includes and macros to compiler options
CXXFLAGS += $(addprefix -I, $(INCLUDES))
CXXFLAGS += $(addprefix -D, $(MACROS))
RAW_DLIBRARIES += $(addprefix -l, $(DYNAMIC_LIBRARIES))

.PHONY: clean-build clean-build-all

# *********************************** RULES ************************************

# Generic runtime builder
build/tests/%: build/tests/%.cpp.o $(BUILD_DIR)/$(RT_INO_LIB) $(COMMON_DIR)/$(COMMON_LIB)
	@mkdir -p $(@D)
	$(CXX) $(CXXLFLAGS) $^ -o $@ $(RAW_DLIBRARIES)

# Generic test object builder
$(BUILD_DIR)/$(TESTS_SRC_DIR)/%.cpp$(OBJ_EXTENSION): %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/$(RT_INO_LIB): $(OBJS)
	@mkdir -p $(@D)
	@$(AR) $(ARFLAGS) $@ $?

# Objects builder
$(BUILD_DIR)/%$(OBJ_EXTENSION): $(SRC_DIR)/%
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Elrond common library builder
$(COMMON_DIR)/$(COMMON_LIB):
	cd $(COMMON_DIR) && $(MAKE) $(notdir $@) m="USE_LINKED_NODES WITHOUT_DESTRUCTORS"

# Cleaning rules
clean-common:
	cd $(COMMON_DIR) && $(MAKE) clean

clean-build:
	rm -rf $(BUILD_DIR)

clean-build-all: clean-build clean-common

# Include all .d files
-include $(DEPS)
