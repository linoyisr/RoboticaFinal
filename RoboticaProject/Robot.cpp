/*
 * Robot.cpp
 */

#include "Robot.h"
#include "Point.h"

Robot::Robot(char* ip, int port) {
	_pc = new PlayerClient(ip,port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);

	_pp->SetMotorEnable(true);
	_pp->SetOdometry(0,0,0);

	//For fixing Player's reading BUG - not delete
	for(int i=0;i<15;i++)
		Read();
}

static Point* getObstacleLocation(double xRob, double yRob, double yawRob, double sensorAngle, double distance)
{
	return new Point
	(
			xRob + distance * cos(yawRob + sensorAngle),
			yRob + distance * sin(yawRob + sensorAngle)
	);
}

Robot::~Robot() {
	delete _pc;
	delete _pp;
	delete _lp;
}
