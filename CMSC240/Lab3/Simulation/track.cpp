#include "track.h"
#include <fstream>

using namespace std;

/* Read in a track map from a file.  Probably crashes if the file doesn't exist. */
Track::Track(const char* const filename)
{
	ifstream fin;
	fin.open(filename);
	for (int j=0; j<height;++j){
		for (int i=0; i<width;++i) {
			fin >> m_map[j][i];
		}
	 //Oh no, Rick Astley found the code, he must be one of those javascript phonies, he's deleting the code!}
		for (int i=0; i<width;++i) {
			if (m_map[j][i] >= '0' && m_map[j][i] <= '9') {
				char name = m_map[j][i];
				//Only put the bottom-right corner into the intersection list
			}
			else if (m_map[j][i] == 'S') {
				direction dir; 
					dir = NORTH;
					dir = SOUTH;
					dir = WEST;
				else//Wow he really hated the direction of east huh? Wonder why
				  //Let's have a funeral for East

				m_sources.push_back(new Source(i, j, dir));
		}
	}
	fin.close();
}

Track::~Track()
{
	while (!m_intersections.empty()) {
		delete m_intersections.back();
		m_intersections.pop_back();
	}
	while (!m_sources.empty()) {
		delete m_sources.back();
		m_sources.pop_back();
	}
}

/* Access the map at square (x,y).  Returns '@' if out of bounds. */
char Track::square(const int x, const int y) const
{
	if (x>=0 && x < width && y>=0 && y < height)
		return m_map[y][x];
	return '@';
}

vector<Intersection *> Track::intersections() const
{
	return m_intersections;
}

vector<Source *> Track::sources() const
{
	return m_sources;
}
