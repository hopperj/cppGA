

CC=g++
CFLAGS=-c -Wall -O3 -L /usr/lib -I /usr/include -march=native -flto -Ofast -ffast-math -fwhole-program -pthread -std=c++11
#
LDFLAGS=-L /usr/lib -I /usr/include -march=native -Ofast -ffast-math -fwhole-program -pthread -std=c++11
# -flto 
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
