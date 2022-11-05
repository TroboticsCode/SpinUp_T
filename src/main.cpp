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

// define your global instances of motors and other devices here
uint32_t pressTime = 0;
uint8_t discCount = 0;
bool updateScreen = true;

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

  Controller1.ButtonUp.pressed(cycle_autons);
  Brain.Screen.pressed(cycle_autons);
  return;
}

void autonomous(void) {
  switch (state) {
  case NONE:
    break;

  case AutonR:
    Auton1();
    break;

  case AutonB:
    Auton2();
    break;
  case AutonY:
    Auton3();
    break;

  case SKILLS:
    skills();
    break;
  case SKILLS120:
    break;

  // Default = NO autonomous
  default:
    break;
  }
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

void usercontrol(void) {
  flywheelBack.setVelocity(95, pct);
  flywheelFront.setVelocity(95, pct);
  intake.setVelocity(100, pct);
//close up is at 60%
//midfield 75%
//auton starting spot 80%
//full diagnol 95%
  bool flyWheelButtonReleased = false;
  bool flyWheelState = false;

  while (1) {

    userDrive();

    // flywheel control - button toggles on or off
    if (Controller1.ButtonL1.pressing()) 
    {
      if(flyWheelButtonReleased)
      {
         flyWheelButtonReleased = false;
         flyWheelState = !flyWheelState;

         if(flyWheelState)
         {
           flywheelFront.spin(reverse);
           flywheelBack.spin(reverse);
         }
         else
         {
           flywheelFront.stop(coast);
           flywheelBack.stop(coast);
         }
      }
    } 
    else
    {
      flyWheelButtonReleased = true;
    }
      
    // intake control
    // make sure we dont pick up too many discs
    if (Controller1.ButtonY.pressing() && !intakeSwitch.pressing()) 
    {
      intake.spin(reverse);
    }
    else if(Controller1.ButtonRight.pressing())
    {
      intake.spin(fwd);
    }
    else {
      intake.stop(coast);
    }

    //roller control
    if (Controller1.ButtonB.pressing()) 
    {
      rollerWheel.spin(reverse);
    }
    else {
      rollerWheel.stop(coast);
    }

    // piston control
    if (Controller1.ButtonR1.pressing()) {
      piston.open();
    } else {
      piston.close();
    }

    Brain.Screen.clearLine(0);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Wheel Speed: ");
    Brain.Screen.print(flywheelEncoder.velocity(rpm));
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
