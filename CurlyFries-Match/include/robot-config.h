using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor FrontL;
extern motor MidL;
extern motor BackL;
extern motor FrontR;
extern motor MidR;
extern motor BackR;
extern digital_out SolenoidPair;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );