#ifndef INTERSECTION_H
#define INTERSECTION_H
enum color {RED, YELLOW, GREEN};

class Intersection
{
	protected:
	int m_x;
	int m_y;
	char m_name;

	/* Color of the north/south lights */
	color m_north;

	/* Color of the east/west lights */
	color m_east;	

	public:
	//Initially North/South is green and East/West is red.
	Intersection(const int x, const int y, const char name);

	void update();
	color north() const;
	color east() const;
	bool id(const char name) const;
};

#endif
