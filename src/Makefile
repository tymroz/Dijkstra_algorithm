CPP = g++
CPPFLAGS = -Wall -g
OBJECTS = main.o dijkstra.o

all: dijkstra

dijkstra: $(OBJECTS)
    $(CPP) $(CPPFLAGS) $(OBJECTS) -o dijkstra

main.o: main.cpp dijkstra.h
    $(CPP) $(CPPFLAGS) -c main.cpp

dijkstra.o: dijkstra.cpp dijkstra.h
    $(CPP) $(CPPFLAGS) -c dijkstra.cpp

clean:
    rm -f *.o dijkstra