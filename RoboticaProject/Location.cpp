/*
 * Location.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#include "Location.h"

Location::Location()
{
}
Location::Location(Point p, double yaw)
{
	point = p;
	yawPoint = yaw;
}

Location::Location(double x ,double y, double yaw)
{
	Point p(x,y);
	point = p;
	yawPoint = yaw;
}

Location::~Location()
{
}

Point Location::GetPoint()
{
	return point;
}

void Location::SetPoint(Point p)
{
	point = p;
}

double Location::GetYawPoint()
{
	return yawPoint;
}

void Location::SetYawPoint(double yaw)
{
	yawPoint = yaw;
}

void Location::SetLocation(Location location)
{
	point.SetX(location.GetPoint().GetX());
	point.SetY(location.GetPoint().GetY());
	yawPoint = location.yawPoint;
}
void Location::Print()
{
	cout << "[" << point.GetX() << "," << point.GetY() <<  "]" << ", " << yawPoint <<endl;

}
