# Makefile — сборка программы обработки данных автомобилей
# Кроссплатформенная сборка (Linux/macOS через g++/clang++, Windows через MinGW).

CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2
TARGET   := carsearch
SRCS     := main.cpp file_io.cpp search_by_field.cpp search_core.cpp export_all.cpp
OBJS     := $(SRCS:.cpp=.o)
HEADERS  := constants.h structures.h file_io.h texts.h search_by_field.h search_core.h export_all.h debug.h

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
