#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor FrontL = motor(PORT6, ratio6_1, true);
motor BackL = motor(PORT12, ratio6_1, false);
motor FrontR = motor(PORT19, ratio6_1, false);
motor BackR = motor(PORT20, ratio6_1, true);

motor ArmL = motor(PORT1, ratio6_1, false);
motor ArmR = motor(PORT4, ratio6_1, true);

motor ClawL = motor(PORT7, ratio18_1, false);
motor ClawR = motor(PORT8, ratio18_1, true);

motor_group DrivetrainL = motor_group(FrontL, BackL);
motor_group DrivetrainR = motor_group(FrontR, BackR);
motor_group ArmPair = motor_group(ArmL, ArmR);
motor_group ClawPair = motor_group(ClawL, ClawR);

digital_out GoalClamp = digital_out(Brain.ThreeWirePort.A);

controller Controller1 = controller(primary);

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