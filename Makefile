# Get the current directory where the Makefile is located
ROOT_DIR := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

# Define directories relative to the ROOT_DIR
SRC_DIR = $(ROOT_DIR)src
BIN_DIR = $(ROOT_DIR)bin
CONFIG_DIR = $(ROOT_DIR)config
DATA_DIR = $(ROOT_DIR)data
DIST_DIR = $(ROOT_DIR)dist

# Define the source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Define the object files
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

# Define the executable
EXECUTABLE = $(DIST_DIR)/Alchemy

# Compiler and flags
CXX = clang++
CXXFLAGS = -Wall -std=c++17

# Default target
all: $(EXECUTABLE)

# Rule to run the executable from dist folder
run: $(EXECUTABLE)
	cd $(DIST_DIR) && $(EXECUTABLE)

# Rule to compile .cpp files to .o files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to link object files into executable
$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $@

# Clean up object files and the executable
clean:
	del /Q $(subst /,\,$(BIN_DIR))\\*.o
	del /Q $(subst /,\,$(DIST_DIR))\\Alchemy.exe

.PHONY: all run clean