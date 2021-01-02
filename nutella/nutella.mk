# Stuff to generate the library
LIB_SRC := $(LIB_DIR)/src
LIB_INC := $(LIB_DIR)/include

LIB_SRCS := $(wildcard $(LIB_SRC)/*.cpp)
LIB_OBJS := $(patsubst $(LIB_SRC)/%.cpp, $(OBJ_DIR)/%.o, $(LIB_SRCS))
LIB_DEPS := $(patsubst $(LIB_SRC)/%.cpp, $(DEP_DIR)/%.d, $(LIB_SRCS))

VPATH += $(LIB_SRC)
INCLUDE += -I$(LIB_INC)
DEPS += $(LIB_DEPS)

# rule to generate the library
$(OUTPUT_DIR)/$(LIB_NAME): $(LIB_OBJS)
	$(CXX) $(LIB_OBJS) -shared -o $@
