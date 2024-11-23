CXX = g++
CXXFLAGS = -Wall -ggdb -pthread

TARGETS = bb-unsafe bb-safe question2

HEADERS = fifo.h process.h utils.h dbc.h

OBJS = process.o utils.o

.PHONY:	all clean cleanall

all: $(TARGETS)

bb-unsafe: main.o fifo-unsafe.o $(OBJS) $(HEADERS)
	$(CXX) -o $@ main.o fifo-unsafe.o $(OBJS) $(CXXFLAGS)

bb-safe: main.o fifo-sem-safe.o $(OBJS) $(HEADERS)
	$(CXX) -o $@ main.o fifo-sem-safe.o $(OBJS) $(CXXFLAGS)

question2: question2.o $(OBJS) $(HEADERS)
	$(CXX) -o $@ question2.o $(OBJS) $(CXXFLAGS)

question3: question3.o $(OBJS) $(HEADERS)
	$(CXX) -o $@ question3.o $(OBJS) $(CXXFLAGS)

question4: question4.o fifo-sem-safe.o $(OBJS) $(HEADERS)
	$(CXX) -o $@ question4.o fifo-sem-safe.o $(OBJS) $(CXXFLAGS)

clean:
	rm -f *.o

cleanall:	clean
	rm -f $(TARGETS) 
