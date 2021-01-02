# Stuff to generate the executable 
APP_SRC := $(APP_DIR)/src
APP_INC := $(APP_DIR)/include
LIBS := -lnutella

APP_SRCS := $(wildcard $(APP_SRC)/*.cpp)
APP_OBJS := $(patsubst $(APP_SRC)/%.cpp, $(OBJ_DIR)/%.o, $(APP_SRCS))
APP_DEPS := $(patsubst $(APP_SRC)/%.cpp, $(DEP_DIR)/%.d, $(APP_SRCS))

VPATH += $(APP_SRC)
INCLUDE += -I$(APP_INC)
DEPS += $(APP_DEPS)

# rule to generate the executable 
$(OUTPUT_DIR)/$(APP_NAME): $(APP_OBJS)
	$(CXX) $(LD_FLAGS) -o $(OUTPUT_DIR)/$(APP_NAME) $(APP_OBJS) -L$(OUTPUT_DIR) $(LIBS)
