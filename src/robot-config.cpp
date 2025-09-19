#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller con;
motor l1 = motor(PORT8, ratio6_1, 1);
motor l2 = motor(PORT9, ratio6_1, 0);
motor l3 = motor(PORT10, ratio6_1, 1);
motor_group leftmo = motor_group(l1, l2, l3);
motor r1 = motor(PORT2, ratio6_1, 0);
motor r2 = motor(PORT3, ratio6_1, 1);
motor r3 = motor(PORT4, ratio6_1, 0);
motor_group rightmo = motor_group(r1, r2, r3);
inertial bob = inertial(PORT18);
motor inta1 = motor(PORT19, ratio6_1, 1); //left
motor inta2 = motor(PORT20, ratio6_1, 1); //right
motor_group intamo = motor_group(inta1, inta2);
//motor pner = motor(PORT13, ratio18_1, 0);
digital_out topCap = digital_out(Brain.ThreeWirePort.A); // 
//digital_out hood = digital_out(Brain.ThreeWirePort.D);


digital_out armLift = digital_out(Brain.ThreeWirePort.H);
digital_out intakeLift = digital_out(Brain.ThreeWirePort.D);
distance tim = distance(PORT13);
rotation ForwardTracker = rotation(PORT17, true);
rotation SidewayTracker = rotation(PORT14, false);

digital_out downRec = digital_out(Brain.ThreeWirePort.B); //

optical colorSen = optical(PORT11);
digital_out puncher = digital_out(Brain.ThreeWirePort.G);
//vision bakchu = vision(PORT7);
// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}
