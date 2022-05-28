/*
But de ce programme: passer les homologations dynamiques 
en contournant les hexagones au sol puis en les poussant dans
la zone de départ pour marquer des points
*/

#include <math.h>

#include "../include/goal.h"
#include "../include/goalslist.h"
#include "../include/robotstate.h"

extern GoalsList goalsList;
extern RobotState robotState;
extern bool isSideYellow;

void fillGoals() {
	// goalsList.addGoal(new InhibSonar(SONAR_FRONT_RIGHT | SONAR_FRONT_LEFT | SONAR_BACK_RIGHT | SONAR_BACK_LEFT, true));

	// goalsList.addGoal(new Jog(300, 0, 2000));

	// goalsList.addGoal(new Rot(-M_PI / 2));

	// goalsList.addGoal(new Jog(300, 0, 1500));

	// goalsList.addGoal(new Rot(0));

	// goalsList.addGoal(new Jog(300, 0, 1500));

	// goalsList.addGoal(new Rot(M_PI / 2));

	// goalsList.addGoal(new Jog(300, 0, 1500));

	// goalsList.addGoal(new Rot(M_PI));

	// goalsList.addGoal(new Jog(300, 0, 3000));

	if (isSideYellow) {
		float x = 51;
		float y = 508;
		Position startPosition = {x, y, 0};
		robotState.setPosition(startPosition);
		x = 400;
		goalsList.addGoal(new Goto(x, y));
		y = 700; // 200;
		// goalsList.addGoal(new Rot(-M_PI / 2));
		goalsList.addGoal(new Goto(x, y));
		x = 1300;
		// x = 900;
		// goalsList.addGoal(new Rot(0));
		goalsList.addGoal(new Goto(x, y));
		y = 500; // 675;
		// goalsList.addGoal(new Rot(M_PI / 2));
		goalsList.addGoal(new Goto(x, y));
		x = 350; // 400;
		// goalsList.addGoal(new Rot(M_PI));
		goalsList.addGoal(new Goto(x, y));
	}
	else {
		float x = 3000 - 51;
		float y = 508;
		Position startPosition = {x, y, M_PI};
		robotState.setPosition(startPosition);
		x = 3000 - 400;
		goalsList.addGoal(new Goto(x, y));
		y = 200;
		// goalsList.addGoal(new Rot(-M_PI / 2));
		goalsList.addGoal(new Goto(x, y));
		x = 3000 - 1350;
		// goalsList.addGoal(new Rot(M_PI / 2));
		goalsList.addGoal(new Goto(x, y));
		y = 675;
		// goalsList.addGoal(new Rot(-M_PI / 2));
		goalsList.addGoal(new Goto(x, y));
		x = 3000 - 400;
		// goalsList.addGoal(new Rot(-M_PI / 2));
		goalsList.addGoal(new Goto(x, y));
	}
}
