//#include "functions.h"
//#include "Aim_vision.h"
#include "Odometry.h"
#include "DriveFunctionsConfig.h"
#include "PID.h"
#include "vex.h"

// define some variables for the file

// this is the x,y,and heading where you put the robot on the field.
double xInitial = 0;
double yInitial = 0;
double tInitial = 0;
// the absolute coordinates of the robot, updated by the odo function.
double xAbs = xInitial;
double yAbs = yInitial;
double tAbs = tInitial;

int odo() {
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Odometry initiated");

  while (true) {
    // sets the intial values to the lastloop variables that we will use to
    // calculate absolute coords
    static double xLastLoop = xInitial;
    static double yLastLoop = yInitial;
    static double tLastLoop = tInitial;

    // relative change per loop values
    double deltaX =
        encoderToInches *
        ((leftTracker.position(degrees) + rightTracker.position(degrees)) / 2);

    double deltaT =
        encoderToInches *
        ((rightTracker.position(degrees) - leftTracker.position(degrees)) /
         (leftTrackerOffset + rightTrackerOffset));

    double deltaY =
        encoderToInches *
        (backTracker.position(degrees) -
         backTrackerOffset *
             (rightTracker.position(degrees) - leftTracker.position(degrees)) /
             (leftTrackerOffset + rightTrackerOffset));

    // Calculate absolute position from the deltas + the lastloop values
    xAbs = xLastLoop + deltaX * cos((M_PI / 180) * tLastLoop) -
           deltaY * sin((M_PI / 180) * tLastLoop);
    yAbs = yLastLoop + deltaX * sin((M_PI / 180) * tLastLoop) -
           deltaY * cos((M_PI / 180) * tLastLoop);
    tAbs = tLastLoop + deltaT;

    // update the lastloop values for the next loop
    xLastLoop = xAbs;
    yLastLoop = yAbs;
    tLastLoop = tAbs;

    printCoords();
    leftTracker.resetRotation();
    rightTracker.resetRotation();
    backTracker.resetRotation();
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
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("xAbs = ");
  Brain.Screen.print(xAbs);
  Brain.Screen.newLine();
  Brain.Screen.print("yAbs = %d", yAbs);
  Brain.Screen.newLine();
  Brain.Screen.print("heading = %d", tAbs);
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
  return tAbs * 57.2958;
}