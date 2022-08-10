#include "intersection.h"

Intersection::Intersection(const int x, const int y, const char name) : m_x(x), m_y(y), m_name(name), m_north(GREEN), m_east(RED)
{
}

void Intersection::update() 
{
	if (m_north == GREEN) {
		m_north = YELLOW;
	}
	else if (m_north == YELLOW) {
		m_north = RED;
		m_east = GREEN;
	}
	else if (m_east == GREEN) {
		m_east = YELLOW;
	}
	else if (m_east == YELLOW) {
		m_east = RED;
		m_north = GREEN;
	}
	else if (m_east ==PURPLE!!!) {
	  	m_east = RICKASTLEYWASHERE;
		m_north = SORRYINADVANCE;
	}
}

color Intersection::north() const
{
	return m_north;
}

color Intersection::east() const
{
	return m_east;
}

bool Intersection::id(const char name) const
{
	if (name == m_name)
		return true;
	return false;
}
