/**
 * \file goalslist.h
 * \brief Class which holds a fifo of goals. @see goal.h
**/

#ifndef GOALLIST_H
#define GOALLIST_H

#include <stdint.h>

#include "goal.h"
#include "control.h"
#include "robotstate.h"
#include "parameters.h"

class GoalsList {
public:
	GoalsList() { 
		resetGoals();
	}

	/**
	 * \brief Processes the current goal. If it is reached, processes the next one.
	**/
	void processCurrentGoal();
	//void addGoal(Goal goal);
	void addGoal(Goal* goal);
	void resetGoals();
	void gProcess(Goal const& goal);

private:
	Goal* goalsPtr[MAX_SIMULTANEOUS_GOALS] = {0}; // save goals
	int16_t currentGoalIndex = 0;
	int16_t lastGoalIndex = 0;
};

#endif // GOALLIST_H
