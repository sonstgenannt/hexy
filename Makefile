VERSION = 0.05a

CXX_LINUX = g++
CXX_WINDOWS = x86_64-w64-mingw32-g++

# Raylib paths
RAYLIB_INCLUDE = /include/
WINDOWS_LIB = /usr/x86_64-w64-mingw32/lib

# Compiler flags
CXXFLAGS_COMMON = -std=c++20 -Os -flto
CXXFLAGS_LINUX = -fsanitize=address $(CXXFLAGS_COMMON) -I$(RAYLIB_INCLUDE)
CXXFLAGS_WINDOWS = $(CXXFLAGS_COMMON) -I$(RAYLIB_INCLUDE) -static

# Source files
SOURCES = src/rect_button.cpp src/entity.cpp src/line.cpp src/circle.cpp src/board.cpp src/ai.cpp src/data_manager.cpp src/main.cpp

# Output names
OUTPUT_LINUX = takaku_v$(VERSION)
OUTPUT_WINDOWS = takaku_v$(VERSION).exe

# Default target
all: linux windows

# Linux build
linux: $(SOURCES)
	$(CXX_LINUX) $(CXXFLAGS_LINUX) -o $(OUTPUT_LINUX) $(SOURCES) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Windows build
windows: $(SOURCES)
	$(CXX_WINDOWS) $(CXXFLAGS_WINDOWS) -o $(OUTPUT_WINDOWS) $(SOURCES) -L$(WINDOWS_LIB) -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows -lkernel32 -luser32 -lshell32 -lws2_32 -s

# Run the Linux version
run: $(OUTPUT_LINUX)
	./$(OUTPUT_LINUX)

# Clean up
clean:
	rm -f $(OUTPUT_LINUX) $(OUTPUT_WINDOWS)

.PHONY: all linux windows run clean
