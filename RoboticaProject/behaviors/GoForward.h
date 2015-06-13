/*
 * GoForward.h
 */

#ifndef GOFORWARD_H_
#define GOFORWARD_H_

#include "Behavior.h"

class GoForward: public Behavior {
public:
	GoForward(Robot* robot);
		bool startCond()
		{
			if(_robot->isForwardFree())
				return true;
			else
				return false;
		}
		bool stopCond()
		{
			//TODO: Until Obstacle
			return false;
		}

		void action()
		{
			_robot->setSpeed(0.0, 0.3);
		}
		virtual ~GoForward();
	};

#endif /* GOFORWARD_H_ */
