/**
 * \file calibatrion.h
 * \brief Manual controls of the six Servos through the Serial Monitor.
**/

#include <math.h>
#include "../include/goal.h"
#include "../include/goalslist.h"
#include "../include/robotstate.h"

extern GoalsList goalsList;
extern RobotState robotState;


class Blank : public Goal {
public:
    Blank() : Goal() {}

    void process() {}
};


void fillGoals() {
    // goalsList.addGoal(new InhibSonar(SONAR_FRONT_RIGHT | SONAR_FRONT_LEFT | SONAR_BACK_RIGHT | SONAR_BACK_LEFT, true));
    // goalsList.addGoal(new Blank());
    // Jog(linearSpeed, angularSpeed, duration) mm/s, mm/s, ms
    // goalsList.addGoal(new Jog(300, 0, 1200));
    // goalsList.addGoal(new Goto(200, 0));
    // goalsList.addGoal(new Rot(-THETA_ERROR_TOLERANCE, COUNTER_CLOCKWISE));
    // return;

    for (uint8_t i=0; i<6; i++) {

    goalsList.addGoal(new Goto(600, 0));
    goalsList.addGoal(new Delay(2000));

    goalsList.addGoal(new Rot(M_PI));
    goalsList.addGoal(new Delay(2000));

    goalsList.addGoal(new Goto(0, 0));
    goalsList.addGoal(new Delay(2000));

    goalsList.addGoal(new Rot(0));
    goalsList.addGoal(new Delay(2000));

    }

    // goalsList.addGoal(new Goto(0, 0, FORWARD));
    // goalsList.addGoal(new Delay(2000));

    // goalsList.addGoal(new Rot(M_PI, CLOCKWISE));
    // goalsList.addGoal(new Delay(2000));

    // goalsList.addGoal(new Rot(0));
    // goalsList.addGoal(new Delay(2000));

    // goalsList.addGoal(new Goto(600, 0));
    // goalsList.addGoal(new Delay(2000));

    // goalsList.addGoal(new Goto(0, 0));
    // goalsList.addGoal(new Delay(2000));

    // goalsList.addGoal(new Goto(400, 0));
    // goalsList.addGoal(new Delay(2000));

    // goalsList.addGoal(new Goto(0, 0));
    // goalsList.addGoal(new Delay(2000));

    // goalsList.addGoal(new Goto(200, 0));
    // goalsList.addGoal(new Delay(2000));

    // goalsList.addGoal(new Goto(0, 0));
    // goalsList.addGoal(new Delay(2000));

    // goalsList.addGoal(new Goto(100, 0));
    // goalsList.addGoal(new Delay(2000));

    // goalsList.addGoal(new Goto(0, 0));
    // goalsList.addGoal(new Delay(2000));

    // goalsList.addGoal(new Rot(M_PI / 2));
    // goalsList.addGoal(new Delay(2000));

    // goalsList.addGoal(new Rot(0));
    // goalsList.addGoal(new Delay(2000));

    // goalsList.addGoal(new Rot(M_PI / 4));
    // goalsList.addGoal(new Delay(2000));

    // goalsList.addGoal(new Rot(-M_PI / 2));
    // goalsList.addGoal(new Delay(2000));

    // goalsList.addGoal(new Rot(0, CLOCKWISE));
    // goalsList.addGoal(new Delay(2000));

    // goalsList.addGoal(new Rot(-0.0001, COUNTER_CLOCKWISE));
    // goalsList.addGoal(new Delay(2000));

    // goalsList.addGoal(new Goto(200, 200));
    // goalsList.addGoal(new Rot(1 * M_PI));
    // goalsList.addGoal(new Blank());
}
