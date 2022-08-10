#include "source.h"
#include <cstdlib>

Source::Source(const int x, const int y, const direction dir) : m_x(x), m_y(y), m_rate(0.1), m_dir(dir)
{
}

Car* Source::createCar() const
{
	int int_rate = m_rate*100;
	int rand_val = rand() % 100 + 1;
	if (rand_val < int_rate) {
		return new Car(m_x, m_y, 1, m_dir);
	}
	return NULL;
}
