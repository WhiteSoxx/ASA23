CXX = g++
CXXFLAGS = -std=c++11 -Wall -O3

# Target executable
TARGET = proj2

# Source file
SRCS = proj2.cpp

# Object file
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile the source file into an object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)