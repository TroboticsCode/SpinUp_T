#include "vex.h"
//constants used for Odometry

#define odoWheelDiameter 2.75f

//double PI = 3.14159;
#define leftTrackerOffset 4.725f
#define rightTrackerOffset 4.725f
#define backTrackerOffset 0.0f
#define encoderToInches odoWheelDiameter * M_PI/360

int odo(void);
void printCoords(void);

double get_xAbs(void);
double get_yAbs(void);
double get_tAbs(void);
double get_tAbs_deg(void);