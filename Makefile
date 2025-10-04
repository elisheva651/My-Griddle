# Compiler
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -I./

# Get OpenCV flags
OPENCV_CFLAGS := $(shell pkg-config --cflags opencv4)
OPENCV_LDFLAGS := $(shell pkg-config --libs opencv4)

# Convert -I to -isystem for OpenCV headers
OPENCV_CFLAGS := $(patsubst -I%,-isystem %,$(OPENCV_CFLAGS))

CXXFLAGS += $(OPENCV_CFLAGS)
LDFLAGS := $(OPENCV_LDFLAGS)

# Executable name
TARGET := my_game

# Source files
SRCS := $(wildcard *.cpp) $(wildcard input/*.cpp) $(wildcard input/**/*.cpp) \
		$(wildcard game/**/*.cpp) $(wildcard game/*.cpp) \
		$(wildcard img_process/*.cpp) $(wildcard img_process/processors/*.cpp)  

# Object files
OBJS := $(SRCS:.cpp=.o)

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compiling
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Run program
run: $(TARGET)
	./$(TARGET)
