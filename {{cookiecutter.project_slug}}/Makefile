DEBUG = false
DEBUG_FLAGS =
ifeq ($(DEBUG), true)
	DEBUG_FLAGS := -ggdb
endif

#uncomment below if shared library target
#CFLAGS += -shared -undefined dynamic_lookup

TARGET_EXEC = {{cookiecutter.project_slug}}
TEST_EXEC = test
BUILD_DIR = build
SRC_DIRS = src

ALL_SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
MAIN_SRCS := $(shell find $(SRC_DIRS) \( -not -name test.c \) -and \( -name *.cpp -or -name *.c -or -name *.s \) )
TEST_SRCS := $(shell find $(SRC_DIRS) \( -not -name {{cookiecutter.project_slug}}.c \) -and \( -name *.cpp -or -name *.c -or -name *.s \) )
ALL_OBJS := $(ALL_SRCS:%=$(BUILD_DIR)/%.o)
MAIN_OBJS := $(MAIN_SRCS:%=$(BUILD_DIR)/%.o)
TEST_OBJS := $(TEST_SRCS:%=$(BUILD_DIR)/%.o)

DEPS := $(ALL_OBJS:.o=.d)

#invert comments in 3 lines below to use a dedicated directory for headers
#HEAD_DIRS ?= ./include
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
#INC_DIRS := $(shell find $(HEAD_DIRS) -type d)

# Flags
CFLAGS = -std=c99 -pedantic -O3 -Wall -Werror -march=native -flto -pipe -fstack-protector-strong --param=ssp-buffer-size=4
CXXFLAGS = -march=native -O3 -flto -pipe -fstack-protector-strong --param=ssp-buffer-size=4
LDFLAGS = -Wl -O3 -flto

INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

# main target
$(BUILD_DIR)/$(TARGET_EXEC): $(MAIN_OBJS)
	$(CC) $(MAIN_OBJS) -o $@ $(LDFLAGS)

# test target
$(BUILD_DIR)/$(TEST_EXEC): $(TEST_OBJS)
	$(CC) $(TEST_OBJS) -o $@ $(LDFLAGS)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEBUG_FLAGS) -c $< -o $@


.PHONY: clean all test run install uninstall

clean:
	$(RM) -r $(BUILD_DIR)

all:	$(BUILD_DIR)/$(TEST_EXEC) $(BUILD_DIR)/$(TARGET_EXEC)

run: $(BUILD_DIR)/$(TARGET_EXEC)
	./build/{{cookiecutter.project_slug}}

test: $(BUILD_DIR)/$(TEST_EXEC)
	./build/test

install: $(BUILD_DIR)/$(TARGET_EXEC)
	cp $(BUILD_DIR)/$(TARGET_EXEC) /usr/local/bin/$(TARGET_EXEC)

uninstall:
	rm /usr/local/bin/$(TARGET_EXEC)

-include $(DEPS)

MKDIR_P ?= mkdir -p

