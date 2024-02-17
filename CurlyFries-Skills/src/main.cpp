#include "vex.h"

using namespace vex;

competition Competition;

//Setup
void pre_auton(void) {
  //Initialize
  vexcodeInit();
}
/////

//Autonomous Period
void autonomous(void) {
  while (true) {
    FlyWheel.spin(fwd, 12, voltageUnits::volt);
  }
}
/////

//Main
int main() {
  //Callbacks
  Competition.autonomous(autonomous);

  //Run Pre-Auton
  pre_auton();

  //Prevent Wasted Resources
  while (true) {
    wait(100, msec);
  }
}
/////