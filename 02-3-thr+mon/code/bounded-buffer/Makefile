CXX = g++
CXXFLAGS = -Wall -Wfatal-errors -ggdb -pthread

TARGETS = bb-unsafe bb-safe ex3

.PHONY:	all clean cleanall

all: $(TARGETS)

bb-unsafe:  ex3.o bwdelay.o fifo-unsafe.o thread.o utils.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

bb-safe: ex3.o bwdelay.o fifo-safe.o thread.o utils.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	rm -f *.o

cleanall:	clean
	rm -f $(TARGETS) 
