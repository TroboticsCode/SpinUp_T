#include "Autons.h"
#include "DriveFunctionsConfig.h"
#include "Functions.h"
#include "vex.h"

// Put your auton routines in here

void Auton1() {
  setRotGains(.001, 0, 0, 20, 10); //update PID gains to tune robot
  setLinGains(200, 0, 0, 20, 10);

}

void Auton2() {

}

void skills() { //this grabs one yellow goal and gets the win point
  
}

void Auton3(){ //yellow goal blitz

}


