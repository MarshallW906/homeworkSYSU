#include <stdio.h>

const int SENSOR_DISTANCE = 40;
/*
  predifined methods:
  1. void lookLeft() and void lookRight()
  function: Let the robot to look at the left or right side.
  2. void lookForward()
  function: let the robot to look forward.
  3. int getDistance()
  function: get a distance from the eye to another.
  object if there is one.
  4. void moveStraight()
  function: go straight for some distance.
  5.int shutDown()
  function: shut down the robot.
*/

int main() {
    lookLeft();
    if (getDistance() < SENSOR_DISTANCE) {
        while (shutDown() != 1) {
            moveStraight();
            while (1) {
                lookLeft();
                if (getDistance() < SENSOR_DISTANCE) {
                    lookForward();
                    if (getDistance() < SENSOR_DISTANCE) {
                        turnRight();
                    }
                    else {
                        break;
                    }
                else {
                    turnLeft();
                }
                }
            }
        }
    }
    else {
        do {
            moveStraight();
            while (1) {
                lookRight();
                if (getDistance() < SENSOR_DISTANCE) {
                    lookForward();
                    if (getDistance() < SENSOR_DISTANCE) {
                        turnLeft();
                    }
                    else {
                        break;
                    }
                else {
                    turnRight();
                }
                }
            }
        } while (shutDown() != 1);
    }
    return 0;
}