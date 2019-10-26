#Arduino general settings
LIBRARY_NAME = $(PROJECT_NAME)
DIST_DIR_ROOT = dist
LIBRARY_DIST_DIR = $(DIST_DIR_ROOT)/$(LIBRARY_NAME)
LIBRARY_SRC_DIR = $(LIBRARY_DIST_DIR)/src
ARDUINO_LIBS_INSTALL_PATH = ~/Arduino/libraries/

# Define all files to the library
LIBRARY_EXTRA_FILES = arduino-meta/*
LIBRARY_INCLUDE_FILES = $(subst $(INCLUDE_DIR_ROOT)/,$(LIBRARY_SRC_DIR)/,$(INCLUDE_FILES))
LIBRARY_SRC_FILES = $(subst $(SRC_DIR_ROOT)/,$(LIBRARY_SRC_DIR)/,$(SRC_FILES))

# Elrond Common library setup
COMMON_DIR = elrond
# if has a dev common version in the project, use it
ifeq ($(shell test -L $(COMMON_DIR)-dev -o -d $(COMMON_DIR)-dev; echo $$?), 0)
    COMMON_DIR := $(COMMON_DIR)-dev
endif

COMMON_DIST_SRC_DIR = $(COMMON_DIR)/dist/elrond-common/src

# ************************** BUILD RULES **************************

.PHONY: arduino-zip arduino-install arduino-uninstall arduino-dist clean-dist arduino-dist-common

# Library packer
arduino-zip: $(LIBRARY_DIST_DIR).zip
$(LIBRARY_DIST_DIR).zip: arduino-dist
	cd $(DIST_DIR_ROOT) && zip $(LIBRARY_NAME).zip -r $(LIBRARY_NAME)/

# Installer in the arduino IDE
arduino-install: arduino-uninstall arduino-dist
	cp -r $(LIBRARY_DIST_DIR) $(ARDUINO_LIBS_INSTALL_PATH)

# Unistaller in the arduino IDE
arduino-uninstall:
	rm -rf $(ARDUINO_LIBS_INSTALL_PATH)$(LIBRARY_NAME)

# Prepare file structure like arduino IDE library specification (1.5.x)
arduino-dist: clean-dist $(LIBRARY_INCLUDE_FILES) $(LIBRARY_SRC_FILES) arduino-dist-common
	cp -r $(LIBRARY_EXTRA_FILES) $(LIBRARY_DIST_DIR)
	cp -r $(COMMON_DIST_SRC_DIR) $(LIBRARY_DIST_DIR)

arduino-dist-common:
	cd $(COMMON_DIR) && $(MAKE) arduino-dist

# Copy headers
$(LIBRARY_SRC_DIR)/%.hpp: $(INCLUDE_DIR_ROOT)/%.hpp
	@mkdir -p $(@D)
	cp $< $@

$(LIBRARY_SRC_DIR)/%.h: $(INCLUDE_DIR_ROOT)/%.h
	@mkdir -p $(@D)
	cp $< $@

# Copy src
$(LIBRARY_SRC_DIR)/%.cpp: $(SRC_DIR_ROOT)/%.cpp
	@mkdir -p $(@D)
	cp $< $@

$(LIBRARY_SRC_DIR)/%.c: $(SRC_DIR_ROOT)/%.c
	@mkdir -p $(@D)
	cp $< $@

# Cleaner
clean-dist:
	rm -Rf $(DIST_DIR_ROOT)
