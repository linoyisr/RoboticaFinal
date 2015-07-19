/*
 * Robot.cpp
 */

#include "Robot.h"
#include "Point.h"
#include "Location.h"

Robot::Robot(char* ip, int port) {
	_player = new PlayerClient(ip,port);
	_positionP = new Position2dProxy(_player);
	_laserP = new LaserProxy(_player);

	_positionP->SetMotorEnable(true);

	_positionP->SetOdometry(9.05,-7.625, 0.34888888);
	_player->Read();
	//until it works!!
	while (_positionP->GetXPos() == 0)
	{
		_positionP->SetOdometry(9.05,-7.625, 20);
	}

	_oldOdometryLocation.SetLocation(Location(Point(9.05,-7.625),20));
	_robotLocation.SetLocation(Location(Point(90,76), 20));
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
	_oldOdometryLocation.SetLocation(Location(Point(_positionP->GetXPos(), _positionP->GetYPos()), _positionP->GetYaw()));
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

Location Robot::getCurrentOdometryLocation()
{
	return Location(_positionP->GetXPos(), -_positionP->GetYPos(), _positionP->GetYaw()*180/3.14);
}

Location Robot::getDeltaLocation()
{
	double deltaX =_oldOdometryLocation.GetPoint().GetX() - _positionP->GetXPos();
	double deltaY = -(_oldOdometryLocation.GetPoint().GetY() - _positionP->GetYPos());
	double deltaYaw = _oldOdometryLocation.GetYawPoint() - _positionP->GetYaw();

	return Location(deltaX, deltaY, deltaYaw);
}

void Robot::updateRobotEstimateLocation(Location loc)
{
	_robotLocation.SetLocation(loc);
}

Location Robot::getEstimateLocation()
{
	//return _robotLocation;
	return getCurrentOdometryLocation();
}

float Robot::getLaserDistance(int index)
{
    return _laserP->GetRange(index);
}

bool Robot::isRangeClear(int start, int end)
{
    bool rangeClear = true;

    for (int index = start; (index <= end) && (rangeClear); index++)
    {
//    	is_dis_Good = (this->getLaserDistance(index) > DISTANCE_TOLERANCE);
    	rangeClear = (this->getLaserDistance(index) > 0.15);
    }

    return (rangeClear);
}

double Robot::getLaserSpec()
{
	return(((_laserP->GetMaxAngle() * 180 / M_PI) + 120 ) / 0.36);
}
