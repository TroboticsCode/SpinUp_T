#include "Autons.h"
#include "DriveFunctionsConfig.h"
#include "Functions.h"
#include "vex.h"

// Put your auton routines in here

void Auton1() {
  //RED NEAR
  autoAimColor = SIGRED;
  
  setRotGains(.0325, 0.0000001, 0, 20, 10); //update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);
 

  flywheelBack.setVelocity(-100, pct);
  flywheelFront.setVelocity(-100, pct);
  
  enableFlywheel();
  
  
  wait(3000, msec);
  
  fireDisc();
 
  flywheelBack.setVelocity(-100, pct);
  flywheelFront.setVelocity(-100, pct);
  
  wait(2000,msec);
  
  fireDisc();

  disableFlywheel();

  moveRotate(15, 100, 2000);
  moveLinear(-8, 100, 1000);

  enableRollerWheel();
  uint32_t currTime = Brain.Timer.system();
  while((Brain.Timer.system() - currTime < 500));
  disableRollerWheel();

  //move away from roller, then drive to other roller
  moveLinear(5, 100, 1000);
  moveRotate(50, 100, 3000);
  moveLinear(80, 100, 3000);
  moveStop(hold);


  //rotate a bit further so we stay on our side of the field
  moveRotate(135, 100, 1000);
  moveStop(hold);

  //turn around to face the roller
  moveLinear(-5, 100, 1000); //back up to the roller
  moveStop(hold);
  moveRotate(23, 100, 3000);
  moveLinear(-38, 100, 1500);
  moveRotate(20, 100, 1000);
  moveLinear(-6, 100, 1000);
  moveRotate(5, 100, 1000);
  moveLinear(-2, 100, 1000);

  //enable roller motor
  enableRollerWheel();
  currTime = Brain.Timer.system();
  while((Brain.Timer.system() - currTime < 500));
  disableRollerWheel();
}

void Auton2() {
  //RED FAR
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
  flywheelBack.setVelocity(-100, pct);
  flywheelFront.setVelocity(-100, pct);
  
  enableFlywheel();
  //step 2:
  //waitUntil(flywheelEncoder.velocity(rpm) > 2500);
  
  wait(3000, msec);
  //step 3:
  fireDisc();
  //step 4:
  flywheelBack.setVelocity(-100, pct);
  flywheelFront.setVelocity(-100, pct);
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

}

void skills() {
  //SKILLS (RED SIDE!!!)
  autoAimColor = SIGRED;

  setRotGains(.0325, 0.0000001, 0, 20, 10); //update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);
 
//shoot preload 1
  flywheelBack.setVelocity(-50, pct);
  flywheelFront.setVelocity(-50, pct);
  enableFlywheel(); 
  wait(1000, msec);
  fireDisc();

 //shoot preload 2
  flywheelBack.setVelocity(-50, pct);
  flywheelFront.setVelocity(-50, pct);
  wait(500,msec);
  fireDisc();
  disableFlywheel();

//roller 1
  moveLinear(-52, 100, 2000);
  moveStop(hold);
  moveRotate(90, 100, 1000);
  moveLinear(-3, 100, 1000);
  enableRollerWheel();
  wait(700, msec);
  disableRollerWheel();
  moveLinear(17, 100, 1000);
  moveStop(hold);

  //roller 2
  moveRotate(-90, 100, 1000);
  moveStop(hold);
  intake.spin(reverse);
  wait(500, msec);
  moveLinear(-20, 100, 1000);
  moveStop(hold);
  enableRollerWheel();
  wait(700, msec);
  disableRollerWheel();
  moveLinear(20, 100, 1000);
  moveStop(hold);

  //1 disc shot
  moveRotate(-12, 100, 1000);
  moveStop(hold);
  intake.stop(coast);
  flywheelBack.setVelocity(-75, pct);
  flywheelFront.setVelocity(-75, pct);
  enableFlywheel(); 
  wait(2000, msec);
  fireDisc();
  disableFlywheel();
  moveRotate(12, 100, 1000);
  moveStop(hold);
  intake.spin(reverse);

  //cross to center
  moveRotate(-132, 85, 2000);
  moveStop(hold);
  moveLinear(-15, 75, 1500);
  moveStop(hold);
  moveLinear(-35, 100, 1500);
  moveStop(hold);

  //turn and shoot
  moveRotate(88, 75, 2000);
  moveStop(hold);
  flywheelBack.setVelocity(-60, pct);
  flywheelFront.setVelocity(-60, pct);
  enableFlywheel(); 
  wait(2000, msec);
  fireDisc();
  wait(1500, msec);
  fireDisc();
  wait(1500, msec);
  fireDisc();
  intake.stop(coast);
  disableFlywheel();

  //turn back to corner
  moveRotate(-88, 75, 2000);
  moveStop(hold);
  moveLinear(-95, 100, 1500);
  moveStop(hold);
  moveLinear(15, 100, 1000);
  moveStop(hold);

  //roller 3
  moveRotate(45, 100, 1500);
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

  //roller 4
  moveRotate(-90, 100, 1000);
  moveStop(hold);
  intake.spin(reverse);
  wait(500, msec);
  moveLinear(-24, 100, 1000);
  moveStop(hold);
  enableRollerWheel();
  wait(700, msec);
  disableRollerWheel();
  moveLinear(26, 100, 1000);
  moveStop(hold);
  intake.stop(coast);
  moveRotate(45, 100, 1000);
  moveStop(hold);

//rope Launch
  ropeLauncher.open();
  moveLinear(-12, 100, 1000);
  moveStop(hold);
}


void Auton3(){ 
  //BLUE NEAR
  autoAimColor = SIGBLUE;
  
  setRotGains(.0325, 0.0000001, 0, 20, 10); //update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);
 

  flywheelBack.setVelocity(-100, pct);
  flywheelFront.setVelocity(-100, pct);
  
  enableFlywheel();
  
  
  wait(3000, msec);
  
  fireDisc();
 
  flywheelBack.setVelocity(-100, pct);
  flywheelFront.setVelocity(-100, pct);
  
  wait(2000,msec);
  
  fireDisc();

  disableFlywheel();

  moveRotate(15, 100, 2000);
  moveLinear(-8, 100, 1000);

  enableRollerWheel();
  uint32_t currTime = Brain.Timer.system();
  while((Brain.Timer.system() - currTime < 500));
  disableRollerWheel();

  //move away from roller, then drive to other roller
  moveLinear(5, 100, 1000);
  moveRotate(50, 100, 3000);
  moveLinear(80, 100, 3000);
  moveStop(hold);


  //rotate a bit further so we stay on our side of the field
  moveRotate(135, 100, 1000);
  moveStop(hold);

  //turn around to face the roller
  moveLinear(-5, 100, 1000); //back up to the roller
  moveStop(hold);
  moveRotate(23, 100, 3000);
  moveLinear(-38, 100, 1500);
  moveRotate(20, 100, 1000);
  moveLinear(-6, 100, 1000);
  moveRotate(5, 100, 1000);
  moveLinear(-2, 100, 1000);

  //enable roller motor
  enableRollerWheel();
  currTime = Brain.Timer.system();
  while((Brain.Timer.system() - currTime < 500));
  disableRollerWheel();
}

/*void Auton4()
{
  autoAimColor = SIGBLUE;

}*/

void Auton4(){

  //BLUE FAR
  autoAimColor = SIGBLUE;
  
  setRotGains(.0325, 0.0000001, 0, 20, 10); //update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);
 

  flywheelBack.setVelocity(-100, pct);
  flywheelFront.setVelocity(-100, pct);
  
  enableFlywheel();
  
  
  wait(3000, msec);
  
  fireDisc();
 
  flywheelBack.setVelocity(-100, pct);
  flywheelFront.setVelocity(-100, pct);
  
  wait(2000,msec);
  
  fireDisc();

  disableFlywheel();

  moveRotate(15, 100, 2000);
  moveLinear(-8, 100, 1000);

  enableRollerWheel();
  uint32_t currTime = Brain.Timer.system();
  while((Brain.Timer.system() - currTime < 500));
  disableRollerWheel();

  //move away from roller, then drive to other roller
  moveLinear(5, 100, 1000);
  moveRotate(50, 100, 3000);
  moveLinear(125, 100, 3000);
  moveStop(hold);

  //rotate a bit further so we stay on our side of the field
  moveRotate(160, 100, 1000);
  moveStop(hold);

  //turn around to face the roller
  moveLinear(-8, 100, 1000); //back up to the roller
  moveStop(hold);
  moveRotate(60, 100, 3000);
  moveLinear(-12, 100, 3000);

  //enable roller motor
  enableRollerWheel();
  currTime = Brain.Timer.system();
  while((Brain.Timer.system() - currTime < 500));
  disableRollerWheel();
}

///////////////////////////////////////////////

void Auton5()
{
  //RED NEAR SHORT
  autoAimColor = SIGRED;
  
  setRotGains(.0325, 0.0000001, 0, 20, 10); //update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);
 

  flywheelBack.setVelocity(-66, pct);
  flywheelFront.setVelocity(-66, pct);
  
  enableFlywheel();
  
  
  wait(4500, msec);
  
  fireDisc();
 
  flywheelBack.setVelocity(-66, pct);
  flywheelFront.setVelocity(-66, pct);
  wait(3000,msec);
  
  fireDisc();

  disableFlywheel();

  moveRotate(15, 100, 2000);
  moveLinear(-8, 100, 1000);

  enableRollerWheel();
  uint32_t currTime = Brain.Timer.system();
  while((Brain.Timer.system() - currTime < 500));
  disableRollerWheel();
}

void Auton6()
{
  //RED FAR SHORT
}

void Auton7()
{
  //BLUE NEAR SHORT
  autoAimColor = SIGBLUE;
  
  setRotGains(.0325, 0.0000001, 0, 20, 10); //update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);
 

  flywheelBack.setVelocity(-73, pct);
  flywheelFront.setVelocity(-73, pct);
  
  enableFlywheel();
  
  
  wait(3000, msec);
  
  fireDisc();
 
  flywheelBack.setVelocity(-92, pct);
  flywheelFront.setVelocity(-92, pct);
  
  wait(3000,msec);
  
  fireDisc();

  disableFlywheel();

  moveRotate(15, 100, 2000);
  moveLinear(-8, 100, 1000);

  enableRollerWheel();
  uint32_t currTime = Brain.Timer.system();
  while((Brain.Timer.system() - currTime < 500));
  disableRollerWheel();

}

void Auton8()
{
  //BLUE FAR SHORT

}
