# Compiler settings
CXX_LINUX = g++
CXX_WINDOWS = x86_64-w64-mingw32-g++

# Compiler flags
CXXFLAGS = -std=c++20 -O2 -I/usr/include

# Source files
SOURCES = src/entity.cpp src/line.cpp src/circle.cpp src/board.cpp src/main.cpp

# Output names
OUTPUT_LINUX = rokkaku_v_0.01
OUTPUT_WINDOWS = rokkaku_v_0.01.exe

# Default target
all: linux windows

# Linux build
linux: $(SOURCES)
	$(CXX_LINUX) $(CXXFLAGS) -o $(OUTPUT_LINUX) $(SOURCES) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Windows build
windows: $(SOURCES)
	$(CXX_WINDOWS) $(CXXFLAGS) -o $(OUTPUT_WINDOWS) $(SOURCES) -lraylib -lopengl32 -lgdi32 -lwinmm -static

# Run the Linux version
run: $(OUTPUT_LINUX)
	./$(OUTPUT_LINUX)

# Clean up
clean:
	rm -f $(OUTPUT_LINUX) $(OUTPUT_WINDOWS)

.PHONY: all linux windows run clean

