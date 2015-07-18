/*
 * Robot.cpp
 */

#include "Robot.h"
#include "Point.h"

Robot::Robot(char* ip, int port) {
	_player = new PlayerClient(ip,port);
	_positionP = new Position2dProxy(_player);
	_laserP = new LaserProxy(_player);

	_positionP->SetMotorEnable(true);
	//TODO: ????? it was (0,0,0);
	_positionP->SetOdometry(90,76,20);

	//For fixing Player's reading BUG - not delete
	for(int i=0;i<15;i++)
		Read();
}

static Point getObstacleLocation(double xRob, double yRob, double yawRob, double sensorAngle, double distance)
{
	return Point
	(
		xRob + distance * cos(yawRob + sensorAngle),
		yRob + distance * sin(yawRob + sensorAngle)
	);
}

Robot::~Robot() {
	delete _player;
	delete _positionP;
	delete _laserP;
}

void Robot::Read()
{
	_player->Read();
}

void Robot::setSpeed(float xSpeed, float angularSpeed)
{
	_positionP->SetSpeed(xSpeed, angularSpeed);
}

double Robot::getLaserByIndex(int index)
{
	return (*_laserP)[index];
}

bool Robot::isRightFree()
{
	if ((*_laserP)[50] > 0.5)
		return true;
	else
		return false;
}

bool Robot::isLeftFree()
{
		//TODO: fix
			return false;
}

bool Robot::isForwardFree() {
	if ((*_laserP)[332] > 0.5)
		return true;
	else
		return false;
}

Location Robot::getRobotLocation()
{
	return _robotLocation;
}

Location Robot::getDeltaLocation()
{
	double deltaX = _positionP->GetXPos() - _robotLocation.GetPoint().GetX();
	double deltaY = _positionP->GetYPos() - _robotLocation.GetPoint().GetY();
	double deltaYaw = _positionP->GetYaw() - _robotLocation.GetYawPoint();

	return Location(deltaX, deltaY, deltaYaw);
}

void Robot::updateRobotLocation(Location loc)
{
	_robotLocation.SetLocation(loc);
}

float Robot::getLaserDistance(int index)
{
    return _laserP->GetRange(index);
}

bool Robot::checkRange(int nStart, int nEnd)
{
    bool is_dis_Good = true;

    for (int index = nStart; (index <= nEnd) && (is_dis_Good); index++)
    {
//    	is_dis_Good = (this->getLaserDistance(index) > DISTANCE_TOLERANCE);
    	is_dis_Good = (this->getLaserDistance(index) > 0.2);
    }

    return (is_dis_Good);
}

double Robot::getLaserSpec()
{
	return(((_laserP->GetMaxAngle() * 180 / M_PI) + 120 ) / 0.36);
}


