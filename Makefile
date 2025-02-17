# Compiler settings
CXX_LINUX = g++
CXX_WINDOWS = x86_64-w64-mingw32-g++

# Raylib paths
RAYLIB_INCLUDE_WINDOWS = /usr/x86_64-w64-mingw32/include/raylib
WINDOWS_LIB = /usr/x86_64-w64-mingw32/lib

# Compiler flags
CXXFLAGS_COMMON = -std=c++20 -O2
CXXFLAGS_LINUX = $(CXXFLAGS_COMMON) -I/usr/include
CXXFLAGS_WINDOWS = $(CXXFLAGS_COMMON) -I$(RAYLIB_INCLUDE_WINDOWS)

# Source files
SOURCES = src/entity.cpp src/line.cpp src/circle.cpp src/board.cpp src/main.cpp

# Output names
OUTPUT_LINUX = rokkaku_v_0.01
OUTPUT_WINDOWS = rokkaku_v_0.01.exe

# Default target
all: linux windows

# Linux build
linux: $(SOURCES)
	$(CXX_LINUX) $(CXXFLAGS_LINUX) -o $(OUTPUT_LINUX) $(SOURCES) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Windows build
windows: $(SOURCES)
	$(CXX_WINDOWS) $(CXXFLAGS_WINDOWS) -o $(OUTPUT_WINDOWS) $(SOURCES) -L$(WINDOWS_LIB) -lraylib -lopengl32 -lgdi32 -lwinmm -lkernel32 -luser32 -lshell32 -lws2_32 -static

# Run the Linux version
run: $(OUTPUT_LINUX)
	./$(OUTPUT_LINUX)

# Clean up
clean:
	rm -f $(OUTPUT_LINUX) $(OUTPUT_WINDOWS)

.PHONY: all linux windows run clean
