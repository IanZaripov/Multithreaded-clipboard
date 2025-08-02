CXX := g++
CXXFLAGS := -std=c++14 -Wall -Wextra -pthread


SRCS := main.cpp Buffer.cpp thread_reader.cpp thread_writer.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := buffer.h thread_reader.h thread_writer.h

TARGET := program


all: $(TARGET)


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^


%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<


clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean