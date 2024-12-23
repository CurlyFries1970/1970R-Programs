using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor FrontL;
extern motor MidL;
extern motor BackL;
extern motor FrontR;
extern motor MidR;
extern motor BackR;

extern motor Belt;
extern motor Intake;

extern motor_group DrivetrainL;
extern motor_group DrivetrainR;
extern motor_group DrivetrainAll;

extern inertial InertialSensor;

extern digital_out GoalClamp;

extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );