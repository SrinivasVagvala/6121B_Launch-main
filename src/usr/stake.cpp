#include "main.h"

pros::Motor lb(WALLSTAKE);
pros::Rotation ladyBrownRotation(LBROTATION);


// Last angle used to be 160
const int numStates = 3;
int states[numStates] = {0, 37, 150};
int currState = 0;
int target = 0;

void resetLadyBrown() {
    currState = 0;
    ladyBrownRotation.reset_position();
    pros::lcd::print(4, "LB Position: %d", ladyBrownRotation.get_position());
}


int getStakeState() {
    return currState;
}


void nextState() {
    currState += 1;
    if (currState == 3) {
        currState = 0;
    }
    target = states[currState];
}

void setState(int state) {
    currState = state;
}

void setStakeTarget(int targetPos) {
    target = targetPos;
}

void liftControl() {
    // doube kP = 0.9
    double kP = 1.1;
    double error = target - (ladyBrownRotation.get_position() / 100.0);
    double velocity = kP * error;
    pros::lcd::print(3, "LB Error: %f", error);
    if (abs(error) > 13) {
        lb.move(velocity);
    }
    else {
        lb.brake();
        lb.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    }
    
}


void liftTask(void *param) {
    resetLadyBrown();
    while (true) {
        pros::lcd::print(4, "LB Position: %d", ladyBrownRotation.get_position());
        if (!pros::competition::is_autonomous()) {
            if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
                nextState();
                pros::lcd::set_text(5, "State was switched!");
            }
        }
        liftControl();
        pros::delay(20);
    }

}









/*
pros::adi::Pneumatics stake(WALLSTAKE, true, true);


bool stakeUp = false; //false is down, true is up
bool stakeButtPress = false;


int stakeMode = 0; //1 is auto, 0 is opcontrol
int stakeClickTimer = 0;


void setStakeMode(int val){
    stakeMode = val;
}

void setStake(bool state){
    stakeUp = state;
}

void stakeOp(){
    if(master.get_digital(DIGITAL_R2) && !stakeButtPress){
        stakeButtPress = true;
        stakeUp = !stakeUp;
    }
    else if(!master.get_digital(DIGITAL_R2)){
        stakeButtPress = false;
    }
}





void stakeTask(void *parameter){
    stake.extend();
	while (true){

        if(stakeMode == 0){
            stakeOp();
        }

        if(!stakeUp){
            stake.extend();
            //pros::lcd::print(0, "clamp: %d\n", 0);
        }
        else{
            stake.retract(); 
            //pros::lcd::print(0, "release: %d\n", 0);
        }

		pros::delay(20);
	}
}

*/