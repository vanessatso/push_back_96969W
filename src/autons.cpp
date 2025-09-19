#include "vex.h"

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(6, 1.1, 0, 10, 0);
  chassis.set_heading_constants(5, .4, 0, 2, 0);
  chassis.set_turn_constants(4, .3, .03, 5, 15);
  chassis.set_swing_constants(4, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 100, 2000);
  chassis.set_turn_exit_conditions(1, 100, 1500);
  chassis.set_swing_exit_conditions(1, 100, 500);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void odom_constants(){
  default_constants();
  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 10;
  chassis.drive_settle_error = 3;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
}

/**
 * The expected behavior is to return to the start position.
 */

void drive_test(){
  chassis.drive_distance(6);
  chassis.drive_distance(12);
  chassis.drive_distance(18);
  chassis.drive_distance(-36);
}

/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

/**
 * Should swing in a fun S shape.
 */

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}


double cm2inch(double cm){
  return cm * 0.3937008;
}


// void red_away(){ //red away 
//   colorSen.setLightPower(100,pct);
//     while(1){
//     int reddd = colorSen.hue();
//     if(reddd < 30 && reddd>0 &&colorSen.isNearObject()){
//       con.rumble("-");
//       // if(tim.objectDistance(mm) < 60){
//         // inta1.spin(reverse, 100, pct);      
//         wait(150,msec);
//         puncher.set(true);
//         wait(500,msec);
//         puncher.set(false);
//         // inta1.spin(reverse,100,pct);
//       // }
//     }
//     wait(10,msec);
//   }
// }

// void blue_away(){ //blue away
//   colorSen.setLightPower(100,pct);
//   while(1){
//     int blueee = colorSen.hue();
//     if(blueee < 300 && blueee>80 && colorSen.isNearObject()){
//       con.rumble("-");
//       // if(tim.objectDistance(mm) < 60){
//         // inta1.spin(reverse, 100, pct);      
//         wait(150,msec);
//         puncher.set(true);
//         wait(500,msec);
//         puncher.set(false);
//         // inta1.spin(reverse,100,pct);
//       // }
//     }
//     wait(10,msec);
//   }  
// }

//intake1 write into a function, true or false, if ring_io is true, intake stop 

void red_left(){

  // colorSen.setLightPower(100,pct);
  // vex::thread blueee(blue_away);

  bob.setHeading(210, degrees);
  chassis.turn_max_voltage = 7;
  chassis.drive_max_voltage = 9;
  chassis.drive_distance(cm2inch(-55), 214);
  chassis.drive_max_voltage = 5;

  chassis.drive_distance(cm2inch(-20));
  topCap.set(true);
  wait(200, msec);

  inta1.spin(fwd, -100, pct); 
  inta2.spin(fwd, -100, pct);
  chassis.turn_to_angle(324);
  chassis.drive_distance(cm2inch(45));
  // chassis.turn_to_angle(290);
  chassis.turn_max_voltage = 3;
  chassis.drive_distance(cm2inch(10), 290);
  // chassis.turn_to_angle(282);
  chassis.drive_distance(cm2inch(20), 281);

  wait(100, msec);
  chassis.turn_max_voltage = 6;
  chassis.drive_distance(cm2inch(-24));
  chassis.turn_to_angle(220);
  chassis.drive_distance(cm2inch(30));
  chassis.drive_distance(cm2inch(-7));
  // // wait(500, msec);

  // //ladder
  // chassis.turn_to_angle(56);
  // chassis.drive_max_voltage = 6;
  // chassis.drive_distance(cm2inch(44), 40);
  // chassis.turn_to_angle(48);
  // downRec.set(true);
  // chassis.drive_stop(coast);






  chassis.turn_to_angle(142);
  wait(390, msec);
  chassis.drive_max_voltage = 6;

  armLift.set(true);
  chassis.drive_distance(cm2inch(132), 146.5);//99
  chassis.drive_stop(brake);

  // chassis.drive_distance(cm2inch(7), 143, 100, 100, 0, 0, 250);//99

  armLift.set(false);
  wait(450, msec);

  chassis.drive_distance(cm2inch(-10));
  chassis.turn_to_angle(30);
  chassis.drive_max_voltage = 6;
  chassis.drive_distance(cm2inch(50));
  downRec.set(true);
  chassis.turn_to_angle(5);
  chassis.drive_stop(coast);


  // chassis.drive_distance(cm2inch(-53));

  //eli
    // chassis.turn_to_angle(328);

  // //eli2
  // armLift.set(true);
  // intakeLift.set(true);
  // chassis.turn_to_angle(131);
  // chassis.drive_distance(cm2inch(85));
  // intakeLift.set(false);
  // wait(300, msec);
  // armLift.set(false);
  // wait(400, msec);
  // chassis.drive_distance(cm2inch(-15));
}

void red_right(){

  // colorSen.setLightPower(100,pct);
  // vex::thread blueee(blue_away);


  //wallstake
  bob.setHeading(230, degrees);
  chassis.drive_max_voltage = 5;
  armLift.set(true);
  wait(550, msec);
  chassis.drive_distance(cm2inch(25));
  armLift.set(false);
  wait(200, msec);
  chassis.turn_to_angle(222); 
  wait(200, msec);
  chassis.turn_to_angle(210); 


  //first ring
  chassis.drive_distance(cm2inch(-50));
  chassis.turn_to_angle(250);
  intakeLift.set(true);
  inta2.spin(fwd, -100, pct);
  wait(200, msec);
  chassis.drive_distance(cm2inch(27));
  intakeLift.set(false);
  armLift.set(true);
  wait(525, msec);

  //first mobogo
  chassis.drive_max_voltage = 4;
  chassis.turn_to_angle(226);
  inta2.stop(brake);
  armLift.set(false);
  chassis.drive_distance(cm2inch(-50));
  chassis.drive_max_voltage = 5;
  chassis.drive_distance(cm2inch(-13));
  topCap.set(true);
  inta1.spin(fwd, -100, pct);
  inta2.spin(fwd, -100, pct);
  wait(600, msec);

  //second ring
  chassis.turn_max_voltage = 6;
  chassis.turn_to_angle(90);
  chassis.drive_max_voltage = 8;
  chassis.drive_distance(cm2inch(57));

  //ladder
  chassis.turn_to_angle(277); 
  chassis.drive_max_voltage = 7;
  chassis.drive_distance(cm2inch(85));
  chassis.turn_to_angle(255);
  chassis.drive_stop(coast);
  downRec.set(true);
  chassis.turn_to_angle(251);


  // //elimination
  // chassis.turn_to_angle(160); 
  // chassis.drive_distance(cm2inch(30)); 

  //corner
  // chassis.turn_to_angle(205);
  // chassis.drive_distance(cm2inch(83));
  // inta2.stop(brake);
  // chassis.turn_to_angle(110);
  // downRec.set(true);
  // chassis.drive_distance(cm2inch(55));
  // chassis.turn_to_angle(85);
  // inta2.spin(fwd, -100, pct);
  // downRec.set(false);
  // chassis.drive_distance(cm2inch(17));





////////////////////////////////////////

  // // first mobogo
  // bob.setHeading(0, degrees);
  // chassis.drive_max_voltage = 8;
  // chassis.drive_distance(cm2inch(100));
  // chassis.turn_to_angle(305);
  // downRec.set(true);
  // wait(300, msec); 
  // chassis.turn_max_voltage = 8;
  // chassis.turn_to_angle(257);
  // downRec.set(false);
  // wait(400, msec);
  // chassis.drive_max_voltage = 4;
  // chassis.turn_to_angle(285);
  // chassis.drive_distance(cm2inch(33));
  // chassis.drive_distance(cm2inch(-27));
  // chassis.drive_max_voltage = 3;
  // chassis.turn_max_voltage = 5;
  // chassis.turn_to_angle(105);
  // chassis.drive_distance(cm2inch(-21));
  // wait(104, msec);
  // chassis.drive_max_voltage = 4;
  // chassis.drive_distance(cm2inch(-18));
  // chassis.turn_max_voltage = 5;
  // topCap.set(true);

  // //rings
  // inta1.spin(fwd, -100, pct);
  // inta2.spin(fwd, -100, pct);
  // wait(550, msec);

  // chassis.turn_to_angle(155);
  // chassis.drive_distance(cm2inch(20)); //25
  // topCap.set(false);
  // chassis.drive_distance(cm2inch(15));
  // inta1.stop(brake);
  // inta2.stop(brake);
  // chassis.turn_to_angle(90);
  // chassis.drive_distance(cm2inch(-40));
  // chassis.drive_max_voltage = 3;
  // chassis.drive_distance(cm2inch(-7));
  // inta1.spin(fwd, -100, pct);
  // inta2.spin(fwd, -100, pct);
  // topCap.set(true);
  // chassis.turn_max_voltage = 6;
  // wait(500, msec);  
  // chassis.turn_to_angle(270);
  // chassis.drive_distance(cm2inch(40));
  // chassis.drive_stop(coast);

}

void blue_left(){

  // colorSen.setLightPower(100,pct);
  // vex::thread reddd(red_away);

//  // first mobogo
//   bob.setHeading(180, degrees);
//   chassis.drive_max_voltage = 8;
//   chassis.drive_distance(cm2inch(110));
//   chassis.turn_to_angle(192);
//   downRec.set(true);
//   wait(300, msec); 
//   chassis.turn_max_voltage = 8;
//   chassis.turn_to_angle(257);
//   downRec.set(false);
//   wait(400, msec);
//   chassis.drive_max_voltage = 4;
//   chassis.turn_to_angle(273);
//   chassis.drive_distance(cm2inch(35));
//   chassis.drive_distance(cm2inch(-25));
//   chassis.drive_max_voltage = 3;
//   chassis.turn_max_voltage = 5;
//   chassis.turn_to_angle(99);
//   chassis.drive_distance(cm2inch(-27));
//   chassis.drive_max_voltage = 6;
//   chassis.drive_distance(cm2inch(-20));
//   topCap.set(true);

//   //rings
//   inta1.spin(fwd, -100, pct);
//   inta2.spin(fwd, -100, pct);
//   wait(550, msec);
//   topCap.set(false);
 

//   chassis.turn_to_angle(45);
//   chassis.drive_distance(cm2inch(23)); 
//   topCap.set(false);
//   inta1.stop(brake);
//   inta2.stop(brake);
//   chassis.turn_to_angle(105);
//   chassis.drive_distance(cm2inch(-40));
//   chassis.drive_max_voltage = 3;
//   chassis.drive_distance(cm2inch(-7));
//   inta1.spin(fwd, -100, pct);
//   inta2.spin(fwd, -100, pct);
//   topCap.set(true); 
//   wait(650, msec);
//   chassis.turn_to_angle(280);
//   chassis.drive_distance(cm2inch(25));

///////////////////////////////////////////

  //wallstake
  bob.setHeading(313, degrees);
  chassis.drive_max_voltage = 5;
  armLift.set(true);
  wait(580, msec);
  chassis.drive_distance(cm2inch(23));
  armLift.set(false);
  wait(200, msec);
  chassis.turn_to_angle(320); 

  //first ring
  chassis.drive_distance(cm2inch(-50));
  chassis.turn_to_angle(285);//250
  intakeLift.set(true);
  inta2.spin(fwd, -100, pct);
  wait(200, msec);
  chassis.drive_distance(cm2inch(29));
  intakeLift.set(false);
  armLift.set(true);
  wait(525, msec);

  //first mobogo
  chassis.drive_max_voltage = 4;
  chassis.turn_to_angle(327); //317//331
  armLift.set(false);
  inta2.stop(brake);
  chassis.drive_distance(cm2inch(-38));
  chassis.drive_distance(cm2inch(-25));
  topCap.set(true);
  inta1.spin(fwd, -100, pct);
  inta2.spin(fwd, -100, pct);
  wait(660, msec);

  //second ring
  chassis.turn_max_voltage = 5;
  chassis.turn_to_angle(90);
  chassis.drive_max_voltage = 8;
  chassis.drive_distance(cm2inch(57));

  //ladder
  chassis.turn_to_angle(274);
  inta2.stop(brake);
  chassis.drive_max_voltage = 5;
  chassis.drive_distance(cm2inch(84));
  downRec.set(true);
  chassis.turn_to_angle(200);
  chassis.drive_stop(coast);

  //elimination
  // chassis.turn_to_angle(15);
  // chassis.drive_distance(cm2inch(30));
}

void blue_right(){

  // colorSen.setLightPower(100,pct);
  // vex::thread reddd(red_away);

  bob.setHeading(332, degrees);
  chassis.turn_max_voltage = 7;
  chassis.drive_max_voltage = 10;
  chassis.drive_distance(cm2inch(-57), 331);
  chassis.drive_max_voltage = 6;
  
  chassis.drive_distance(cm2inch(-23));
  topCap.set(true);
  wait(200, msec);

  inta1.spin(fwd, -100, pct);
  inta2.spin(fwd, -100, pct);
  colorSen.setLightPower(100,pct);
  // vex::thread reddd(red_away); 
  chassis.turn_to_angle(218);
  chassis.drive_max_voltage = 7;  
  chassis.drive_distance(cm2inch(32));
  // chassis.turn_to_angle(237);
  chassis.turn_max_voltage = 3;
  chassis.drive_distance(cm2inch(15), 240);
  // chassis.turn_to_angle(264);
  chassis.drive_distance(cm2inch(25), 255);
 

  wait(100, msec);
  chassis.turn_max_voltage = 6;
  chassis.drive_distance(cm2inch(-28), 264);
  chassis.turn_to_angle(315);
  chassis.drive_distance(cm2inch(23));
  chassis.drive_distance(cm2inch(-8));
  // wait(500, msec);


  

  //eli1
  // chassis.turn_to_angle(299);

  // //eli2
  // chassis.turn_to_angle(48);
  // armLift.set(true);
  // intakeLift.set(true);
  // chassis.drive_distance(cm2inch(95));
  // wait(200, msec);
  // intakeLift.set(false);
  // armLift.set(false);
  // wait(200, msec);
  // chassis.drive_distance(cm2inch(-15));




  // //quali
  chassis.turn_to_angle(38);

  chassis.drive_max_voltage = 5;
  wait(400, msec); 
  armLift.set(true);


  chassis.drive_distance(cm2inch(134), 32.5);
  armLift.set(false);
  wait(400, msec); 
  // chassis.drive_stop(coast); 


  chassis.drive_distance(cm2inch(-51));
  // chassis.turn_to_angle(130);
  // chassis.drive_max_voltage = 5;
  // chassis.drive_distance(cm2inch(28));
  // downRec.set(true);
  // chassis.turn_to_angle(100);
  chassis.drive_stop(coast);


  // intakeLift.set(false);

  // wait(300, msec); 


  // chassis.turn_to_angle(17);

  // // inta1.stop(brake);
  // // inta2.stop(brake);

  // chassis.drive_distance(cm2inch(51));

  // armLift.set(false);

  // wait(290, msec);
  // chassis.drive_distance(cm2inch(-30));
  // // chassis.turn_to_angle(90); //elimination


  // chassis.turn_to_angle(177);
  // chassis.drive_distance(cm2inch(50));
  // inta1.stop(brake);
  // inta2.stop(brake);
  // chassis.drive_stop(coast); 
}

void elim_red(){
  // colorSen.setLightPower(100,pct);
  // vex::thread blueee(blue_away);


  bob.setHeading(17, degrees);
  chassis.drive_max_voltage = 8;
  chassis.turn_max_voltage = 8;
  inta1.spin(fwd, -100, pct);
  inta2.spin(fwd, -100, pct);
  chassis.drive_distance(cm2inch(65), 19);
  chassis.drive_distance(cm2inch(18), 352);
  inta1.stop(brake);
  downRec.set(true);

  wait(350, msec); 
  // inta1.stop(brake);
  inta2.stop(brake);
  chassis.drive_max_voltage = 5;
  chassis.turn_max_voltage = 5;
  chassis.drive_distance(cm2inch(-28), 0);
  downRec.set(false);
  wait(200, msec); 
  chassis.turn_to_angle(200);
  chassis.drive_max_voltage = 4;
  chassis.turn_max_voltage = 4;
  chassis.drive_distance(cm2inch(-29), 197);
  topCap.set(true);
  inta1.spin(fwd, -100, pct);
  inta2.spin(fwd, -100, pct);
  wait(650, msec);

  topCap.set(false);
  chassis.drive_max_voltage = 5;
  chassis.turn_max_voltage = 5;
  chassis.drive_distance(cm2inch(6), 197);
  chassis.turn_to_angle(90);
  chassis.drive_max_voltage = 4;
  chassis.drive_distance(cm2inch(-45), 90);
  topCap.set(true);
  chassis.turn_to_angle(207);
  chassis.drive_distance(cm2inch(18), 209);
  wait(200, msec); 

  chassis.drive_max_voltage = 7;
  chassis.turn_max_voltage = 7;
  chassis.drive_distance(cm2inch(-26), 209);
  chassis.turn_to_angle(305);
  inta1.stop(brake);
  inta2.stop(brake); 
  wait(50, msec); 
  chassis.drive_distance(cm2inch(46));
  downRec.set(true);
  wait(370, msec); 
  chassis.turn_max_voltage = 3;
  chassis.drive_distance(cm2inch(-51));
  downRec.set(false);
  wait(400, msec);
  chassis.turn_to_angle(320);
  inta1.spin(fwd, -100, pct);
  inta2.spin(fwd, -100, pct);
  chassis.drive_distance(cm2inch(25));
}

void elim_blue(){
  // colorSen.setLightPower(100,pct);
  // vex::thread reddd(red_away);


  bob.setHeading(164, degrees);
  chassis.drive_max_voltage = 9;
  chassis.turn_max_voltage = 9;
  inta1.spin(fwd, -100, pct);
  inta2.spin(fwd, -100, pct);
  chassis.drive_distance(cm2inch(65), 157);
  chassis.drive_distance(cm2inch(18), 160);
  inta1.stop(brake);
  downRec.set(true);

  wait(300, msec); 
  inta2.stop(brake);
  chassis.drive_max_voltage = 5;
  chassis.turn_max_voltage = 5;
  chassis.drive_distance(cm2inch(-28));
  downRec.set(false);
  wait(200, msec); 
  chassis.turn_to_angle(30);
  chassis.drive_max_voltage = 4;
  chassis.turn_max_voltage = 4;
  chassis.drive_distance(cm2inch(-37), 1);
  topCap.set(true);
  inta1.spin(fwd, -100, pct);
  inta2.spin(fwd, -100, pct);
  wait(600, msec);

  topCap.set(false);
  chassis.drive_max_voltage = 5;
  chassis.turn_max_voltage = 5;
  chassis.drive_distance(cm2inch(17), 1);
  chassis.turn_to_angle(90);
  chassis.drive_max_voltage = 4;
  chassis.drive_distance(cm2inch(-40), 90);
  topCap.set(true);
  chassis.turn_to_angle(13);
  chassis.drive_distance(cm2inch(20));
  wait(200, msec); 

  chassis.drive_max_voltage = 7;
  chassis.turn_max_voltage = 7;
  chassis.turn_to_angle(209);
  chassis.drive_distance(cm2inch(43));
  inta1.stop(brake);
  inta2.stop(brake); 
  chassis.drive_distance(cm2inch(19), 203);

  wait(50, msec); 
  downRec.set(true);
  wait(300, msec); 
  chassis.drive_distance(cm2inch(-30), 209);
  downRec.set(false);
  wait(250, msec); 
  inta1.spin(fwd, -100, pct);
  inta2.spin(fwd, -100, pct);
  chassis.turn_max_voltage = 3;
  chassis.turn_to_angle(217);
  chassis.drive_max_voltage = 8;
  chassis.drive_distance(cm2inch(26));
  chassis.drive_distance(cm2inch(-10));
}

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

/**
 * Should end in the same place it began, but the second movement
 * will be curved while the first is straight.
 */

void tank_odom_test(){
  odom_constants();
  // chassis.set_coordinates(0, 0, 0);
  // //chassis.turn_to_point(24, 24);
  // chassis.drive_to_point(0,94.25);
  // //chassis.turn_to_point(94.25, 94.25);
  // chassis.drive_to_point(94.25,94.25);
  // chassis.turn_to_point(94.25, 0);
  // chassis.drive_to_point(94.25,0); 
  // chassis.turn_to_point(0, 0);
  // chassis.drive_to_point(0,0); 
  // chassis.turn_to_point(0, 94.25);
  //chassis.turn_to_angle(0);
  bob.setHeading(0, degrees);
  chassis.drive_max_voltage = 7;
  chassis.drive_distance(cm2inch(120));
  // chassis.turn_max_voltage = 7;
  // chassis.turn_to_angle(90);
  // chassis.turn_to_angle(0);
  // chassis.turn_to_angle(45);
  // chassis.turn_to_angle(0);



}

/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_pose(0, 18, 90);
  chassis.holonomic_drive_to_pose(18, 0, 180);
  chassis.holonomic_drive_to_pose(0, 18, 270);
  chassis.holonomic_drive_to_pose(0, 0, 0);
}

void auton_skills(){
  // colorSen.setLightPower(100,pct);
  // vex::thread blueee(blue_away);
  // odom_constants();
  // chassis.set_coordinates(0, 0, 0);
  default_constants();
  bob.setHeading(0, degrees);
  chassis.drive_max_voltage = 4;
  chassis.turn_max_voltage = 6;
  // armLift.set(true);
  // wait(300, msec);
  // chassis.drive_distance(cm2inch(15)); 
  // armLift.set(false);
  inta1.spin(fwd, -100, pct);
  inta2.spin(fwd, -100, pct);
  wait(800, msec);
  chassis.drive_distance(cm2inch(28)); 
  chassis.turn_to_angle(-90);
  chassis.drive_max_voltage = 5;
  chassis.drive_distance(cm2inch(-40)); 
  chassis.drive_max_voltage = 4;
  chassis.drive_distance(cm2inch(-12));   
  topCap.set(true);
  wait(200, msec);
  chassis.drive_max_voltage = 8;
  chassis.turn_to_angle(8);
  chassis.drive_distance(cm2inch(50)); 
  chassis.turn_to_angle(80);
  chassis.drive_distance(cm2inch(60)); 
  chassis.turn_to_angle(25);  
  chassis.drive_distance(cm2inch(60), 23); 
  chassis.drive_distance(cm2inch(-10)); 
  chassis.turn_max_voltage = 6;

  chassis.turn_to_angle(-190);

  chassis.drive_distance(cm2inch(85)); 
  chassis.turn_to_angle(-110);
  chassis.drive_distance(cm2inch(15)); 
  chassis.turn_to_angle(-170);
  chassis.drive_distance(cm2inch(19)); 
  chassis.turn_to_angle(-57);//47
  chassis.drive_max_voltage = 6;
  chassis.drive_distance(cm2inch(-30)); //25 
  topCap.set(false);

  inta1.spin(fwd, 100, pct);
  chassis.drive_max_voltage = 7;
  chassis.turn_to_angle(-47);
  inta1.spin(fwd, -100, pct);
  chassis.drive_distance(cm2inch(205), -49);   
  chassis.turn_max_voltage = 5;
  inta1.stop(brake);
  inta2.stop(brake);    
  chassis.turn_to_angle(-140); 
  chassis.drive_distance(cm2inch(110)); 
  chassis.turn_max_voltage = 6;
  chassis.drive_max_voltage = 8;
  chassis.drive_distance(cm2inch(-34)); 
  chassis.turn_to_angle(0);
  chassis.drive_max_voltage = 4;
  chassis.drive_distance(cm2inch(-50)); 
  chassis.drive_max_voltage = 2;
  chassis.turn_max_voltage = 5;
  chassis.turn_to_angle(10);
  chassis.drive_distance(cm2inch(-20),13); 
  // chassis.drive_max_voltage = 4;
  // // chassis.drive_distance(cm2inch(-10), -6); 
  topCap.set(true);
  wait(500, msec);
  inta1.spin(fwd, -100, pct);
  inta2.spin(fwd, -100, pct);
  chassis.drive_max_voltage = 7;

  chassis.turn_max_voltage = 6;
  chassis.turn_to_angle(-85);//54
  chassis.drive_distance(cm2inch(86), -42); //80
  chassis.turn_to_angle(-180);
  chassis.drive_distance(cm2inch(90)); //60
  chassis.turn_to_angle(-60);//80
  chassis.drive_distance(cm2inch(29)); 
  chassis.turn_to_angle(25);
  wait(200, msec);
  topCap.set(false);
  inta1.spin(fwd, 100, pct);
  chassis.drive_distance(cm2inch(-14));  

  chassis.turn_max_voltage = 7;
  chassis.drive_max_voltage = 6;
  chassis.turn_to_angle(15);
  inta1.spin(fwd, -100, pct);
  chassis.drive_distance(cm2inch(165)); 
  chassis.turn_to_angle(35); //
  chassis.drive_distance(cm2inch(62));   
  inta1.stop(brake);
  inta2.stop(brake);      

  chassis.turn_to_angle(-136); //135
  chassis.drive_distance(cm2inch(-45));  
  chassis.turn_max_voltage = 5;
  chassis.turn_to_angle(-143);
  chassis.drive_max_voltage = 5;
  chassis.drive_distance(cm2inch(-25));  
  
  // chassis.drive_max_voltage = 4;
  // // // chassis.drive_distance(cm2inch(-17), -143);  
  // chassis.turn_max_voltage = 4;
  // chassis.turn_to_angle(-160); 
  // chassis.drive_distance(cm2inch(-20));  
  // // chassis.turn_to_angle(-112); 
  // // // bob.setHeading(215, degrees);
  topCap.set(true); 

  wait(300, msec);

  inta1.spin(fwd, -100, pct);
  inta2.spin(fwd, -100, pct);
  chassis.drive_max_voltage = 8;
  chassis.turn_max_voltage = 7;
  chassis.turn_to_angle(135);
  chassis.drive_distance(cm2inch(67));  
  chassis.turn_to_angle(94);
  chassis.drive_max_voltage = 12;
  chassis.drive_distance(cm2inch(75));  
  chassis.turn_to_angle(0);
  chassis.drive_distance(cm2inch(83));  
  wait(100, msec);
  chassis.turn_to_angle(130);
  chassis.drive_distance(cm2inch(25)); 
  chassis.turn_to_angle(200);
  wait(300, msec);
  topCap.set(false);
  inta1.spin(fwd, 100, pct);
  inta2.spin(fwd, 100, pct);      
  chassis.drive_distance(cm2inch(-35));
  chassis.drive_distance(cm2inch(25));
  // leftmo.stop(brake);
  // rightmo.stop(brake);    

  chassis.turn_to_angle(236);
  chassis.drive_distance(cm2inch(34));  
  chassis.turn_to_angle(286);
  chassis.drive_max_voltage = 10;
  chassis.drive_distance(cm2inch(116));  
  inta2.spin(fwd, 100, pct);
  chassis.drive_distance(cm2inch(162), 270);
  inta2.spin(fwd, -100, pct);
  chassis.drive_max_voltage = 8;
  chassis.drive_distance(cm2inch(-47));   
  chassis.turn_to_angle(232);
  chassis.drive_distance(cm2inch(40));  
  chassis.turn_to_angle(130);

  chassis.drive_max_voltage = 6;
  armLift.set(true);
  chassis.drive_distance(cm2inch(120));  
  leftmo.stop(hold);
  rightmo.stop(hold);
  wait(150, msec);
  chassis.drive_max_voltage = 7;
  chassis.drive_distance(cm2inch(60));  
  chassis.drive_max_voltage = 12;
  chassis.drive_distance(cm2inch(-18));  
  leftmo.stop(brake);
  rightmo.stop(brake);

////////

  // inta1.stop(brake);
  // inta2.stop(brake);   
  // chassis.turn_to_angle(268);
  // chassis.drive_distance(cm2inch(-94)); 
  // chassis.turn_to_angle(178);
  // chassis.drive_distance(cm2inch(-40)); 
  // inta1.spin(fwd, -100, pct);
  // inta2.spin(fwd, -100, pct);  
  // // wait(200, msec);
  // leftmo.stop(brake);
  // rightmo.stop(brake);

  //with odom
  
  // odom_constants();
  // chassis.set_coordinates(cm2inch(180), cm2inch(26.5), 0);
  // chassis.drive_max_voltage = 4;
  // inta1.spin(fwd, -100, pct);
  // inta2.spin(fwd, -100, pct);
  // wait(600, msec);
  // chassis.drive_to_point(cm2inch(180), cm2inch(60));
  // // chassis.turn_to_point(cm2inch(180), cm2inch(60));
  // chassis.turn_to_angle(-90);
  // chassis.drive_to_point(cm2inch(230), cm2inch(60));
  // topCap.set(true);
  // wait(200, msec);
  // chassis.drive_max_voltage = 6;
  // chassis.turn_to_angle(8);
  // chassis.drive_to_point(cm2inch(240), cm2inch(120)); 
  // chassis.turn_to_angle(60);
  // chassis.drive_to_point(cm2inch(300), cm2inch(120)); 
  // chassis.right_swing_to_angle(48);
  // chassis.drive_distance(cm2inch(70), 5); 
  // chassis.turn_to_angle(-35);
  // chassis.drive_to_point(cm2inch(300), cm2inch(240)); 
  // inta1.stop(brake);
  // chassis.turn_to_angle(0);
  // chassis.drive_to_point(cm2inch(300), cm2inch(180)); 
  // chassis.turn_to_angle(90);
  // chassis.drive_max_voltage = 4;
  // armLift.set(true); 
  // wait(500, msec);
  // chassis.drive_to_point(cm2inch(314), cm2inch(180)); 
  // armLift.set(false);
  // wait(700, msec);
}






void pb_red_right(){

  default_constants();

  bob.setHeading(0, degrees);
  chassis.turn_max_voltage = 2;
  chassis.drive_max_voltage = 3;
  intamo.spin(fwd, -127, pct);
  chassis.drive_distance (cm2inch(37), -30);
  wait(200, msec);
  chassis.drive_max_voltage = 2;
  chassis.turn_max_voltage = 1;
  chassis.drive_distance(cm2inch(19), -49);
  chassis.drive_distance(cm2inch(20), 3, 127, 50);
  chassis.drive_max_voltage = 8;
  chassis.drive_distance(cm2inch(-55), 55);
  chassis.drive_distance(cm2inch(-5), 180);

  wait(300, msec);

  // chassis.turn_to_angle(90);
  // chassis.turn_to_angle(180);

  // chassis.drive_distance(cm2inch(-30), 40);
  chassis.drive_stop(brake);

  chassis.drive_distance(cm2inch(-10));
  topCap.set(true);
  // wait(200, msec);
  // chassis.turn_to_angle(324);
  // chassis.drive_distance(cm2inch(45));
}

void pb_red_left(){

}

void pb_blue_right(){

}

void pb_blue_left(){

}