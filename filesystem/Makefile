CC=g++
CFLAGS=-c -std=c++11 -g
LDFLAGS=
SOURCES=filesys.cpp main.cpp operations.cpp
LIBS=
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lab4

all: $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(LIBS) $^ -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:	
	rm -f *.o $(EXECUTABLE) 
	touch *

handin: clean
	handin cmsc442 $(EXECUTABLE) ../$(EXECUTABLE)

