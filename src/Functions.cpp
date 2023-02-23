#include "functions.h"
#include "Aim_vision.h"
#include "DriveFunctionsConfig.h"
#include "PID.h"
#include "vex.h"

#define CENTER_X 316 / 2.0f
#define CENTER_Y 212 / 2.0f
using namespace vex;

int16_t autonFlywheelSpeed = 0;

void setAutonFlywheelSpeed(int16_t speed) { autonFlywheelSpeed = speed; }

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
  int motorPower = 15;
  // Brain.Screen.setCursor(1, 1);
  // Brain.Screen.print("Starting tower center routine");

  if (color == SIGRED)
    Vision1.takeSnapshot(REDSIG);
  else if (color == SIGBLUE)
    Vision1.takeSnapshot(BLUESIG);

  int objectCenter = Vision1.largestObject.centerX;

  // while ((objectCenter > CENTER_X + 10) || (objectCenter < CENTER_X - 10)) {
  // if (color == SIGRED)
  //   Vision1.takeSnapshot(REDSIG);
  // else if (color == SIGBLUE)
  //   Vision1.takeSnapshot(BLUESIG);

  // objectCenter = Vision1.largestObject.centerX;
  // Brain.Screen.setCursor(2, 2);
  // Brain.Screen.clearLine();
  // Brain.Screen.print(objectCenter);

  if (objectCenter > CENTER_X + 5) {
    // Brain.Screen.print("turn right");
    BackRight.spin(directionType::rev, motorPower, velocityUnits::pct);
    BackLeft.spin(directionType::fwd, motorPower, velocityUnits::pct);
    FrontRight.spin(directionType::rev, motorPower, velocityUnits::pct);
    FrontLeft.spin(directionType::fwd, motorPower, velocityUnits::pct);
  } else if (objectCenter < CENTER_X - 5) {
    // Brain.Screen.print("turn left ");
    BackRight.spin(directionType::fwd, motorPower, velocityUnits::pct);
    BackLeft.spin(directionType::rev, motorPower, velocityUnits::pct);
    FrontRight.spin(directionType::fwd, motorPower, velocityUnits::pct);
    FrontLeft.spin(directionType::rev, motorPower, velocityUnits::pct);
  } else {
    // Brain.Screen.print("Dont move");
    // Controller1.Screen.clearScreen();
    // Controller1.Screen.print("Auto Aim Done");
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
const float kV = 0.004; //flywheel gain
const float flywheelOffset = 2; //min voltage for movement
int autonFlywheelControl(void) {
  pidInit(&flyWheelPID, 0.0425, 0.0001, 0.02, 15, 15);
  while (true) {
    double motorVoltage = 0.8 * kV * -1.0f * autonFlywheelSpeed;
      motorVoltage += 0.2 * (12 / 100.0f) * (pidCalculate(&flyWheelPID, -1.0f * autonFlywheelSpeed,flywheelBack.velocity(rpm) * 7));

      if(fabs(motorVoltage) < flywheelOffset)
        motorVoltage = -1.0f * flywheelOffset;
      
      //motorVoltage = -1.0f * speedSelector;

      if (motorVoltage > 0)
        motorVoltage = 0;

    printPIDValues(&flyWheelPID);

    flywheelFront.spin(forward, motorVoltage, voltageUnits::volt);
    flywheelBack.spin(forward, motorVoltage, voltageUnits::volt);

    Brain.Screen.clearLine(7);
    Brain.Screen.setCursor(7, 1);
    Brain.Screen.print("Wheel Speed: ");
    Brain.Screen.print(flywheelBack.velocity(rpm) * 7);
    Brain.Screen.print(" RPM");
    vex::task::sleep(flyWheelPID.minDt);
  }
  return 0;
}

  int autonRollerMove(void){
    while(true){
      moveLinear(100, 10, 5000);
      vex::task::sleep(flyWheelPID.minDt);
    }
  return 0;
}