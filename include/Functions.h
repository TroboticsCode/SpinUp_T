#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define OPEN 1
#define CLOSE 0

#define UP 1
#define DOWN 0

//always include vex.h because it has all the robot setup declarations
//as well as the API for the code.
#include "vex.h"
#include "PID.h"

#define SIGRED   1
#define SIGBLUE  2
#define SIGGREEN 3

//enter the prototypes for other functions here
//lift, claw, etc
//drive function prototypes can go here but they should be in the DriveFunctions.h file
void testPID(void);
void enableFlywheel(void);
void disableFlywheel(void);
void enableIntake(void);
void enableRollerWheel(void);
void disableRollerWheel(void);
void disableIntake(void);
void fireDisc(void);
void autoAim(int color);
int autonFlywheelControl(void);
void setAutonFlywheelSpeed(int16_t speed);
void autonRollerMove(int16_t);


extern int autoAimColor;
extern pidStruct_t flyWheelPID;


#endif