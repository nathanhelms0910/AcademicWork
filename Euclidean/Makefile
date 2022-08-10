CFLAGS=-g -Wfatal-errors
all: Euclidean Manhattan Mapgen

Euclidean: minHeap.o interacting.o node.o euclidean.cpp
	g++ ${CFLAGS} euclidean.cpp interacting.o node.o minHeap.o -o Euclidean

Manhattan: minHeap.o interacting.o node.o manhattan.cpp
	g++ ${CFLAGS} manhattan.cpp interacting.o node.o minHeap.o -o Manhattan

Mapgen: make_Map.cpp
	g++ ${CFLAGS} make_Map.cpp -o Mapgen

%.o: %.cpp %.h
	g++ -c -o $@ $< ${CFLAGS}

.PHONY: clean submit

clean:
	rm -f *.o Main

