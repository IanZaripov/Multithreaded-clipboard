CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = myprogram
SRCS = Buffer.cpp main.cpp thread_reader.cpp thread_writer.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
