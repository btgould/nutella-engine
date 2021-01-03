CXX_FLAGS := -std=c++17 -ggdb
LD_FLAGS := -Wl,-rpath='$$ORIGIN' # executable needs to know where to look for shared lib

# default build configuration
PROJECT_NAME := nutella
PROJECT_VERSION := 0.1.0
PLATFORM := unix
CONFIG := debug

# locations to store output
APP_DIR := sandbox
LIB_DIR := nutella
BIN := bin
OUTPUT_DIR := $(BIN)/$(PLATFORM)/$(CONFIG)
INT_DIR := $(BIN)/intermediates/$(PLATFORM)/$(CONFIG)
OBJ_DIR := $(INT_DIR)/objs
DEP_DIR := $(BIN)/intermediates/deps
CLEAN_DIRS := $(BIN)

# intialize platform specific information
# TODO: prevent trying to build for platforms it can't handle
ifeq ($(PLATFORM), unix)
CXX := g++
LIB_NAME := libnutella.so
APP_NAME := $(PROJECT_NAME)-$(PLATFORM)-$(CONFIG)-$(PROJECT_VERSION)
else ifeq ($(PLATFORM), win64)
CXX := x86_64-w64-mingw32-g++
LIB_NAME := libnutella.dll
APP_NAME := $(PROJECT_NAME)-$(PLATFORM)-$(CONFIG)-$(PROJECT_VERSION).exe
else ifeq ($(PLATFORM), win32)
CXX := i686-w64-mingw32-g++
LIB_NAME := libnutella.dll
APP_NAME := $(PROJECT_NAME)-$(PLATFORM)-$(CONFIG)-$(PROJECT_VERSION).exe
endif

# these are what we actually care about
ENG_LIB := $(OUTPUT_DIR)/$(LIB_NAME)
EXECUTABLE := $(OUTPUT_DIR)/$(APP_NAME)

.DEFAULT_GOAL := all
.PHONY := all run clean INT_DIRS

VPATH := # added to by all included makefiles
INCLUDE := -Ivendor/spdlog/include # added to by all included makefiles
DEPS :=  # added to by all included makefiles

include $(LIB_DIR)/nutella.mk
include $(APP_DIR)/sandbox.mk
include $(DEPS)

all: $(EXECUTABLE) # final goal is executable

$(EXECUTABLE): $(ENG_LIB) # executable needs lib
$(APP_OBJS): $(ENG_LIB)

$(ENG_LIB): | $(OUTPUT_DIR) # output dir must exist, don't care about when it was last updated

run: all
	./$(EXECUTABLE)

# how to generate object files
$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c -fPIC $(INCLUDE) $< -o $@

# how to generate dependency files
$(DEP_DIR)/%.d: %.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) $< -MT $(OBJ_DIR)/$(*F).o -MM -MF $@

clean: 
	rm -r -f $(addsuffix /**, $(CLEAN_DIRS))

$(DEPS): | INT_DIRS

# intermediate dirs to generate
INT_DIRS:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(DEP_DIR)

# output dir to generate
$(OUTPUT_DIR):
	@mkdir -p $(OUTPUT_DIR)
