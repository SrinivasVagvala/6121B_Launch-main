#include "main.h"


pros::adi::Pneumatics mogo(MOGOMECH, true, true);



bool isMogoClamped = false; //false is out, true is active clamp
bool mogoButtPress = false;

bool autoClampOn = true; 
bool clampButtPress = false; 

int mogoMode = 0; //1 is auto, 0 is opcontrol
int mogoClickTimer = 0; 

void setMogoMode(int val){ // sets the mogo to the value
    mogoMode = val;
}

void setMogo(bool state){ // sets the mogo the state
    isMogoClamped = state;
}

void mogoOp(){
    if(master.get_digital(DIGITAL_B) && !mogoButtPress){
        mogoButtPress = true;
        isMogoClamped = !isMogoClamped;
    }
    else if(!master.get_digital(DIGITAL_B)){
        mogoButtPress = false;
    }

}




void mogoTask(void *param){
    mogo.retract();
	while (true){

        
        if(mogoMode == 0){
            mogoOp();

            if(master.get_digital(DIGITAL_A) && !clampButtPress){
                autoClampOn = !autoClampOn;
                clampButtPress = true; 

            }
            else if(!master.get_digital(DIGITAL_A)){
               clampButtPress = false; 
            }
            
        }

        if(!isMogoClamped){
            mogo.extend();
        }
        else{
            mogo.retract(); 
        }

        

		pros::delay(20);
	}
}