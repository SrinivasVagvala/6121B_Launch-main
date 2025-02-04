#include "main.h"


pros::adi::Pneumatics frame (FRAME, true, true);


bool frameUp = false; //false is down, true is up
bool frameButtPress = false;


int frameMode = 0; //1 is auto, 0 is opcontrol
int frameClickTimer = 0;

void setFrameMode(int val){
    frameMode = val;
}

void setFrame(bool state){
    frameUp = state;
}


void frameTask(void *parameter){
    frame.extend();
	while (true){


        if(!frameUp){
            frame.extend();
            //pros::lcd::print(0, "clamp: %d\n", 0);
        }
        else{
            frame.retract(); 
            //pros::lcd::print(0, "release: %d\n", 0);
        }

		pros::delay(20);
	}
}