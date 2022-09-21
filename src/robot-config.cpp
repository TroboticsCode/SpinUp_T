#include "vex.h"
#include "DriveFunctionsConfig.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor flywheelFront = motor(PORT5, BLUE, true);
motor flywheelBack = motor(PORT6, BLUE, false);
motor intake = motor(PORT7, GREEN, true);

pneumatics piston = pneumatics(Brain.ThreeWirePort.A);
// VEXcode generated functions


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}