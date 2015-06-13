/*
 * TurnLeft.h
 *
 *  Created on: May 30, 2015
 *      Author: colman
 */

#ifndef TURNLEFT_H_
#define TURNLEFT_H_

#include "Behavior.h"

class TurnLeft: public Behavior {
public:
	TurnLeft(Robot* robot);
		bool startCond()
		{
			if(_robot->isLeftFree())
				return true;
			else
				return false;
		}
		bool stopCond()
		{
			if(_robot->isForwardFree())
						return true;
					else
						return false;
		}

		void action()
		{
			_robot->setSpeed(0.0, 0.3);
		}
		virtual ~TurnLeft();
	};

#endif /* TURNLEFT_H_ */
