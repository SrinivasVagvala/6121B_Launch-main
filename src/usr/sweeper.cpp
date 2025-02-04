#include "main.h"


pros::adi::Pneumatics sweeper (SWEEPER, true, true);


bool sweeperUp = false; //false is down, true is up
bool sweeperButtPress = false;


int sweeperMode = 0; //1 is auto, 0 is opcontrol
int sweeperClickTimer = 0;

void setSweeperMode(int val){
    sweeperMode = val;
}

void setSweeper(bool state){
    sweeperUp = state;
}

void sweeperOp(){
    if(master.get_digital(DIGITAL_X) && !sweeperButtPress){
        sweeperButtPress = true;
        sweeperUp = !sweeperUp;
    }
    else if(!master.get_digital(DIGITAL_X)){
        sweeperButtPress = false;
    }
}





void sweeperTask(void *parameter){
    sweeper.extend();
	while (true){

        if(sweeperMode == 0){
            sweeperOp();
        }

        if(!sweeperUp){
            sweeper.extend();
            //pros::lcd::print(0, "clamp: %d\n", 0);
        }
        else{
            sweeper.retract(); 
            //pros::lcd::print(0, "release: %d\n", 0);
        }

		pros::delay(20);
	}
}