CXX = g++
CXXFLAGS = -Wall -O3

TAR = pixcii

all: $(TAR)

$(TAR): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TAR) main.cpp

clean:
	rm -f $(TAR)

.PHONY: all clean
