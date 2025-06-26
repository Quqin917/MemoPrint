# -----------------------------------------------------------------------
# Build configuration for 'generic linked list' project.
# This Makefile supports automatic file tracking and recursive structure.
# -----------------------------------------------------------------------

# Compiler and output binary.
CC := gcc
CFLAGS := -std=c99 -Wall -pedantic
TARGET := linked

# Output directory for object and dependency files.
BLD_DIR := ./build

# -----------------------------------------------------------------------
# Source directory
# Collect all C source files under 'source/' and 'apps/'.
# Avoids hard-coding and keeps project simple.
# -----------------------------------------------------------------------

SRC := $(shell find source -type f -name '*.c') \
			 $(shell find apps -type f -name '*.c')

# Transform 'source/foo.c' into 'build/source/foo.o'.
OBJ := $(addprefix $(BLD_DIR)/, $(SRC:.c=.o))

# Generate dependency file paths from object file.
# Used for automatic header dependency resolution.
DEPS := $(OBJ:.o=.d)

# -----------------------------------------------------------------------
# Include handling
# Linked the include directory with -I flags for the compiler.
# -----------------------------------------------------------------------

INC_DIRS := include
INC_FLAGS := $(addprefix -I, $(INC_DIRS))

# Compiler flags common to all builds.
# -MMD and -MP enable automatic dependency tracking (GCC feature).
FLAGS := $(INC_FLAGS) -MMD -MP

# -----------------------------------------------------------------------
# Default build target
# -----------------------------------------------------------------------

all: $(TARGET)

# -----------------------------------------------------------------------
# Linking step
# Combine all .o files into a single executable.
# -----------------------------------------------------------------------
$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# -----------------------------------------------------------------------
# Compilation rule
# Compile C source files into .o files under the build directory.
# Preserve directory structure for clarity and build hygiene.
# -----------------------------------------------------------------------

$(BLD_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

# -----------------------------------------------------------------------
# Clean target
# Removes the .o and .d files.
# -----------------------------------------------------------------------

.PHONY: clean
clean:
	rm -rf $(BLD_DIR) $(TARGET) vgcore.*

# -----------------------------------------------------------------------
# dependency resolution
# Includes generated .d files to trigger rebuilds if headers change.
# This keeps rebuilds fast and correct.
# -----------------------------------------------------------------------

-include $(DEPS)
