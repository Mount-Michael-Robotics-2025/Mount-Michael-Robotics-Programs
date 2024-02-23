using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor SmallL;
extern motor SmallR;
extern motor FrontL;
extern motor FrontR;
extern motor MidL;
extern motor MidR;
extern motor BackL;
extern motor BackR;
extern motor FlyWheel;
extern digital_out SolenoidPair;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );