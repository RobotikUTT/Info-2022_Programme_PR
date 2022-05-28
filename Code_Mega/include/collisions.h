/**
 * \file collisions.h
 * \brief Class which holds a maximal speed value based on the proximity of obstacles.
**/

#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "pins.h"
#include "parameters.h"
#include "robotstate.h"
#include "nano.h"

//typedef struct {float ahead, behind;} Obstacle;

class Collisions  {
public:
	/**
	 * Updates the maximal speed based on the distance to the nearest obstacle.
	**/
	void update();
	float getMaxSpeed() { return maxSpeed; }

private:
	uint8_t activeCounts[4] = {0};
	float maxSpeed = MAX_SPEED; // mm/s
};

#endif // COLLISIONS_H
