# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -g -std=c++17

# Include directories
INCLUDES = -Iinclude

# Library directories
LDFLAGS = -Llib

# Libraries to link
LIBS = -lglfw3dll

# Source files
SRCS = $(wildcard src/*.cpp) src/glad.c

# Output executable
TARGET = CubeLogic.exe

# Build target
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LDFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

# Clean up build files
clean:
	rm -f $(TARGET)

.PHONY: all clean
