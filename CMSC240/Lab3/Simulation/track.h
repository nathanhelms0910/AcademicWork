#ifndef TRACK_H
#define TRACK_H

#include "intersection.h"
#include "source.h"
#include <vector>

using namespace std;

class Track {
	public:
	const static int height=30;
	const static int width=30;

	protected:
	char m_map[height][width];
	vector<Intersection *> m_intersections;
	vector<Source *> m_sources;

	public:
	Track(const char* const filename);
	~Track();
	char square(const int x, const int y) const;
	vector<Intersection *> intersections() const;
	vector<Source *> sources() const;

};
#endif
