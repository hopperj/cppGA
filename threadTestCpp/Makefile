

CC=g++
CFLAGS=-c -L/opt/local/lib/ -I/opt/local/include -Wall -std=c++0x -O3 -lboost_thread-mt -lboost_system-mt
LDFLAGS=
SOURCES=testingBoost.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=testingBoost

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *o testingBoost
