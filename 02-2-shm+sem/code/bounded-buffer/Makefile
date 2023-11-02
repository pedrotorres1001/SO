CXX = g++
CXXFLAGS = -Wall -Wfatal-errors -ggdb -pthread

TARGETS = bb-unsafe bb-safe ex2

.PHONY:	clean cleanall

all: $(TARGETS)

bb-unsafe: ex2.cpp main.cpp bwdelay.cpp fifo-unsafe.cpp process.cpp utils.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS)

bb-safe: ex2.cpp main.cpp bwdelay.cpp fifo-safe.cpp process.cpp utils.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	rm -f *.o

cleanall:	clean
	rm -f $(TARGETS) 
