CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pthread

# Исходные файлы (теперь в src/)
SRCS := src/main.cpp src/buffer.cpp src/thread_reader.cpp src/thread_writer.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := src/buffer.h src/thread_reader.h src/thread_writer.h

TARGET := program

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
