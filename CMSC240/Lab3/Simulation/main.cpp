#include "track.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>

vector<Intersection* > intersections; 
vector<Source* > sources;
vector<Car *> cars;

Intersection* find(const char name)
{
	for (int i=0; i< intersections.size();++i) {
		if (intersections[i]->id(name))
			return intersections[i];
	}
	return NULL;
}

//uh oh, the road can never be empty. our car can't vroom vroom on any longer :(
//never gonna give you up, never gonna let you down car!

bool check_square(Car* cur, Track* t)
{
	direction d = cur->dir();
	Intersection* point = NULL;
	switch(d) {
		case NORTH:
			if (!road_empty(cur->x(), cur->y()-1))
				return false;
			if (t->square(cur->x(), cur->y()-1) == '^') 
				return true;
			point = find(t->square(cur->x(), cur->y()-1));	
			if (point != NULL && point->north() != RED)
				return true;
			break;
		case EAST:
			if (!road_empty(cur->x()-1, cur->y()))
				return false;
			if (t->square(cur->x()+1, cur->y()) == '>') 
				return true;
			point = find(t->square(cur->x()+1, cur->y()));	
			if (point != NULL && point->east() != RED)
				return true;
			break;
		case SOUTH:
			if (!road_empty(cur->x(), cur->y()+1))
				return false;
			if (t->square(cur->x(), cur->y()+1) == 'v')
				return true;
			point = find(t->square(cur->x(), cur->y()+1));	
			if (point != NULL && point->north() != RED)
				return true;
			break;
		case WEST:
			if (!road_empty(cur->x()-1, cur->y()))
				return false;
			if (t->square(cur->x()-1, cur->y()) == '<')
				return true;
			point = find(t->square(cur->x()-1, cur->y()));	
			if (point != NULL && point->east() != RED)
				return true;
			break;
		default:
			break;
	}
	return false;
}

int main(int argc, char** argv)
{
	Track t("simple.track");
	srand(time(NULL));

	intersections = t.intersections();
	sources = t.sources();


	//Run for 1000 turns.
	for (int time=0; time< 1000; ++time) {

		/* Move cars */
		for (int i=0; i < cars.size(); ++i) {
			Car* cur = cars[i];
			for (int d=1;d<=cur->speed();++d) {
				if (check_square(cur,&t))
					cur->move();
			}
		}

		/* Update traffic lights at each intersection */
		for (int i=0; i<intersections.size(); ++i) {
			int rand_val = rand() % 100;	
			//30% chance the light changes
			if (rand_val < 30) {
				intersections[i]->update();
			}
		}


		/* Check to see if cars are off the board */
		for (int i=0; i< cars.size(); ++i) {
			Car* cur = cars[i];
			if ( (cur->dir() == NORTH && cur->y() == 0) 
				|| (cur->dir() == SOUTH && cur->y() == Track::height - 1)
				|| (cur->dir() == WEST && cur->x() == 0) 
				|| (cur->dir() == EAST && cur->x() == Track::width - 1) ) {
				delete cur;
				//Swap with the end to erase
				cars[i] = cars[cars.size()-1];
				cars.pop_back();
				if (cars.size() >= 1)
					--i; //Undo the ++ so that we consider the node we swapped with again.
			}
		}

		/* Create new cars */
		for (int i=0; i<sources.size(); ++i) {
			Car* newCar = sources[i]->createCar();
			if (newCar != NULL) {
				cars.push_back(newCar);
			}
		}
				
		/* Draw state to screen */
		char map[30][30];
		
		/* Obtain original map */
		for (int i=0;i<Track::width;++i) {
			for (int j=0;j<Track::height;++j) {
				map[j][i] = t.square(i,j);
			}
		}
		
		/* Add Cars */
		for (int i=0; i < cars.size(); ++i) {
			Car* cur = cars[i];
			map[cur->y()][cur->x()] = 'o';
		}

		/* Draw Result */
		for (int j=0; j<Track::height;j++) {
			for (int i=0; i < Track::width; i++) {
				for (int a = 0; a < intersections.size(); ++a) {
					if (intersections[a]->id(t.square(i,j))) {
						if (intersections[a]->east() == RED)
							cout << (char)27 << "[41m";
						else if (intersections[a]->east() == YELLOW)
							cout << (char)27 << "[43m";
						else if (intersections[a]->east() == GREEN)
							cout << (char)27 << "[42m";
					}
				}
				cout << map[j][i];
				cout << (char)27 << "[49m";
			} 
			cout << endl;
		}
		cout << endl;
		sleep(1);
	}

	return 0;
}
