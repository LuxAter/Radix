
SHELL=/bin/bash
ifndef .VERBOSE
    .SILENT:
endif
ROOT=$(shell pwd)
CXX=clang++
CC=clang
CCIGNORE=
CXXIGNORE=
CCFLAGS=-fPIC -Wall -Wpedantic --static
CXXFLAGS=-std=c++17 -fPIC -Wall -Wpedantic --static
LINK=-llua5.3
SOURCE=src
INCLUDE_DIR=include
INCLUDE=
BUILD=build
COMMON_INCLUDE=-I$(ROOT)/$(INCLUDE_DIR) $(INCLUDE)

SCAN_COLOR=\033[1;35m
BUILD_COLOR=\033[32m
CLEAN_COLOR=\033[1;33m
LINK_COLOR=\033[1;32m
INSTALL_COLOR=\033[1;36m
CMD_COLOR=\033[1;34m
HELP_COLOR=\033[1;34m

define scan_target
printf "%b%s%b\n" "$(SCAN_COLOR)" "Scaning dependencies for target $(1)" "\033[0m"
endef
define complete_target
printf "%s\n" "Built target $(1)"
endef
define clean_target
printf "%b%s%b\n" "$(CLEAN_COLOR)" "Cleaning target $(1)" "\033[0m"
endef
define install_target
printf "%b%s%b\n" "$(INSTALL_COLOR)" "Installing target $(1)" "\033[0m"
endef
define uninstall_target
printf "%b%s%b\n" "$(INSTALL_COLOR)" "Unnstalling target $(1)" "\033[0m"
endef
define print_build_c
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(BUILD_COLOR)" "Building C object $$str" "\033[0m"
endef
define print_build_cpp
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(BUILD_COLOR)" "Building C++ object $$str" "\033[0m"
endef
define print_link_lib
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(LINK_COLOR)" "Linking static library $$str" "\033[0m"
endef
define print_link_exe
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(LINK_COLOR)" "Linking executable $$str" "\033[0m"
endef
define print_run_cmd
printf "%b%s%b\n" "$(CMD_COLOR)" "Running '$(1)'" "\033[0m"
endef
define help
printf "%b%*s%b: %s\n" "$(HELP_COLOR)" 20 "$(1)" "\033[0m" "$(2)"
endef

all: build-radix
clean: clean-radix
install: install-radix
uninstall: uninstall-radix

# RADIX {{{

RADIX=radix.out
RADIX_FILES=src/main.cpp
RADIX_OBJS=$(RADIX_FILES:%=$(ROOT)/$(BUILD)/%.o)
-include $(RADIX_OBJS:.o=.d)

build-radix: build-libradix.a pre-radix $(RADIX)
	$(call complete_target,$(shell basename $(RADIX)))

clean-radix:
	$(call clean_target,$(shell basename $(RADIX)))
	if [ -e "$(RADIX)" ]; then rm $(RADIX); fi

pre-radix:
	$(call scan_target,$(shell basename $(RADIX)))

$(RADIX): $(RADIX_OBJS) FORCE
	$(call print_link_exe,$(shell basename $(RADIX)))
	$(CXX) $(RADIX_OBJS) $(LIBRADIX.A) $(LINK) $(COMMON_INCLUDE) -o $(RADIX)

install-radix: build-radix
	$(call install_target,$(shell basename $(RADIX)))
	mkdir -p $(INSTALL_PATH)/bin/
	cp $(RADIX) $(INSTALL_PATH)/bin

uninstall-radix:
	$(call uninstall_target,$(shell basename $(RADIX)))
	if [ -e "$(INSTALL_PATH)/bin/$(shell basename $(RADIX))" ]; then rm $(INSTALL_PATH)/bin/$(shell basename $(RADIX)); fi

# }}}
# LIBRADIX.A {{{

LIBRADIX.A=$(BUILD)/libradix.a
LIBRADIX.A_FILES=$(filter-out src/main.cpp, $(shell find "$(SOURCE)/" -name "*.cpp"))
LIBRADIX.A_OBJS=$(LIBRADIX.A_FILES:%=$(ROOT)/$(BUILD)/%.o)
-include $(LIBRADIX.A_OBJS:.o=.d)

build-libradix.a:  pre-libradix.a $(LIBRADIX.A)
	$(call complete_target,$(shell basename $(LIBRADIX.A)))

clean-libradix.a: 
	$(call clean_target,$(shell basename $(LIBRADIX.A)))
	if [ -e "$(LIBRADIX.A)" ]; then rm $(LIBRADIX.A); fi

pre-libradix.a:
	$(call scan_target,$(shell basename $(LIBRADIX.A)))

$(LIBRADIX.A): $(LIBRADIX.A_OBJS) FORCE
	$(call print_link_lib,$(shell basename $(LIBRADIX.A)))
	ar rcs $@ $(LIBRADIX.A_OBJS)
	

install-libradix.a: build-libradix.a
	$(call install_target,$(shell basename $(LIBRADIX.A)))
	mkdir -p $(INSTALL_PATH)/lib/
	mkdir -p $(INSTALL_PATH)/include/$(NAME)/
	cp $(LIBRADIX.A) $(INSTALL_PATH)/lib
	if [ ! -z "$(INCLUDE_DIR)" ]; then cp -R $(INCLUDE_DIR)/ $(INSTALL_PATH)/include/$(NAME)/; fi
	if [ ! -z "$(shell find $(SOURCE_DIR) -name "*.h")" ]; then cd $(SOURCE_DIR) && cp --parents $(sehll cd $(SOURCE_DIR) && find . -name "*.h") $(INSTALL_PATH)/include/$(NAME); fi
	if [ ! -z "$(shell find $(SOURCE_DIR) -name "*.hpp")" ]; then cd $(SOURCE_DIR) && cp --parents $(sehll cd $(SOURCE_DIR) && find . -name "*.hpp") $(INSTALL_PATH)/include/$(NAME); fi

uninstall-libradix.a:
	$(call uninstall_target,$(shell basename $(LIBRADIX.A)))
	if [ ! -e "$(INSTALL_PATH)/lib/$(shell basename $(LIBRADIX.A))" ]; then rm $(INSTALL_PATH)/lib/$(shell basename $(LIBRADIX.A)); fi
	if [ ! -e "$(INSTALL_PATH)/include/$(NAME)" ]; then rm $(INSTALL_PATH)/include/$(NAME) -r; fi

# }}}

$(ROOT)/$(BUILD)/%.cpp.o: %.cpp
	mkdir -p $(@D)
	$(call print_build_cpp,$@)
	$(CXX) $(CXXFLAGS) -MMD -c $(COMMON_INCLUDE) $< -o $@

$(ROOT)/$(BUILD)/%.c.o: %.c
	mkdir -p $(@D)
	$(call print_build_c,$@)
	$(CC) $(CCFLAGS) -MMD -c $(COMMON_INCLUDE) $< -o $@

FORCE:
