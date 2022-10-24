#include "Autons.h"
#include "DriveFunctionsConfig.h"
#include "Functions.h"
#include "vex.h"

// Put your auton routines in here

void Auton1() {
  setRotGains(.05, 0.00000000001, 0, 20, 10); //update PID gains to tune robot
  setLinGains(200, 0, 0, 20, 10);

  /*
    1. Turn on flywheel
    2. wait for flyuwheel to get to speed ~3200 rpm
    3. fire disc 1
    4. wait for speed
    5. fire disc 2
    6. turn off flywheel
    7. approach near roller
    8. turn roller to color (time to trun tbd)
    9. stretch goal 1: approach far roller
    10. turn roller to color
    11. stretch goal 2: collect more discs
  */

  //moveLinear(float distance, int velocity, uint32_t timeOut);
  // step 1:
  enableFlywheel();
  //step 2:
  waitUntil(flywheelEncoder.velocity(rpm) > 3000);
  //step 3:
  fireDisc();
  //step 4:
  waitUntil(flywheelEncoder.velocity(rpm) > 3000);
  //step 5:
  fireDisc();
  //step 6:
  disableFlywheel();
  //step 7:
  moveRotate(30, 100, 3000);
  moveLinear(-8, 100, 3000);
  moveRotate(-20, 100, 3000);
  moveStop(hold);
  //step 9:
  enableRollerWheel();
  wait(3, seconds);
  //step 10:
  disableRollerWheel();
}

void Auton2() {

}

void skills() {
  enableRollerWheel();
  wait(3, seconds);
  disableRollerWheel();
  moveLinear(29, 80, 30000);
  moveRotate(90, 80, 3000);
  moveLinear(35, 80, 30000);
  enableRollerWheel();
  wait(3, seconds);
  disableRollerWheel();
  moveLinear(30, 80, 3000);
  moveRotate(180, 80, 3000);
  enableIntake();
  moveLinear(20, 80, 3000);
  enableFlywheel();
  waitUntil(flywheelEncoder.velocity(rpm) > 3000);
  fireDisc();enableFlywheel();
  waitUntil(flywheelEncoder.velocity(rpm) > 3000);
  fireDisc();enableFlywheel();
  waitUntil(flywheelEncoder.velocity(rpm) > 3000);
  fireDisc();
}

void Auton3(){ 

}


