#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor TopL = motor(PORT13, ratio6_1, false);
motor MidL = motor(PORT15, ratio6_1, true);
motor LowL = motor(PORT20, ratio6_1, false);
motor TopR = motor(PORT2, ratio6_1, true);
motor MidR = motor(PORT16, ratio6_1, false);
motor LowR = motor(PORT1, ratio6_1, true);


motor Belt = motor(PORT6, ratio6_1, true);
motor Intake = motor(PORT10, ratio6_1, false);

motor_group DrivetrainL = motor_group(TopL, MidL, LowL);
motor_group DrivetrainR = motor_group(TopR, MidR, LowR);
motor_group DrivetrainAll = motor_group(TopL, MidL, LowL, TopR, MidR, LowR);

inertial InertialSensor = inertial(PORT11);

digital_out GoalClamp = digital_out(Brain.ThreeWirePort.A);

controller Controller1 = controller(primary);

/*float wheelDiameter = 2.75;
float wheelBase = 12;*/

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}

/*               ___====-_  _-====___
           _--^^^#####//      \\#####^^^--_
        _-^##########// (    ) \\##########^-_
       -############//  |\^^/|  \\############-
     _/############//   (@::@)   \\############\_
    /#############((     \\//     ))#############\
   -###############\\    (oo)    //###############-
  -#################\\  / VV \  //#################-
 -###################\\/      \//###################-
_#/|##########/\######(   /\   )######/\##########|\#_
|/ |#/\#/\#/\/  \#/\##\  |  |  /##/\#/  \/\#/\#/\#| \|
`  |/  V  V  `   V  \#\| |  | |/#/  V   '  V  V  \|  '
   `   `  `      `   / | |  | | \   '      '  '   '
                    (  | |  | |  )
                   __\ | |  | | /__
                  (vvv(VVV)(VVV)vvv)                 */