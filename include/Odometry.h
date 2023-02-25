#include "vex.h"
//constants used for Odometry

#define odoWheelDiameter 2.75f

//double PI = 3.14159;
#define leftTrackerOffset 4.475f
#define rightTrackerOffset 4.475f
#define backTrackerOffset 3.5f
#define encoderToInches (odoWheelDiameter * 3.14159f)/360.0f

int odo(void);
void printCoords(void);

double get_xAbs(void);
double get_yAbs(void);
double get_tAbs(void);
double get_tAbs_deg(void);