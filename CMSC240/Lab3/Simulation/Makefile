Simulator: car.o track.o intersection.o source.o main.cpp
	g++ -g main.cpp car.o track.o intersection.o source.o -o Simulator

car.o: car.cpp car.h
	g++ -g -c car.cpp

track.o: track.cpp track.h
	g++ -g -c track.cpp

intersection.o: intersection.cpp intersection.h
	g++ -g -c intersection.cpp

source.o: source.cpp source.h
	g++ -g -c source.cpp

.PHONY: clean

clean: 
	rm -f *.o Simulator
