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
        state = AutonRedNear;
        strcpy(state_name, "Auton Red Near");
    }
    else if (state == AutonRedNear)
    {
         state =   AutonRedFar;
         strcpy(state_name, "Auton Red Far");
    }
    else if (state == AutonRedFar)
    {
        state = AutonBlueNear;
        strcpy(state_name, "Auton Blue Near");
    }
    else if (state == AutonBlueNear)
    {
        state = AutonBlueFar;
        strcpy(state_name, "Auton Blue Far");
    }
    else if (state == AutonBlueFar)
    {
        state = AutonRedNearShort;
        strcpy(state_name, "Auton Red Near Short");
    }
    
    //shorts
    else if (state == AutonRedNearShort)
    {
         state =   AutonRedFarShort;
         strcpy(state_name, "Auton Red Far Short");
    }
    else if (state == AutonRedFarShort)
    {
        state = AutonBlueNearShort;
        strcpy(state_name, "Auton Blue Near Short");
    }
    else if (state == AutonBlueNearShort)
    {
        state = AutonBlueFarShort;
        strcpy(state_name, "Auton Blue Far Short");
    }
    else if (state == AutonBlueFarShort)
    {
        state = SKILLS;
        strcpy(state_name, "Skills");
    }
    else if (state == SKILLS)
    {
        state = NONE;
        strcpy(state_name, "NONE");
    }
    else if (state == SKILLS2)
    {
        state = NONE;
        strcpy(state_name, "NONE");
    }
    Paint_Screen();
}
