#pragma once
#include "JAR-Template/drive.h"

class Drive;

extern Drive chassis;
extern bool detect_color;

void RedSide();
void BlueSide();

void default_constants();

void drive_test();
void turn_test();
void swing_test();

void red_left();
void red_right();
void blue_left();
void blue_right();
void auton_skills();
void elim_red();
void elim_blue();

void odom_test();
void tank_odom_test();
void holonomic_odom_test();

//for push back 
void pb_red_right();
void pb_red_left();
void pb_blue_right();
void pb_blue_left();


