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
	Location _robotLocation;
	Location _oldOdometryLocation;

public:
	Robot(char* ip, int port);

	void Read();
	void setSpeed(float xSpeed, float angularSpeed);
	double getLaserByIndex(int index);
	bool isRightFree() ;
	bool isLeftFree();
	bool isForwardFree();
	void updateRobotEstimateLocation(Location loc);
	Location getCurrentOdometryLocation();
	Location getOldOdometryLocation();
	Location getDeltaLocation();
	Location getEstimateLocation();
	static Point getObstacleLocation(double xRob, double yRob, double yawRob, double sensorAngle, double distance);
	void SetOldToCurrent();
	virtual ~Robot();

	float getLaserDistance(int index);
	bool isRangeClear(int start, int end);
	double getLaserSpec();
};

#endif /* ROBOT_H_ */
