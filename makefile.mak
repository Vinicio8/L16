CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lCLI11 -lbarkeep

TARGET = retail_analyzer
SRCS = main.cpp analytics.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
