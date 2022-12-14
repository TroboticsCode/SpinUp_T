#ifndef AUTONS_H
#define AUTONS_H

//always include vex.h because it has all the robot setup declarations
//as well as the API for the code.
#include "vex.h"

//add defines here as more auton routines are created
//number them sequentially and match them to the cases names
//in autonomous() in main.cpp
#define NONE 0
#define AutonRedNear  1
#define AutonRedFar   2
#define AutonBlueNear 3
#define AutonBlueFar  4
#define SKILLS 5

extern int state;

//auton support function prototypes
void cycle_autons(void);
void Paint_Screen(void);

//list the names of your autonomous programs here
void Auton1(void);
void Auton2(void);
void Auton3(void);
void Auton4(void);
void skills(void);

#endif
