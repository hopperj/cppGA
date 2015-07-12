

CC=g++
CFLAGS=-c -Wall -std=c++0x -O3 -pthread
LDFLAGS=-pthread
SOURCES=NeuralNetwork.cpp TTT.cpp GA.cpp Player.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=GA

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *o GA
