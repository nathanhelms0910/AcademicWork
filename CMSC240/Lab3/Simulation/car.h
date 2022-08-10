#ifndef CAR_H
#define CAR_H
enum direction { NORTH, EAST, SOUTH, WEST };

class Car  {
	protected:
	int m_x;
	int m_y;
	direction m_dir; //North, South, East, or West
	int m_speed;  //In cells per update (from 0 to 5)

	public:
	Car(); //Default position is (0,0)
	Car(const int x, const int y);
	Car(const int x, const int y, const direction dir); //Default speed is 0
	Car(const int x, const int y, const int speed); //Default direction is NORTH
	Car(const int x, const int y, const int speed, const direction dir);
	
	int x() const;
	int y() const;
	int speed() const;
	direction dir() const;

	void accelerate();
	void decelerate();
	void stop();
	
	void set_dir(const direction dir);
	void turn_left();
	void turn_right();

	void move();

};
#endif
