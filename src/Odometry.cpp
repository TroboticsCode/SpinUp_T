//#include "functions.h"
//#include "Aim_vision.h"
#include "Odometry.h"
#include "DriveFunctionsConfig.h"
#include "PID.h"
#include "vex.h"
#include <math.h>

// define some variables for the file

// this is the x,y,and heading where you put the robot on the field.
double xInitial = 0;
double yInitial = 0;
double tInitial = 0;
// the absolute coordinates of the robot, updated by the odo function.
double xAbs = xInitial;
double yAbs = yInitial;
double tAbs = tInitial;

double xLastLoop = xInitial;
double yLastLoop = yInitial;
double tLastLoop = tInitial;

double deltaX;
double deltaY;
double deltaT;

double deltaRight;
double deltaLeft;
double deltaBack;

double lastRight = 0;
double lastLeft = 0;
double lastBack = 0;

int odo() {
  //reseting the encoders
  leftTracker.resetRotation();
  backTracker.resetRotation();
  rightTracker.resetRotation();
  


  while (true) {
    // sets the intial values to the lastloop variables that we will use to
    // calculate absolute coords


    // relative change per loop values

    //avoid resetting encoders by tracking new and previous values to find delta
    deltaRight = rightTracker.position(rotationUnits::deg) - lastRight;
    deltaLeft = leftTracker.position(rotationUnits::deg) - lastLeft;
    deltaT = backTracker.position(rotationUnits::deg) - lastBack;

    lastRight = rightTracker.position(rotationUnits::deg);
    lastLeft = leftTracker.position(rotationUnits::deg);
    lastBack = backTracker.position(rotationUnits::deg);

    //now find relative change in position
    deltaX =
        encoderToInches *
        ((deltaRight + deltaLeft) / 2);

    deltaT =
        encoderToInches *
        ((deltaRight - deltaLeft) /
         (leftTrackerOffset + rightTrackerOffset));

    deltaY =
        encoderToInches *
        (
          (deltaRight - deltaLeft) /
          (leftTrackerOffset + rightTrackerOffset));

    // Calculate absolute position from the deltas + the lastloop values
    xAbs += deltaX * cos(tLastLoop) -
           deltaY * sin(tLastLoop);
    yAbs = yLastLoop + deltaX * sin(tLastLoop) -
           deltaY * cos(tLastLoop);
    tAbs = tLastLoop + deltaT;

    // update the lastloop values for the next loop
    xLastLoop = xAbs;
    yLastLoop = yAbs;
    tLastLoop = tAbs;
    printCoords();

    //leftTracker.setRotation(0, rotationUnits::deg);
    //rightTracker.setRotation(0, rotationUnits::deg);
    //backTracker.setRotation(0, rotationUnits::deg);

    vex::task::sleep(100);
  }
  return 0;
}

// this is the function that calculates the distance to target. Returns the
// value as an integer
int distanceToTarget(int xTarget, int yTarget) {

  double dist = sqrt((xTarget - xAbs) * (xTarget - xAbs) +
                     (yTarget - yAbs) * (yTarget - yAbs));
  return dist;
}

// this is the function that calculates angle to target heading. returns value
// as an integer
int angleToTargetHeading(int tTarget) {
  double theta = tTarget - tAbs;
  if (theta >
      180) { // This will optimize the turn to always go the proper direction.
             // Always outputs the shortest turn in proper direction
    theta = theta - 360;
  } else if (theta < -180) {
    theta = theta + 360;
  }
  return theta;
}
// this is not finished yet
int angleToTargetCoord(int xTarget, int yTarget) {
  double theta = atan((xTarget - xAbs) / (yTarget - yAbs));

  return theta;
}

// print the absolute coordinates (x,y,theta) to the brain screen
void printCoords() {
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("xAbs = ");
  Controller1.Screen.print(xAbs);

  // Controller1.Screen.newLine();
  // Controller1.Screen.print("deltaX: ");
  // Controller1.Screen.print(deltaX);

  // Controller1.Screen.newLine();
  // Controller1.Screen.print("C: ");
  // Controller1.Screen.print(encoderToInches);

  Controller1.Screen.newLine();
  Controller1.Screen.print("yAbs = ");
  Controller1.Screen.print(yAbs);

  Controller1.Screen.newLine();
  Controller1.Screen.print("heading = ");
  Controller1.Screen.print(get_tAbs_deg());
}

double get_xAbs(void)
{
  return xAbs;
}
double get_yAbs(void)
{
  return yAbs;
}
double get_tAbs(void)
{
  return tAbs;
}

double get_tAbs_deg(void)
{
  double modVal = 360;
  double accumDeg = tAbs * 57.2958;
  
  return fmod(accumDeg, modVal);
}