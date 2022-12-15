#include "Autons.h"
#include "DriveFunctionsConfig.h"
#include "Functions.h"
#include "vex.h"

// Put your auton routines in here

void Auton1() {
  autoAimColor = SIGRED;
  
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
  flywheelBack.setVelocity(-75, pct);
  flywheelFront.setVelocity(-75, pct);
  
  enableFlywheel();
  //step 2:
  //waitUntil(flywheelEncoder.velocity(rpm) > 2500);
  
  wait(2000, msec);
  //step 3:
  fireDisc();
  //step 4:
  flywheelBack.setVelocity(-78, pct);
  flywheelFront.setVelocity(-78, pct);
  //waitUntil(flywheelEncoder.velocity(rpm) > 2500);
  wait(2000,msec);
  //step 5:
  fireDisc();
  //step 6:
  disableFlywheel();

  //step 7: align with color roller
  moveRotate(5, 100, 1000);
  moveLinear(-10, 100, 1000);
  //40, -5; 45, -20
  //moveRotate(-35, 100, 1000);
  //moveLinear(-3, 100, 1000);
 //moveStop(hold);

  //step 8: turn roller
  enableRollerWheel();
  uint32_t currTime = Brain.Timer.system();
  while((Brain.Timer.system() - currTime < 500));
  disableRollerWheel();

  //step 9:

  //ropeLauncher.open();
}

void Auton2() {
  autoAimColor = SIGRED;


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
  flywheelBack.setVelocity(-63, pct);
  flywheelFront.setVelocity(-63, pct);
  
  enableFlywheel();
  //step 2:
  //waitUntil(flywheelEncoder.velocity(rpm) > 2500);
  
  wait(2000, msec);
  //step 3:
  fireDisc();
  //step 4:
  flywheelBack.setVelocity(-65, pct);
  flywheelFront.setVelocity(-65, pct);
  //waitUntil(flywheelEncoder.velocity(rpm) > 2500);
  wait(2000,msec);
  //step 5:
  fireDisc();
  //step 6:
  disableFlywheel();

  //step 7: align with color roller
  //moveRotate(20, 100, 1000);
  moveLinear(-10, 100, 1000);
  //40, -5; 45, -20
  //moveRotate(-35, 100, 1000);
  //moveLinear(-3, 100, 1000);
 //moveStop(hold);

  //step 8: turn roller
  enableRollerWheel();
  wait(1000, msec);
  disableRollerWheel();

  //step 9:

  ropeLauncher.open();
}

void skills() {
  setRotGains(.05, 0.00000000001, 0, 20, 10); //update PID gains to tune robot
  setLinGains(200, 0, 0, 20, 10);

  enableRollerWheel();
  uint32_t currTime = Brain.Timer.system();
  while((Brain.Timer.system() - currTime < 3000));
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
  //waitUntil(flywheelEncoder.velocity(rpm) > 3000);
  fireDisc();
  enableFlywheel();
  //waitUntil(flywheelEncoder.velocity(rpm) > 3000);
  fireDisc();
  enableFlywheel();
  //waitUntil(flywheelEncoder.velocity(rpm) > 3000);
  fireDisc();
}

void Auton3(){ 
  autoAimColor = SIGBLUE;

  //robot goes to first roller
  moveLinear(-5, 90, 3000);
//robot spins first roller
  enableRollerWheel();
  wait(1000, msec);
  disableRollerWheel();
  //robot moves to second roller
  moveLinear(48, 90, 3000);
  moveRotate(90, 90, 3000);
  moveLinear(36, 90, 3000);
  moveRotate(-90, 90, 3000);
  moveLinear(12, 90, 3000);
  moveRotate(90, 90, 3000);
  moveLinear(20, 90, 3000);
  moveRotate(-90, 90, 3000);
  moveLinear(-12, 90, 3000);
  //robot moves second roller
  enableRollerWheel();
  wait(1000, msec);
  disableRollerWheel();
}

void Auton4()
{
  autoAimColor = SIGBLUE;

}

