

CC=g++
CFLAGS=-c -Wall -std=c++0x -stdlib=libc++ -O3 -L /opt/local/include/boost/ -L /usr/lib -I /usr/include -lboost_thread -lboost_mutex
LDFLAGS= -stdlib=libc++ -L /opt/local/include/boost/ -L /usr/lib -I /usr/include -lboost_thread -lboost_mutex
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
