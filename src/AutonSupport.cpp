/***********************************
 * AutonSupport.cpp
 * This file contains support
 * functions for selecting auton
 * routines
 * Update as needed, do not delete
***********************************/

#include "Autons.h"
#include "Functions.h"

int state = 0;
char state_name[] = "NONE";

/* void Paint_Screen()
* brief: this function will update the brain's display to show the currently selected auton program
*/
void Paint_Screen(void)
{
  Controller1.Screen.setCursor(3,1);
  Controller1.Screen.clearLine(3);
  Controller1.Screen.print("%s", state_name);
}

/*void cycle_autons
* brief: this function is called when a button on the controller is pressed to advance to the 
*          next auton routine
* Update this function as more auton programs are added
*/
void cycle_autons(void)
{
    if (state == 0)
    {
        state = AutonNear;
        strcpy(state_name, "Auton Near");
    }
    else if (state == AutonNear)
    {
         state =   AutonFar;
         strcpy(state_name, "Auton Far");
    }
    else if (state == AutonFar)
    {
        state = AutonSkills;
        strcpy(state_name, "Auton Skills");
    }
    else if (state == AutonSkills)
    {
        state = AutonWinPoint;
        strcpy(state_name, "Auton Win Point");
    }
    else if (state == AutonWinPoint)
    {
        state = AutonTest;
        strcpy(state_name, "Test");
    }
    else if (state == AutonTest)
    {
        state = NONE;
        strcpy(state_name, "NONE");
    }
    Paint_Screen();
}
