#include "Autons.h"
#include "DriveFunctionsConfig.h"
#include "Functions.h"
#include "vex.h"
#include "Odometry.h"

// Put your auton routines in here
//New Autons bc we only need 3

//Near
void Auton1(){
//Set Gains
  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);
 
  pidInit(&flyWheelPID, 0.0425, 0.0001, 0.02, 20, 15);
  
  setAutonFlywheelSpeed(2350);
  vex::task taskFlywheel(&autonFlywheelControl);
  vex::task taskOdometry(&odo);

  wait(2500, msec);

  fireDisc();

  wait(3000, msec);

  fireDisc();

  disableFlywheel();
  taskFlywheel.stop();

  moveRotate(12, 100, 2000);
  moveLinear(-8, 100, 1000);

  enableRollerWheel();
  uint32_t currTime = Brain.Timer.system();
  while ((Brain.Timer.system() - currTime < 500))
    ;
  disableRollerWheel();
  taskFlywheel.stop();
  taskOdometry.stop();
}

//Far
void Auton2(){
  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);
  pidInit(&flyWheelPID, 0.0425, 0.0001, 0.02, 15, 15);

  vex::task taskFlywheel(&autonFlywheelControl);
  vex::task taskOdometry(&odo);

  moveLinear(-20, 80, 2000);
  moveStop(hold);
  moveRotate(90, 75, 1500);
  moveLinear(-5, 75, 1000);
  enableRollerWheel();
  wait(500, msec);
  disableRollerWheel();
  moveLinear(8, 80, 1500);

  moveRotate(18, 75, 1000);
  moveStop(hold);
  setAutonFlywheelSpeed(2320);
  enableFlywheel();
  wait(2500, msec);
  fireDisc();
  wait(1500, msec);
  fireDisc();
  disableFlywheel();
  taskFlywheel.stop();
  taskOdometry.stop();
}

//Skills
void Auton3(){
  //Set Gains
  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(35, 0.0075, 0, 20, 10);
  //pidInit(&flyWheelPID, 0.0425, 0.0001, 0.02, 20, 15);
  
  //Start FlyWheel PID Task
  vex::task taskFlywheel(&autonFlywheelControl);
  vex::task taskOdometry(&odo);

  //Roller 1 and Preload Shots
  setAutonFlywheelSpeed(2175);
  enableRollerWheel();
  moveLinear(-10, 100, 700); 
  disableRollerWheel();

  enableFlywheel();
  moveLinear(28, 80, 2000);
  moveStop(hold);
  moveRotate(-14, 100, 2000);
  moveStop(hold);
  fireDisc();
  wait(1000, msec);
  fireDisc();
  setAutonFlywheelSpeed(0);

  //Roller 2
  moveRotate(98, 75, 2000);
  intake.spin(reverse);
  moveStop(hold);
  moveLinear(-30, 100, 1000);
  moveStop(hold);
  enableRollerWheel();
  moveLinear(-10, 100, 700);
  disableRollerWheel();
  intake.stop();

  //Move and next 3 shots
  moveLinear(15, 100, 1000);
  moveStop(hold);
  moveRotate(135, 75, 2000);
  moveStop(hold);
  intake.spin(reverse);
  moveLinear(-35, 100, 2000);
  moveStop(hold);

  //Turn and shoot
  setAutonFlywheelSpeed(2050);
  moveRotate(98, 75, 2500);
  moveStop(hold);
  wait(1000,msec);
  fireDisc();
  intake.stop();
  wait(700, msec);
  fireDisc();
  wait(700, msec);
  fireDisc();

  //Next 2 Discs
  intake.spin(reverse);
  moveLinear(-10, 100, 1000);
  moveStop(hold);
  moveLinear(20, 100, 1000);
  moveStop(hold);
  moveRotate(-90, 100, 2000);
  moveStop(hold);
  moveLinear(-20, 100, 1000);
  moveStop(hold);
  setAutonFlywheelSpeed(2050);
  moveRotate(74, 100, 2000);
  moveStop(hold);
  wait(1000, msec);
  intake.stop();
  fireDisc();
  wait(1000, msec);
  fireDisc();
  setAutonFlywheelSpeed(0);
  

  //Pick up the Next 3 Discs
  moveRotate(-75, 100, 2000);
  moveStop(hold);
  intake.spin(reverse);
  moveLinear(-25, 75, 2000);
  moveLinear(-15,75, 1000);
  moveStop(hold);
  setAutonFlywheelSpeed(2100);
  moveRotate(37, 75, 2000);
  moveStop(hold);
  wait(1500, msec);
  fireDisc();
  wait(700, msec);
  fireDisc();
  wait(700, msec);
  fireDisc();
  setAutonFlywheelSpeed(0);

  
  //Roller 3
  moveLinear(-45, 75, 3000);
  moveStop(hold);
  enableRollerWheel();
  moveLinear(-10, 100, 700);
  disableRollerWheel();
  moveLinear(24, 100, 1000);
  moveStop(hold);

  //Roller 4
  moveRotate(-90, 75, 2000);
  moveStop(hold);
  moveLinear(-24, 100, 1000);
  enableRollerWheel();
  moveLinear(-10, 100, 700);
  disableRollerWheel();
  intake.stop();

  //ENDGAME!!!
  moveLinear(18, 100, 1000);
  moveStop(hold);
  moveRotate(45, 100, 1000);
  moveStop(hold);
  ropeLauncher.open();
  moveLinear(-12, 100, 1000);
  moveStop(hold);

  //END THE TASK
  taskFlywheel.stop();
  taskOdometry.stop();
}

//Test Autons
void Auton4(){
  //Set Gains
  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);
  vex::task taskOdometry(&odo);
 
  wait(500, sec);

  taskOdometry.stop();
}
