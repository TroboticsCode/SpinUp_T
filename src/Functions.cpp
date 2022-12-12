#include "functions.h"
#include "Aim_vision.h"
#include "DriveFunctionsConfig.h"
#include "vex.h"

#define CENTER_X 316 / 2.0f
#define CENTER_Y 212 / 2.0f
using namespace vex;

void testPID() {
  for (int i = 0; i < 8; i++) {
    moveLinear(12, 100, 10000);
    moveRotate(-90, 90, 10000);
  }
  // moveStop();
  wait(20, msec); // Sleep the task for a short amount of time t
}

void enableFlywheel(void) {
  flywheelFront.spin(forward);
  flywheelBack.spin(forward);
}

void disableFlywheel(void) {
  flywheelFront.stop(coast);
  flywheelBack.stop(coast);
}

void enableIntake(void) { intake.spin(fwd); }

void enableRollerWheel(void) { rollerWheel.spin(forward); }

void disableIntake(void) { intake.stop(coast); }

void fireDisc(void) {
  piston.open();
  wait(500, msec);
  piston.close();
  wait(500, msec);
}

void disableRollerWheel(void) { rollerWheel.stop(); }

void autoAim(int color) {
  Brain.Screen.setCursor(1, 1);
  //Brain.Screen.print("Starting tower center routine");

  if (color == SIGRED)
    Vision1.takeSnapshot(REDSIG);
  else if (color == SIGBLUE)
    Vision1.takeSnapshot(BLUESIG);
  else if (color == SIGGREEN)
    Vision1.takeSnapshot(GREENSIG);

  int objectCenter = Vision1.largestObject.centerX;

  //while ((objectCenter > CENTER_X + 10) || (objectCenter < CENTER_X - 10)) {
    if (color == SIGRED)
      Vision1.takeSnapshot(REDSIG);
    else if (color == SIGBLUE)
      Vision1.takeSnapshot(BLUESIG);
    else if (color == SIGGREEN)
      Vision1.takeSnapshot(GREENSIG);

    objectCenter = Vision1.largestObject.centerX;
    Brain.Screen.setCursor(2, 2);
    Brain.Screen.clearLine();
    Brain.Screen.print(objectCenter);

    if (objectCenter > CENTER_X + 5) {
      Brain.Screen.print("turn right");
      BackRight.spin(directionType::rev, 10, velocityUnits::pct);
      BackLeft.spin(directionType::fwd, 10, velocityUnits::pct);
      FrontRight.spin(directionType::rev, 10, velocityUnits::pct);
      FrontLeft.spin(directionType::fwd, 10, velocityUnits::pct);
    } else if (objectCenter < CENTER_X - 5) {
      Brain.Screen.print("turn left ");
      BackRight.spin(directionType::fwd, 10, velocityUnits::pct);
      BackLeft.spin(directionType::rev, 10, velocityUnits::pct);
      FrontRight.spin(directionType::fwd, 10, velocityUnits::pct);
      FrontLeft.spin(directionType::rev, 10, velocityUnits::pct);
    } else {
      Brain.Screen.print("Dont move");
      Controller1.Screen.clearScreen();
      Controller1.Screen.print("Auto Aim Done");
      BackRight.stop();
      BackLeft.stop();
      FrontRight.stop();
      FrontLeft.stop();
    }
  //}
 /* Brain.Screen.newLine();
  Brain.Screen.print("DONE");
  BackRight.stop(brakeType::brake);
  BackLeft.stop(brakeType::brake);
  FrontRight.stop(brakeType::brake);
  FrontLeft.stop(brakeType::brake);*/
}
