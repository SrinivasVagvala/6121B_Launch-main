#include "main.h"


pros::adi::Pneumatics stackPiston (STACK, true, true);
bool stackUp = false; //false is down, true is up
bool stackButtPress = false;


int stackMode = 0; //1 is auto, 0 is opcontrol
int stackClickTimer = 0;

void setStackMode(int val){
    stackMode = val;
}

void setStack(bool state){
    stackUp = state;
}

void stackOp(){
    if(master.get_digital(DIGITAL_RIGHT) && !stackButtPress){
        stackButtPress = true;
        stackUp = !stackUp;
    }
    else if(!master.get_digital(DIGITAL_RIGHT)){
        stackButtPress = false;
    }
}

void stackTask(void *param){
    stackPiston.extend();
	while (true){

        if(stackMode == 0){
            stackOp();
        }

        if(!stackUp){
            stackPiston.extend();
            //pros::lcd::print(0, "clamp: %d\n", 0);
        }
        else{
            stackPiston.retract(); 
            //pros::lcd::print(0, "release: %d\n", 0);
        }

		pros::delay(20);
	}
}