#include "botcontrol.h"
#include "main.h"
#include "robot-config.h"
// #include "odom.h"
using namespace vex;
bool ring_io =false;
// bool blue_io =false;
int pxpos = 480/2;
int pypos = 240/2;
int turningCurve = 5;
int x = 1; //elevation
int push = 0;
int y = 1; //clamp
int push1 = 0;
int z = 1;
int push2 = 0;
int a = 1; //armLift
int push3 = 0;
int b = 1; //downRec
int push4 = 0;
int c = 1; //intakeLift
int push5 = 0;
int d = 1;
int push6 = 0;

bool buttonReleased = false;
bool turningRed = false;

int forwardCurve = 10;
bool forwardRed = false;

bool intaReverse = false;
bool intaForward = false;
bool intaForward2 = false;
bool intaReverse2 = false;

bool redSide = false;
bool blueSide = false;

bool buttonR1pressing = false;

bool colorSorting = true;
int qq = 1;


int curveJoystick(bool red, int input, double t){
  int val = 0;
  if(red){
    val = (std::exp(-t/10)+std::exp((std::abs(input)-100)/10)*(1-std::exp(-t/10))) * input;
  }else{
    //blue
    val = std::exp(((std::abs(input)-100)*t)/1000) * input;
  }
  return val;
}

// float deadband(float input, float width){
//   if(std::fabs(input)<width){
//     return(0);
//   }
//   return(input);
// }

// void intakeControlTask() {
//   colorSen.setLightPower(100,pct);
//   if (controller.ButtonUp.pressing()) {

//   }
// }

void intakeThread() {
  while (1) {
    if (auto_started) {
      wait(10, msec);
      continue;
    }
    
    if(con.ButtonR1.pressing()) {
        // Debounce button press
        while(con.ButtonR1.pressing()) {
            wait(10, msec);
        }
        // Toggle reverse spinning state
        if(intaReverse) {
            inta1.stop(brake);
            inta2.stop(brake);
            intaReverse = false;
            // buttonR1pressing = false;
        } else {
            inta1.spin(reverse, 127, pct);
            inta2.spin(reverse, 127, pct);
            // buttonR1pressing = true;
            intaReverse = true;
            intaForward = false;  // Ensure forward spin is stopped
        }
    } else if(con.ButtonR2.pressing()) {
        // Debounce button press
        while(con.ButtonR2.pressing()) {
            wait(10, msec);
        }

        // Toggle forward spinning state
        if(intaForward) {
            inta1.stop(brake);
            inta2.stop(brake);
            intaForward = false;
        } else {
            if(ring_io){
              inta1.stop(hold);
              wait(30, msec);
            }
            inta1.spin(fwd, 127, pct);
            inta2.spin(fwd, 127, pct);
            intaForward = true;
            intaReverse = false;  // Ensure reverse spin is stopped
        }
    } else {
        // Stop the intake motor if neither button is pressed
        if(!intaForward && !intaReverse) {
            inta1.stop(brake);
            inta2.stop(brake);
        }
    }
    wait(10, msec);
  }
}

int printBB(){
  while(1){
    Brain.Screen.clearScreen();
    // wait(200, msec);
    Brain.Screen.printAt(10,36, "X: %f", chassis.get_X_position() * 2.54);
    Brain.Screen.printAt(10,16, "Y: %f", chassis.get_Y_position() * 2.54);
    Brain.Screen.printAt(220,16, "Heading: %f", chassis.get_absolute_heading());
    // Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    // Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    Brain.Screen.printAt(10, 96, "L1 Temp: %.2f C", l1.temperature(temperatureUnits::celsius));
    Brain.Screen.printAt(10, 116, "L2 Temp: %.2f C", l2.temperature(temperatureUnits::celsius));
    Brain.Screen.printAt(10, 136, "L3 Temp: %.2f C", l3.temperature(temperatureUnits::celsius));

    Brain.Screen.printAt(10, 156, "R1 Temp: %.2f C", r1.temperature(temperatureUnits::celsius));
    Brain.Screen.printAt(10, 176, "R2 Temp: %.2f C", r2.temperature(temperatureUnits::celsius));
    Brain.Screen.printAt(10, 196, "R3 Temp: %.2f C", r3.temperature(temperatureUnits::celsius));

    Brain.Screen.printAt(10, 76, "Inta1 Temp: %.2f C", inta1.temperature(temperatureUnits::celsius));
    Brain.Screen.printAt(10, 56, "Inta2 Temp: %.2f C", inta2.temperature(temperatureUnits::celsius));
    Brain.Screen.printAt(220, 36, "colorSorting = %.2d", colorSorting);
    wait(30,msec);
  }
}

// void colorSorting(){
//   while(1){
//     if (auto_started){
//       wait(10, msec);
//       continue;
//     }

//   }
// }

// bool det_color_;
// int colorSorting(){
//   while(1){
//     double hue = colorSen.hue();

//     if(det_color_){
//       if ((hue >= 210 && hue <= 270)){ // Hue range for blue
//         return ring_io =1;
//       }else{
//         return ring_io =0;
//       }
//     }else{
//       if((hue >= 0 && hue <= 30) || (hue >= 330 && hue <= 359)){ // Hue range for red
//         return ring_io =1;
//       }else{
//         return ring_io =0;
//       }
//     }
//   }
// }


// void colorSorting_(bool det_color){
//   det_color_= det_color;
//   task colorSortingTask(colorSorting);
// }

void redAway(){ //red away 
  while(1){
    int redd = colorSen.hue();
      if(con.ButtonX.pressing() ==  true)
      {
        d++;
      }
      else 
      {
        d = 0;
      }
      if(d == 1)
      {
        waitUntil(!con.ButtonX.pressing());
        if(push6 == 0)
        {
          colorSorting = true;
          con.rumble("-""-");
          push6 = 1;
        }
        else if (push6 == 1)
        {
          colorSorting = false;
          con.rumble("-");
          push6 = 0;
        }
      }  

    if(colorSorting == true){
      if(redd < 30 && redd>0 && colorSen.isNearObject()){
        con.rumble("-");
        // if(tim.objectDistance(mm) < 60){
          // inta1.spin(reverse, 100, pct);      
          wait(150,msec);
          puncher.set(true);
          wait(500,msec);
          puncher.set(false);
          // inta1.spin(reverse,100,pct);
        // }
      }
    } 
    wait(10,msec);
  }
}

void blueAway(){ // blue away
  while(1){
    int bluee = colorSen.hue();
    // colorSorting = false;
      if(con.ButtonX.pressing() ==  true)
      {
        d++;
      }
      else 
      {
        d = 0;
      }
      if(d == 1)
      {
        waitUntil(!con.ButtonX.pressing());
        if(push6 == 0)
        {
          colorSorting = true;
          con.rumble("-""-");
          push6 = 1;
        }
        else if (push6 == 1)
        {
          colorSorting = false;
          con.rumble("-");
          push6 = 0;
        }
      }    
    if(colorSorting == true){
      if(bluee < 300 && bluee>80 && colorSen.isNearObject()){
        con.rumble("-");
        // if(tim.objectDistance(mm) < 60){
          // inta1.spin(reverse, 100, pct);      
          wait(150,msec);
          puncher.set(true);
          wait(500,msec);
          puncher.set(false);
          // inta1.spin(reverse,100,pct);
        // }
      }
    } 
    wait(10,msec);
  }
}

// void neutral(){
//         if(con.ButtonX.pressing() ==  true)
//       {
//         d++;
//       }
//       else 
//       {
//         d = 0;
//       }
//       if(d == 1)
//       {
//         waitUntil(!con.ButtonX.pressing());
//         if(push6 == 0)
//         {
//           colorSorting = false;
//           con.rumble("-");
//           push6 = 1;
//         }
//         else if (push6 == 1)
//         {
//           colorSorting = colorSorting;
//           con.rumble("-""-");
//           push6 = 0;
//         }
//       }
// }

void driver(){
  // colorSen.setLightPower(100,pct);
  // vex::thread redd(redAway);
  // vex::thread bluee(blueAway);


  task intakeTask([] () -> int { intakeThread(); return 1; });
  task printBBTASK(printBB);
  // void colorSorting_(detect_color);
  // set_physical_distances()
  while(1){


      // BlueSide(blueSide);    
      // double turnVal = curveJoystick(false, con.Axis1.position(percent), turningCurve); //Get curvature according to settings [-100,100]
      // double forwardVal = curveJoystick(false, con.Axis3.position(percent), forwardCurve); //Get curvature according to settings [-100,100]

      // double turnVolts = turnVal * 0.12; //Converts to voltage
      // double forwardVolts = forwardVal * 0.12; //Converts to voltage

      // leftmo.spin(forward, forwardVolts + turnVolts, voltageUnits::volt); //Apply Via Voltage
      // rightmo.spin(forward, forwardVolts - turnVolts, voltageUnits::volt);

      // vex::task::sleep(20);

      // if(con.ButtonL2.pressing()){
      //   inta.spin(reverse, 100, pct);
      //  } else if(con.ButtonL1.pressing()){
      //    inta.spin(fwd, 100, pct);
      // } else{
      //   inta.stop(brake);
      // }



    // if(con.ButtonX.pressing()){
    //   pner.spin(reverse, 30, pct);
    // } else if(con.ButtonB.pressing()){
    //   pner.spin(fwd, 30, pct);
    // } else{
    //   pner.stop(hold);
    // }

/////////////////////////////////////////////////////////////////

    // distance sensor
        // double distance = tim.objectDistance(mm);
        
        // // Check if Button X is pressed
        // if(con.ButtonX.pressing() && buttonReleased == false) {
        //     z++;
        //     waitUntil(!con.ButtonX.pressing());  
        //     buttonReleased = true;
        // } else if (!con.ButtonX.pressing()) {
        //     z = 0;  
        //     buttonReleased = false;
        // }
        // // if(con.ButtonX.pressing() == true){
        // //   z++;
        // // } else {
        // //   z = 0;
        // // }

        // if(z == 1) {
        //     if(push2 == 0 && distance < 300) {
        //         // If distance is less than 10 mm, spin the motor forward
        //         inta1.stop(brake);
        //         inta2.stop(brake);
        //         // intaReverse = false;
        //         // intaForward = true;
        //         push2 = 1;
        //     } else if(push2 == 1 && distance >= 300) {
        //         // If distance is greater than or equal to 10 mm, reverse the motor
        //         inta1.spin(reverse, 100, pct);
        //         inta2.spin(reverse, 100, pct);
        //         push2 = 0;
        //     }
        // }

        // if(con.ButtonY.pressing() == true){
        //   z++;
        // } else {
        //   z = 0;
        // }
        // if (z == 1) {
        //   waitUntil(!con.ButtonY.pressing());

        //   if (push2 == 0){
        //     inta1.stop(brake);
        //     inta2.spin(reverse, 100, pct);
        //     push2 = 1;
        //   } else if (push2 == 1){
        //     inta1.spin(reverse, 100, pct);
        //     inta2.spin(reverse, 100, pct);
        //     push2 = 0;
        //   }
        // }
/////////////////////////////////////////////////////////////////

    //elevation button need to change
    // if(con.ButtonDown.pressing() == true)
    //   {
    //     x++;
    //   }
    // else
    //   {
    //     x = 0 ;
    //   }
    // if(x == 1)
    //   {
    //     if(push == 0)
    //     {
    //       downRec.set(true);
    //       push = 1;
    //     }
    //     else if (push == 1)
    //     {
          
    //       downRec.set(false);
          
    //       push = 0;
    //     }
    //   }
    // if(con.ButtonB.pressing() == true)
    //   {
    //     x++;
    //   }
    // else
    //   {
    //     x = 0 ;
    //   }
    // if(x == 1)
    //   {
    //     waitUntil(!con.ButtonB.pressing());
    //     if(push == 0)
    //     {
    //       elevation.set(true);
    //       push = 1;
    //     }
    //     else if (push1 == 1)
    //     {
    //       elevation.set(false);
    //       push = 0;
    //     }
    //   }
  
    //clamp
    if(con.ButtonB.pressing() == true)
      {
        y++;
      }
    else
      {
        y = 0 ;
      }
    if(y == 1)
      {
        waitUntil(!con.ButtonB.pressing());
        if(push1 == 0)
        {
          topCap.set(true);
          push1 = 1;
        }
        else if (push1 == 1)
        {
          topCap.set(false);
          push1 = 0;
        }
      }

    //clamp another button
    if(con.ButtonRight.pressing() == true)
      {
        y++;
      }
    else
      {
        y = 0 ;
      }
    if(y == 1)
      {
        waitUntil(!con.ButtonRight.pressing());
        if(push1 == 0)
        {
          topCap.set(true);
          push1 = 1;
        }
        else if (push1 == 1)
        {
          topCap.set(false);
          push1 = 0;
        }
      }

      //armLift 
      // if(con.ButtonL2.pressing() == true)
      // {
      //   a++;
      // }
      // else
      // {
      //   a = 0 ;
      // }
      // if(a == 1)
      // {
      //   waitUntil(!con.ButtonL2.pressing());
      //   if(push3 == 0)
      //   {
      //     armLift.set(true);
      //     push3 = 1;
      //   }
      //   else if (push3 == 1)
      //   {
      //     armLift.set(false);
      //     push3 = 0;
      //   }
      // }

      //downRec  
      if(con.ButtonDown.pressing() == true)
      {
        b++;
      }
      else
      {
        b = 0 ;
      }
      if(b == 1)
      {
        waitUntil(!con.ButtonDown.pressing());
        if(push4 == 0)
        {
          downRec.set(true);
          push4 = 1;
        }
        else if (push4 == 1)
        {
          downRec.set(false);
          push4 = 0;
        }
      }

      //intake lift  
      // if(con.ButtonL1.pressing() == true)
      // {
      //   c++;
      // }
      // else
      // {
      //   c = 0 ;
      // }
      // if(c == 1)
      // {
      //   waitUntil(!con.ButtonL1.pressing());
      //   if(push5 == 0)
      //   {
      //     intakeLift.set(true);
      //     push5 = 1;
      //   }
      //   else if (push5 == 1)
      //   {
      //     intakeLift.set(false);
      //     push5 = 0;
      //   }
      // }

      // puncher 
      // if(con.ButtonX.pressing() ==  true)
      // {
      //   d++;
      // }
      // else 
      // {
      //   d = 0;
      // }
      // if(d == 1)
      // {
      //   waitUntil(!con.ButtonX.pressing());
      //   if(push6 == 0)
      //   {
      //     colorSorting = false;
      //     con.rumble("-");
      //     push6 = 1;
      //   }
      //   else if (push6 == 1)
      //   {
      //     colorSorting = true;
      //     con.rumble("-""-");
      //     push6 = 0;
      //   }
      // }

/////////////////////////////////////////////////////////////////

      double axis3 = deadband(con.Axis3.position(pct),5);
      double axis1 = deadband(con.Axis1.position(pct),5);
      double turtle = curveJoystick(true, axis3, 20); //20
      double rabbit = curveJoystick(true, axis1, 20);
      double leftVolt = turtle + rabbit;
      double rightVolt = turtle - rabbit;
      double scale = 12.0 / fmax(12.0, fmax(fabs(leftVolt), fabs(rightVolt)));
      leftVolt *= scale;
      rightVolt *= scale;
      if (fabs(leftVolt) < 0.1){
          leftmo.stop(brake);
      } 
      else{
          leftmo.spin(forward, leftVolt, volt);
      }
      if(fabs(rightVolt) < 0.1){
          rightmo.stop(brake);
      }
      else{
          rightmo.spin(forward, rightVolt, volt);
      }

//////////////////////////////////////////////////////////////////////////////
    wait(20, msec);
    }
}