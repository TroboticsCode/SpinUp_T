#include "Autons.h"
#include "DriveFunctionsConfig.h"
#include "Functions.h"
#include "vex.h"

// Put your auton routines in here



//new Autons bc we only need 3

//Near
void Auton1(){
//Set Gains
  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);
 
  pidInit(&flyWheelPID, 0.0425, 0.0001, 0.02, 20, 15);
  

  setAutonFlywheelSpeed(2350);
  vex::task taskFlywheel(&autonFlywheelControl);
  

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
}

//Far
void Auton2(){
  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);
  pidInit(&flyWheelPID, 0.0425, 0.0001, 0.02, 15, 15);

  vex::task taskFlywheel(&autonFlywheelControl);

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
}

//Skills
void Auton3(){
  //Set Gains
  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(35, 0.0075, 0, 20, 10);
  pidInit(&flyWheelPID, 0.0425, 0.0001, 0.02, 20, 15);
  
  //Start FlyWheel PID Task
  vex::task taskFlywheel(&autonFlywheelControl);

  //Roller 1 and Preload Shots
  myGyro.calibrate();
  while (myGyro.isCalibrating()){
    myGyro.resetRotation();
  }
  setAutonFlywheelSpeed(2175);
  enableRollerWheel();
  moveLinear(-10, 100, 700); 
  disableRollerWheel();

  enableFlywheel();
  moveLinear(28, 80, 2000);
  moveStop(hold);
  moveRotate(-14, 100, 2000);
  moveStop(hold);
  myGyro.calibrate();
  while (myGyro.isCalibrating()){
    myGyro.resetRotation();
    fireDisc();
    wait(1000, msec);
    fireDisc();
    setAutonFlywheelSpeed(0);
  }

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
  myGyro.calibrate();
  while (myGyro.isCalibrating()){
    myGyro.resetRotation();
    wait(1000,msec);
    fireDisc();
    intake.stop();
    wait(700, msec);
    fireDisc();
    wait(700, msec);
    fireDisc();
  }

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
  myGyro.calibrate();
  while (myGyro.isCalibrating()){
    myGyro.resetRotation();
    wait(1000, msec);
    intake.stop();
    fireDisc();
    wait(1000, msec);
    fireDisc();
    setAutonFlywheelSpeed(0);
  }
  

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
  myGyro.calibrate();
  while (myGyro.isCalibrating()){
    myGyro.resetRotation();
    wait(1500, msec);
    fireDisc();
    wait(700, msec);
    fireDisc();
    wait(700, msec);
    fireDisc();
    setAutonFlywheelSpeed(0);
  }
  
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
}

//Test Autons
void Auton4(){
  
}






/* Commented out old skills that are not needed for now



void Auton1() {
  // RED NEAR
  autoAimColor = SIGRED;

  flywheelBack.setVelocity(-100, pct);
  flywheelFront.setVelocity(-100, pct);

  wait(2000, msec);

  fireDisc();

  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);

  flywheelBack.setVelocity(-100, pct);
  flywheelFront.setVelocity(-100, pct);

  enableFlywheel();

  wait(3000, msec);

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

  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);
  pidInit(&flyWheelPID, 0.0425, 0.0001, 0.02, 15, 15);

  vex::task taskFlywheel(&autonFlywheelControl);

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
}
void skills(){
  // NEW SKILLS
  autoAimColor = SIGRED;

<<<<<<< Updated upstream
=======
void skills(){
  // NEW SKILLS
  autoAimColor = SIGRED;

>>>>>>> Stashed changes
  //Set Gains
  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(35, 0.0075, 0, 20, 10);
  pidInit(&flyWheelPID, 0.0425, 0.0001, 0.02, 20, 15);
<<<<<<< Updated upstream
  //Start FlyWheel PID Task

  vex::task taskFlywheel(&autonFlywheelControl);

  //Shoot Preloads
  setAutonFlywheelSpeed(1900);
  enableFlywheel();
  wait(1500, msec);
  fireDisc();
  wait(500, msec);
  fireDisc();
  disableFlywheel();
  setAutonFlywheelSpeed(0);

  // roller 1
  moveLinear(-55, 100, 3000);
  moveStop(hold);
  moveRotate(90, 100, 3000);
  moveLinear(-7, 100, 1000);
  enableRollerWheel();
  wait(700, msec);
  disableRollerWheel();

  // recalibrate since we hit the wall
  while (myGyro.isCalibrating())
    ;

  moveLinear(16, 100, 3000);
  moveStop(hold);

  // roller 2
  moveRotate(-90, 100, 3000);
  moveStop(hold);
  intake.spin(reverse);
  wait(500, msec);
  moveLinear(-24, 100, 3000);
  moveStop(hold);
  enableRollerWheel();
  wait(700, msec);
  disableRollerWheel();

  while (myGyro.isCalibrating())
    ;

  moveLinear(20, 100, 3000);
  moveStop(hold);

  // 1 disc shot
  moveRotate(-10, 100, 2000);
  moveStop(hold);
  intake.stop(coast);
  setAutonFlywheelSpeed(2500);
  enableFlywheel();
  wait(2000, msec);
  fireDisc();
  disableFlywheel();
  intake.spin(reverse);

  // cross to center
  moveRotate(-120, 85, 3000);
  moveStop(hold);
  moveLinear(-50, 100, 3000);
  moveStop(hold);

  // turn and shoot
  moveRotate(82, 75, 3000);
  moveStop(hold);
  setAutonFlywheelSpeed(2300);
  enableFlywheel();
  wait(2000, msec);
  fireDisc();
  wait(1500, msec);
  fireDisc();
  wait(1500, msec);
  fireDisc();
  intake.stop(coast);
  disableFlywheel();

  // turn back to corner
  moveRotate(-98, 75, 3000);
  moveStop(hold);
  moveLinear(-65, 100, 3000);
  moveStop(hold);
  moveLinear(15, 100, 3000);
  moveStop(hold);

  // roller 3
  moveRotate(45, 100, 3000);
  moveStop(hold);
  intake.spin(reverse);
  wait(500, msec);
  moveLinear(-24, 100, 3000);
  moveStop(hold);
  enableRollerWheel();
  wait(700, msec);
  disableRollerWheel();
  moveLinear(16, 100, 3000);
  moveStop(hold);
  intake.stop(coast);

  // roller 4
  moveRotate(-90, 100, 3000);
  moveStop(hold);
  intake.spin(reverse);
  wait(500, msec);
  moveLinear(-24, 100, 3000);
  enableRollerWheel();
  wait(700, msec);
  disableRollerWheel();
  moveLinear(26, 100, 3000);
  moveStop(hold);
  intake.stop(coast);
  moveRotate(45, 100, 3000);

  // rope Launch
  ropeLauncher.open();
  moveLinear(-12, 100, 3000);
=======
  
  //Start FlyWheel PID Task
  vex::task taskFlywheel(&autonFlywheelControl);

  //Roller 1 and Preload Shots
  myGyro.calibrate();
  while (myGyro.isCalibrating()){
    myGyro.resetRotation();
  }
  setAutonFlywheelSpeed(2175);
  enableRollerWheel();
  moveLinear(-10, 100, 700); 
  disableRollerWheel();

  enableFlywheel();
  moveLinear(28, 80, 2000);
  moveStop(hold);
  moveRotate(-14, 100, 2000);
  moveStop(hold);
  myGyro.calibrate();
  while (myGyro.isCalibrating()){
    myGyro.resetRotation();
    fireDisc();
    wait(1000, msec);
    fireDisc();
    setAutonFlywheelSpeed(0);
  }

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
  myGyro.calibrate();
  while (myGyro.isCalibrating()){
    myGyro.resetRotation();
    wait(1000,msec);
    fireDisc();
    intake.stop();
    wait(700, msec);
    fireDisc();
    wait(700, msec);
    fireDisc();
  }

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
  myGyro.calibrate();
  while (myGyro.isCalibrating()){
    myGyro.resetRotation();
    wait(1000, msec);
    intake.stop();
    fireDisc();
    wait(1000, msec);
    fireDisc();
    setAutonFlywheelSpeed(0);
  }
  

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
  myGyro.calibrate();
  while (myGyro.isCalibrating()){
    myGyro.resetRotation();
    wait(1500, msec);
    fireDisc();
    wait(700, msec);
    fireDisc();
    wait(700, msec);
    fireDisc();
    setAutonFlywheelSpeed(0);
  }
  
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
>>>>>>> Stashed changes
  moveStop(hold);

  //END THE TASK
  taskFlywheel.stop();
}


void oldSkills() {
  // SKILLS (RED SIDE!!!)
  autoAimColor = SIGRED;

  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(35, 0.0075, 0, 20, 10);

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
  moveLinear(-52, 100, 50000);
  moveStop(hold);
  moveRotate(90, 100, 1000);
<<<<<<< Updated upstream
=======
  moveStop(hold);
>>>>>>> Stashed changes
  moveLinear(-6, 100, 1000);
  enableRollerWheel();
  wait(700, msec);
  disableRollerWheel();

  // recalibrate since we hit the wall
  while (myGyro.isCalibrating())
    ;

  moveLinear(21, 100, 1000);
  moveStop(hold);

  // roller 2
  moveRotate(-90, 100, 1250);
  moveStop(hold);
  intake.spin(reverse);
  wait(500, msec);
  moveLinear(-24, 100, 1000);
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


void Auton4() {

  // BLUE FAR
  autoAimColor = SIGBLUE;

  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);
  pidInit(&flyWheelPID, 0.0425, 0.0001, 0.02, 15, 15);

  vex::task taskFlywheel(&autonFlywheelControl);

  moveLinear(-24, 80, 2000);
  moveStop(hold);
  moveRotate(90, 75, 1500);
  moveLinear(-5, 75, 1000);
  enableRollerWheel();
  wait(500, msec);
  disableRollerWheel();
  moveLinear(8, 80, 1500);

<<<<<<< Updated upstream
  moveRotate(12, 75, 1000);
  moveStop(hold);
  setAutonFlywheelSpeed(2500);
  enableFlywheel();
  wait(1500, msec);
=======
  moveRotate(10, 75, 1000);
  moveStop(hold);
  setAutonFlywheelSpeed(2300);
  enableFlywheel();
  wait(2500, msec);
>>>>>>> Stashed changes
  fireDisc();
  wait(1500, msec);
  fireDisc();
  disableFlywheel();
  taskFlywheel.stop();
}
///////////////////////////////////////////////

void Auton5() {
  // RED NEAR SHORT
  autoAimColor = SIGRED;

  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);

  
  pidInit(&flyWheelPID, 0.0425, 0.0001, 0.02, 20, 15);
  
<<<<<<< Updated upstream
  setAutonFlywheelSpeed(2500);
=======
  setAutonFlywheelSpeed(2350);
>>>>>>> Stashed changes

  vex::task taskFlywheel(&autonFlywheelControl);
  

<<<<<<< Updated upstream
  wait(5000, msec);

  fireDisc();

  setAutonFlywheelSpeed(2500);

  wait(2500, msec);
=======
  wait(2500, msec);

  fireDisc();

  wait(3000, msec);
>>>>>>> Stashed changes

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
}

void Auton6() // Testing the flywheel speed control
// RED FAR SHORT
{
  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(35, 0.0075, 0, 20, 10);
  myGyro.calibrate();
  while(true){
    Controller1.Screen.clearScreen();
    Controller1.Screen.newLine();
    Controller1.Screen.print(myGyro.heading());
  }
}

void Auton7() {
  // BLUE NEAR SHORT
  autoAimColor = SIGBLUE;

  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);

  
  pidInit(&flyWheelPID, 0.0425, 0.0001, 0.02, 20, 15);
  
<<<<<<< Updated upstream
  setAutonFlywheelSpeed(2500);
=======
  setAutonFlywheelSpeed(2350);
>>>>>>> Stashed changes

  vex::task taskFlywheel(&autonFlywheelControl);
  

<<<<<<< Updated upstream
  wait(5000, msec);

  fireDisc();

  setAutonFlywheelSpeed(2500);

  wait(2500, msec);
=======
  wait(2500, msec);

  fireDisc();

  wait(3000, msec);
>>>>>>> Stashed changes

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
}

void Auton8() {
  // BLUE FAR SHORT
<<<<<<< Updated upstream
  
=======
  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(35, 0.0075, 0, 20, 10);
  myGyro.calibrate();
  Controller1.Screen.print(myGyro.heading());
  moveRotate(360, 100, 5000);
  moveStop(hold);
  Controller1.Screen.clearScreen();
  Controller1.Screen.newLine();
  Controller1.Screen.print(myGyro.heading());
  wait(5000, msec);
  moveRotate(-360, 100, 5000);
  moveStop(hold);
  Controller1.Screen.clearScreen();
  Controller1.Screen.newLine();
  Controller1.Screen.print(myGyro.heading());
  wait(5000, msec);
  moveRotate(360, 100, 5000);
  moveStop(hold);
  Controller1.Screen.clearScreen();
  Controller1.Screen.newLine();
  Controller1.Screen.print(myGyro.heading());
  wait(5000, msec);
  moveRotate(-360, 100, 5000);
  moveStop(hold);
  Controller1.Screen.clearScreen();
  Controller1.Screen.newLine();
  Controller1.Screen.print(myGyro.heading());
  wait(5000, msec);
>>>>>>> Stashed changes
}

void skills2() {
  // RED FAR
  autoAimColor = SIGRED;

  setRotGains(.0325, 0.0000001, 0, 20, 10); // update PID gains to tune robot
  setLinGains(150, 0.07, 0, 20, 10);
  pidInit(&flyWheelPID, 0.0425, 0.0001, 0.02, 15, 15);

  vex::task taskFlywheel(&autonFlywheelControl);

  moveLinear(-24, 80, 2000);
  moveStop(hold);
  moveRotate(90, 75, 1500);
  moveLinear(-5, 75, 1000);
  enableRollerWheel();
  wait(500, msec);
  disableRollerWheel();
  moveLinear(8, 80, 1500);

  moveRotate(12, 75, 1000);
  moveStop(hold);
  setAutonFlywheelSpeed(2500);
  enableFlywheel();
  wait(1500, msec);
  fireDisc();
  wait(1500, msec);
  fireDisc();
  disableFlywheel();
  taskFlywheel.stop();
}
<<<<<<< Updated upstream
=======
*/
>>>>>>> Stashed changes
