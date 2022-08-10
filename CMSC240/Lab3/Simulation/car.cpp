#include "car.h"
#include "track.h"

Car::Car() : m_x(0), m_y(0), m_speed(0), m_dir(NORTH) 
{
}

Car::Car(const int x, const int y) : m_x(x), m_y(y), m_speed(0), m_dir(NORTH) 
{
	if (x < 0) {
		m_x = 0;
	}
	if (y < 0) {
		m_y = 0;
	}
}

Car::Car(const int x, const int y, const int speed) : m_x(x), m_y(y), m_speed(speed), m_dir(NORTH)
{
	if (x < 0) {
		m_x = 0;
	}
	if (y < 0) {
		m_y = 0;
	}
	if (speed < 0)
		m_speed = 0;
	if (speed > 5)
		m_speed = 5;
}

Car::Car(const int x, const int y, const direction dir) : m_x(x), m_y(y), m_speed(0), m_dir(dir)
{
	if (x < 0) {
		m_x = 0;
	}
	if (y < 0) {
		m_y = 0;
	}
}

Car::Car(const int x, const int y, const int speed, const direction dir) : m_x(x), m_y(y), m_speed(speed), m_dir(dir)
{
	if (x < 0) {
		m_x = 0;
	}
	if (y < 0) {
		m_y = 0;
	}
	if (speed < 0)
		m_speed = 0;
	if (speed > 5)
		m_speed = 5;
}

int Car::x() const
{
	return m_x;
}

int Car::y() const
{
	return m_y;
}

int Car::speed() const
{
	return m_speed;
}

direction Car::dir() const
{
	return m_dir;
}

void Car::accelerate()
{
	if (m_speed < 5)
		m_speed++;
}

void Car::decelerate()
{
	if (m_speed > 0)
		m_speed--;
}

void Car::stop()
{
	m_speed = 0;
}

void Car::set_dir(const direction dir)
{
	m_dir = dir;
}

void Car::turn_left()
{
	switch(m_dir) {
		case NORTH:
			m_dir = WEST;
			break;
		case EAST:
			m_dir = NORTH;
			break;
		case SOUTH:
			m_dir = EAST;
			break;
		case WEST:
			m_dir = SOUTH;
			break;
		default:
			break;
	}
}

void Car::turn_right()
{
	switch(m_dir) {
		case NORTH:
			m_dir = EAST;
			break;
		case EAST:
			m_dir = SOUTH;
			break;
		case SOUTH:
			m_dir = WEST;
			break;
		case WEST:
			m_dir = NORTH;
			break;
		default:
			break;
	}
}
//uh oh, the car don't move anymore. rest in peace car, you will be missed
//vroom vroom forever
//:(
