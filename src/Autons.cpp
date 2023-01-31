#include "Autons.h"
#include "DriveFunctionsConfig.h"
#include "Functions.h"
#include "vex.h"
#include "v5lvgl.h"

// Put your auton routines in here

void Auton1() {
  // RED NEAR
  autoAimColor = SIGRED;

  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);

  flywheelBack.setVelocity(-100, pct);
  flywheelFront.setVelocity(-100, pct);

  enableFlywheel();

  wait(3000, msec);

  fireDisc();

  flywheelBack.setVelocity(-100, pct);
  flywheelFront.setVelocity(-100, pct);

  wait(2000, msec);

  fireDisc();

  disableFlywheel();

  moveRotate(15, 100, 2000);
  moveStop(hold);
  moveLinear(-8, 100, 1000);

  enableRollerWheel();
  uint32_t currTime = Brain.Timer.system();
  while ((Brain.Timer.system() - currTime < 500))
    ;
  disableRollerWheel();

  // move away from roller, then drive to other roller
  moveLinear(5, 100, 1000);
  moveRotate(50, 100, 3000);
  moveLinear(80, 100, 3000);
  moveStop(hold);

  // rotate a bit further so we stay on our side of the field
  moveRotate(135, 100, 1000);
  moveStop(hold);

  // turn around to face the roller
  moveLinear(-5, 100, 1000); // back up to the roller
  moveStop(hold);
  moveRotate(23, 100, 3000);
  moveLinear(-38, 100, 1500);
  moveRotate(20, 100, 1000);
  moveLinear(-6, 100, 1000);
  moveRotate(5, 100, 1000);
  moveLinear(-2, 100, 1000);

  // enable roller motor
  enableRollerWheel();
  currTime = Brain.Timer.system();
  while ((Brain.Timer.system() - currTime < 500))
    ;
  disableRollerWheel();
}

void Auton2() {
  // RED FAR
  autoAimColor = SIGRED;

  setRotGains(.05, 0.00000000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(200, 0, 0, 20, 10);

  moveLinear(-24, 80, 3000);
  moveRotate(90, 75, 1500);
  moveLinear(-5, 75, 1000);
  enableRollerWheel();
  wait(500, msec);
  disableRollerWheel();
  moveLinear(5, 80, 1500);
  moveRotate(10, 75, 1500);
  moveStop(hold);
  flywheelBack.setVelocity(-60, pct);
  flywheelFront.setVelocity(-60, pct);
  enableFlywheel();
  wait(2000, msec);
  fireDisc();
  wait(2000, msec);
  fireDisc();
  disableFlywheel();
}

void skills() {
  // SKILLS (RED SIDE!!!)
  autoAimColor = SIGRED;

  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);

  // shoot preload 1
  flywheelBack.setVelocity(-50, pct);
  flywheelFront.setVelocity(-50, pct);
  enableFlywheel();
  wait(1000, msec);
  fireDisc();

  // shoot preload 2
  flywheelBack.setVelocity(-50, pct);
  flywheelFront.setVelocity(-50, pct);
  wait(500, msec);
  fireDisc();
  disableFlywheel();

  // roller 1
  moveLinear(-52, 100, 1500);
  moveStop(hold);
  moveRotate(90, 100, 1000);
  moveLinear(-5, 100, 1000);
  enableRollerWheel();
  wait(700, msec);
  disableRollerWheel();

  // recalibrate since we hit the wall
  while (myGyro.isCalibrating())
    ;

  moveLinear(17, 100, 1000);
  moveStop(hold);

  // roller 2
  moveRotate(-90, 100, 1250);
  moveStop(hold);
  intake.spin(reverse);
  wait(500, msec);
  moveLinear(-20, 100, 1000);
  moveStop(hold);
  enableRollerWheel();
  wait(700, msec);
  disableRollerWheel();

  while (myGyro.isCalibrating())
    ;

  moveLinear(20, 100, 1000);
  moveStop(hold);

  // 1 disc shot
  moveRotate(-13, 100, 1000);
  moveStop(hold);
  intake.stop(coast);
  flywheelBack.setVelocity(-74, pct);
  flywheelFront.setVelocity(-74, pct);
  enableFlywheel();
  wait(2000, msec);
  fireDisc();
  disableFlywheel();
  intake.spin(reverse);

  // cross to center
  moveRotate(-121, 85, 2000);
  moveStop(hold);
  moveLinear(-15, 50, 1000);
  intake.stop(coast); // here to stop and restart the intake if disc is jammed
  intake.spin(reverse);
  moveLinear(-35, 100, 1000);
  moveStop(hold);

  // turn and shoot
  moveRotate(78, 75, 1000);
  moveStop(hold);
  flywheelBack.setVelocity(-60, pct);
  flywheelFront.setVelocity(-60, pct);
  enableFlywheel();
  wait(2000, msec);
  fireDisc();
  wait(1500, msec);
  fireDisc();
  //  wait(1500, msec);
  //  fireDisc();
  intake.stop(coast);
  disableFlywheel();

  // turn back to corner
  moveRotate(-78, 75, 1000);
  moveStop(hold);
  moveLinear(-90, 100, 2000);
  moveStop(hold);
  moveLinear(15, 100, 1000);
  moveStop(hold);

  // roller 3
  moveRotate(45, 100, 1000);
  moveStop(hold);
  intake.spin(reverse);
  wait(500, msec);
  moveLinear(-24, 100, 1000);
  moveStop(hold);
  enableRollerWheel();
  wait(700, msec);
  disableRollerWheel();
  moveLinear(16, 100, 1000);
  moveStop(hold);
  intake.stop(coast);

  // roller 4
  moveRotate(-90, 100, 1000);
  moveStop(hold);
  intake.spin(reverse);
  wait(500, msec);
  moveLinear(-24, 100, 1000);
  enableRollerWheel();
  wait(700, msec);
  disableRollerWheel();
  moveLinear(26, 100, 1000);
  moveStop(hold);
  intake.stop(coast);
  moveRotate(45, 100, 1000);

  // rope Launch
  ropeLauncher.open();
  moveLinear(-12, 100, 1000);
  moveStop(hold);
}

void Auton3() {
  // BLUE NEAR
  autoAimColor = SIGBLUE;

  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);

  flywheelBack.setVelocity(-100, pct);
  flywheelFront.setVelocity(-100, pct);

  enableFlywheel();

  wait(3000, msec);

  fireDisc();

  flywheelBack.setVelocity(-100, pct);
  flywheelFront.setVelocity(-100, pct);

  wait(2000, msec);

  fireDisc();

  disableFlywheel();

  moveRotate(15, 100, 2000);
  moveStop(hold);
  moveLinear(-8, 100, 1000);

  enableRollerWheel();
  uint32_t currTime = Brain.Timer.system();
  while ((Brain.Timer.system() - currTime < 500))
    ;
  disableRollerWheel();

  // move away from roller, then drive to other roller
  moveLinear(5, 100, 1000);
  moveRotate(50, 100, 3000);
  moveLinear(80, 100, 3000);
  moveStop(hold);

  // rotate a bit further so we stay on our side of the field
  moveRotate(135, 100, 1000);
  moveStop(hold);

  // turn around to face the roller
  moveLinear(-5, 100, 1000); // back up to the roller
  moveStop(hold);
  moveRotate(23, 100, 3000);
  moveLinear(-38, 100, 1500);
  moveRotate(20, 100, 1000);
  moveLinear(-6, 100, 1000);
  moveRotate(5, 100, 1000);
  moveLinear(-2, 100, 1000);

  // enable roller motor
  enableRollerWheel();
  currTime = Brain.Timer.system();
  while ((Brain.Timer.system() - currTime < 500))
    ;
  disableRollerWheel();
}

/*void Auton4()
{
  autoAimColor = SIGBLUE;

}*/

void Auton4() {

  // BLUE FAR
  autoAimColor = SIGBLUE;

  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);

  moveLinear(-24, 80, 3000);
  moveRotate(90, 75, 1500);
  moveLinear(-5, 75, 1000);
  enableRollerWheel();
  wait(500, msec);
  disableRollerWheel();
  moveLinear(5, 80, 1500);

  /* does not see goal for some reason
    uint32_t currTime = Brain.Timer.system();
    while((Brain.Timer.system() - currTime < 2000))
    {
      autoAim(autoAimColor);
    }
    */
  moveRotate(2, 75, 1000);
  moveStop(hold);
  flywheelBack.setVelocity(-75, pct);
  flywheelFront.setVelocity(-75, pct);
  enableFlywheel();
  wait(2000, msec);
  fireDisc();
  wait(2000, msec);
  fireDisc();
  disableFlywheel();
}

///////////////////////////////////////////////

void Auton5() {
  // RED NEAR SHORT
  autoAimColor = SIGRED;

  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);

  //need ~2350 rpm here
  flywheelBack.setVelocity(-66, pct);
  flywheelFront.setVelocity(-66, pct);

  enableFlywheel();

  wait(4500, msec);

  fireDisc();

  flywheelBack.setVelocity(-66, pct);
  flywheelFront.setVelocity(-66, pct);
  wait(3000, msec);

  fireDisc();

  disableFlywheel();

  moveRotate(15, 100, 2000);
  moveLinear(-8, 100, 1000);

  enableRollerWheel();
  uint32_t currTime = Brain.Timer.system();
  while ((Brain.Timer.system() - currTime < 500));
  disableRollerWheel();
}

void Auton6() // Testing the flywheel speed control
// RED FAR SHORT
{
  pidInit(&flyWheelPID, 0.0425, 0.0001, 0.02, 20, 15);
  vex::task taskFlywheel(&autonFlywheelControl);

  // setAutonFlywheelSpeed(1000);

  // wait(5, seconds);

  // setAutonFlywheelSpeed(1500);

  // wait(5, seconds);

  // setAutonFlywheelSpeed(2000);

  // wait(5, seconds);

  // setAutonFlywheelSpeed(2500);

  // wait(5, seconds);

  setAutonFlywheelSpeed(1850);

  wait(60, seconds);
  fireDisc();
  wait(3, seconds);
  fireDisc();
  disableFlywheel();
  taskFlywheel.stop();
}

void Auton7() {
  // BLUE NEAR SHORT
  autoAimColor = SIGBLUE;

  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);

  flywheelBack.setVelocity(-73, pct);
  flywheelFront.setVelocity(-73, pct);

  enableFlywheel();

  wait(3500, msec);

  fireDisc();

  flywheelBack.setVelocity(-92, pct);
  flywheelFront.setVelocity(-92, pct);

  wait(3000, msec);

  fireDisc();

  disableFlywheel();

  moveRotate(15, 100, 2000);
  moveLinear(-8, 100, 1000);

  enableRollerWheel();
  uint32_t currTime = Brain.Timer.system();
  while ((Brain.Timer.system() - currTime < 500))
    ;
  disableRollerWheel();
}

void Auton8() {
  // BLUE FAR SHORT
}
