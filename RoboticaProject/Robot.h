/*
 * Robot.h
 */

#ifndef ROBOT_H_
#define ROBOT_H_
#include <libplayerc++/playerc++.h>
#include "Point.h"
#include "Location.h"

using namespace PlayerCc;

class Robot {
private:
	PlayerClient*_player;
	Position2dProxy* _positionP;
	LaserProxy* _laserP;
	Location* _robotLocation;

public:
	Robot(char* ip, int port);

	void Read();
	void setSpeed(float xSpeed, float angularSpeed);
	double getLaserByIndex(int index);
	bool isRightFree() ;
	bool isLeftFree();
	bool isForwardFree();
	void updateRobotLocation(Location* loc);
	Location* getRobotLocation();
	Location getDeltaLocation();
	static Point* getObstacleLocation(double xRob, double yRob, double yawRob, double sensorAngle, double distance);
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
