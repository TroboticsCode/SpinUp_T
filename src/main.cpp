// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Inertial12           inertial      12
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       JBormann                                                  */
/*    Created:      Nov. 2019                                                 */
/*    Description:  Trobotics Template File                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "Autons.h"
#include "DriveFunctionsConfig.h"
#include "Functions.h"
#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
void updateSpeedDisplay(void);

// define your global instances of motors and other devices here
uint32_t pressTime = 0;
uint8_t discCount = 0;
bool updateScreen = true;

// close up is at 60%
// midfield 75%
// auton starting spot 80%
// full diagnol 95%

pidStruct_t flyWheelPID;
//uint8_t flywheelSpeeds[] = {45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100};
uint16_t flywheelSpeeds[] = {1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2750, 3000, 3200};

uint8_t speedSelector = 1;
const uint8_t numSpeed = 18;

bool flyWheelState = false;
int autoAimColor = SIGRED;
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  pidInit(&flyWheelPID, 0.09, 0.00003, 0, 10, 20);

  Controller1.ButtonUp.pressed(cycle_autons);
  Brain.Screen.pressed(cycle_autons);
  return;
}

void autonomous(void) {
  switch (state) {
  case NONE:
    break;

  case AutonRedNear:
    Auton1();
    break;

  case AutonRedFar:
    Auton2();
    break;
  case AutonBlueNear:
    Auton3();
    break;

  case AutonBlueFar:
    Auton4();
    break;
  
  case SKILLS:
    skills();
    break;

  // Default = NO autonomous
  default:
    break;
  }

  updateSpeedDisplay();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void updateSpeedDisplay(void) {
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1, 1);

  Controller1.Screen.print("speed: %d", flywheelSpeeds[speedSelector]);

  Controller1.Screen.setCursor(1, 12);
  Controller1.Screen.print("Enabled: ");
  Controller1.Screen.print(flyWheelState);
}

void increaseSpeed(void) {
  if (speedSelector < numSpeed - 1) {
      speedSelector++;

      flywheelBack.setVelocity(-1 * flywheelSpeeds[speedSelector], pct);
      //flywheelFront.setVelocity(-1 * flywheelSpeeds[speedSelector], pct);

      updateSpeedDisplay();
    }
}


void decreaseSpeed(void) {
  if (speedSelector > 0) {
    speedSelector--;

    flywheelBack.setVelocity(-1 * flywheelSpeeds[speedSelector], pct);
    //flywheelFront.setVelocity(-1 * flywheelSpeeds[speedSelector], pct);

    updateSpeedDisplay();
  }
}

void usercontrol(void) {

  bool flyWheelButtonReleased = false;

  bool flywheelSpeedButtonReleased = false;
  bool rumbleDone = true;

  double maxCurrent = 0;
  
  setLinGains(50, 0.007, 0, 40, 30);
  setRotGains(50, 0.007, 0, 40, 30);
  intake.setVelocity(100, pct);

  ropeLauncher.close();
  

  while (1) {

    userDrive();

    if (flyWheelState) {
      double motorVoltage = pidCalculate(&flyWheelPID, -1.0f * flywheelSpeeds[speedSelector],flywheelBack.velocity(rpm) * 7);
      motorVoltage = motorVoltage * 12 / 100.0f;
      if(motorVoltage > 0)
        motorVoltage = 0;

      printPIDValues(&flyWheelPID);

      flywheelFront.spin(forward, motorVoltage, voltageUnits::volt);
      flywheelBack.spin(forward, motorVoltage, voltageUnits::volt);

      if (flywheelFront.current() > maxCurrent) // update max current val
        maxCurrent = flywheelFront.current();

      //rumbleDone = false;

    } else {
      flywheelFront.stop(coast);
      flywheelBack.stop(coast);
    }

    // flywheel control - button toggles on or off
    if (Controller1.ButtonL1.pressing()) {
      if (flyWheelButtonReleased) {
        flyWheelButtonReleased = false;
        flyWheelState = !flyWheelState;

        updateSpeedDisplay();       
      }
    } else {
      flyWheelButtonReleased = true;
    }

    // flywheel speed control
    if (Controller1.ButtonR2.pressing() || Controller1.ButtonL2.pressing()) {
      if (flywheelSpeedButtonReleased) {
        if (Controller1.ButtonR2.pressing()) {
          increaseSpeed();
        } else if (Controller1.ButtonL2.pressing()) {
          decreaseSpeed();
        }
      }
      flywheelSpeedButtonReleased = false;
      rumbleDone = false;
    } else {
      flywheelSpeedButtonReleased = true;
    }

    // should only trigger once the motor current has rolled off
    if (!rumbleDone && flywheelFront.current() < maxCurrent / 4) {
      //Controller1.rumble("---");
      rumbleDone = true;
    }

    // intake control
    // make sure we dont pick up too many discs
    if (Controller1.ButtonY.pressing() && !intakeSwitch.pressing()) {
      intake.spin(reverse);
    } else if (Controller1.ButtonRight.pressing()) {
      intake.spin(fwd);
    } else {
      intake.stop(coast);
    }

    // roller control
    if (Controller1.ButtonB.pressing()) {
      rollerWheel.spin(forward);
    } else if (Controller1.ButtonDown.pressing()) {
      rollerWheel.spin(reverse);
    } else {
      rollerWheel.stop(coast);
    }

    // piston control
    if (Controller1.ButtonR1.pressing()) {
      piston.open();
    } else {
      piston.close();
    }

    // rope launcher
    if (Controller1.ButtonA.pressing() && Controller1.ButtonLeft.pressing()) {
      ropeLauncher.open();
    } else {
      ropeLauncher.close();
    }

    if(Controller1.ButtonX.pressing())
    {
      autoAim(autoAimColor);
    }

    Brain.Screen.clearLine(7);
    Brain.Screen.setCursor(7, 1);
    Brain.Screen.print("Wheel Speed: ");
    Brain.Screen.print(flywheelBack.velocity(rpm) * 7);
    Brain.Screen.print(" RPM");
    wait(20, msec); // Sleep the task for a short amount of time to
  }
}

// Main will set up the competition functions and callbacks.

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
