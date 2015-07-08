

CC=g++
CFLAGS=-c -Wall -std=c++11 -O2
LDFLAGS=
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
