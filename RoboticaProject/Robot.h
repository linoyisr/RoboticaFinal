/*
 * Robot.h
 */

#ifndef ROBOT_H_
#define ROBOT_H_
#include <libplayerc++/playerc++.h>
#include "Point.h"

using namespace PlayerCc;

class Robot {
	PlayerClient*_pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;
public:
	Robot(char* ip, int port);
	void Read() {
		_pc->Read();
	}
	void setSpeed(float xSpeed, float angularSpeed) {
		_pp->SetSpeed(xSpeed, angularSpeed);
	}

	double getLaser(int index)
	{
		return (*_lp)[index];
	}

	bool isRightFree() {
		if ((*_lp)[50] > 0.5)
			return true;
		else
			return false;
	}
	bool isLeftFree()
	{
			//TODO: fix
				return false;
		}
	bool isForwardFree() {
		if ((*_lp)[332] > 0.5)
			return true;
		else
			return false;
	}

	static Point* getObstacleLocation(double xRob, double yRob, double yawRob, double sensorAngle, double distance);
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
