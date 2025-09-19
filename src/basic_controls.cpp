#include "basic_control.h"
#include "main.h"
#include "robot-config.h"



void keybind(){
    intaout();
    intain();
}

void intaout(){
    inta1.spin(fwd, 100, pct);
    inta2.spin(fwd, 100, pct);
}
void intain(){
    inta1.spin(reverse, 100, pct);
    inta2.spin(reverse, 100, pct);
}