#include "Autons.h"
#include "DriveFunctionsConfig.h"
#include "Functions.h"
#include "vex.h"

// Put your auton routines in here

void Auton1() {
  autoAimColor = SIGRED;
  
  setRotGains(.0325, 0.0000001, 0, 20, 10); //update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);
 

  flywheelBack.setVelocity(-62, pct);
  flywheelFront.setVelocity(-62, pct);
  
  enableFlywheel();
  
  
  wait(2000, msec);
  
  fireDisc();
 
  flywheelBack.setVelocity(-68, pct);
  flywheelFront.setVelocity(-68, pct);
  
  wait(1000,msec);
  
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

  ropeLauncher.open();
}

void Auton3(){ 
  autoAimColor = SIGBLUE;
  
  setRotGains(.0325, 0.0000001, 0, 20, 10); //update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);
 

  flywheelBack.setVelocity(-100, pct);
  flywheelFront.setVelocity(-100, pct);
  
  enableFlywheel();
  
  
  wait(2000, msec);
  
  fireDisc();
 
  flywheelBack.setVelocity(-100, pct);
  flywheelFront.setVelocity(-100, pct);
  
  wait(1000,msec);
  
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

/*void Auton4()
{
  autoAimColor = SIGBLUE;

}*/

void Auton4(){
  autoAimColor = SIGBLUE;
  
  setRotGains(.0325, 0.0000001, 0, 20, 10); //update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);
 

  flywheelBack.setVelocity(-100, pct);
  flywheelFront.setVelocity(-100, pct);
  
  enableFlywheel();
  
  
  wait(2000, msec);
  
  fireDisc();
 
  flywheelBack.setVelocity(-100, pct);
  flywheelFront.setVelocity(-100, pct);
  
  wait(1000,msec);
  
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
