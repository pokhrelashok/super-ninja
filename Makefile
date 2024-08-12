# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++20 -Iinclude

# Libraries
LIBS = -lglfw -lGL -lm -lpthread -lXi -lXrandr -lwayland-client -lwayland-egl -lwayland-cursor -ldl

# Source files
SRC = src/main.cpp $(wildcard src/**/*.cpp) src/glad.c src/stb_image.cpp

# Output executable
TARGET = main

# Default target
all: $(TARGET)

# Rule to create the executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LIBS)

# Clean rule to remove the executable
clean:
	rm -f $(TARGET)