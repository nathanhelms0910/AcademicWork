#ifndef SOURCE_H
#define SOURCE_H
#include "car.h"

class Source
{
	protected:
	int m_x;
	int m_y;
	double m_rate;
	direction m_dir;

	public:
	Source(const int x, const int y, const direction dir);

	/* Roughly every 100*"rate" turns, produce a new car and return a pointer to it.  Otherwise, return NULL. */
	Car* createCar() const;
};
#endif
