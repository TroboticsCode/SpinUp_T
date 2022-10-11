#include "functions.h"
#include "DriveFunctionsConfig.h"
#include "vex.h"

using namespace vex;

void testPID() {
  for (int i = 0; i < 8; i++) {
    moveLinear(12, 100, 10000);
    moveRotate(-90, 90, 10000);
  }
  // moveStop();
  wait(20, msec); // Sleep the task for a short amount of time t
}

void enableFlywheel(void)
{
  flywheelFront.spin(reverse);
  flywheelBack.spin(reverse);
}

void disableFlywheel(void)
{
  flywheelFront.stop(coast);
  flywheelBack.stop(coast);
}

void enableIntake(void)
{
  intake.spin(fwd);
}

void enableRollerWheel(void)
{
  rollerWheel.spin(reverse);
}

void disableIntake(void)
{
  intake.stop(coast);
}

void fireDisc(void)
{
  piston.open();
  wait(500, msec);
  piston.close();
  wait(500, msec);
}

void disableRollerWheel(void)
{
  rollerWheel.stop();
}