#include "main.h"

pros::Motor intake(INTAKE); // refers to the second stage of the intake
pros::Motor firstIntake(FIRSTINTAKE); 
pros::Optical optical(OPTICAL);

bool intakeOpMode = true; // sets the intake mode and velocties for both intakes
int OP_FIRST_INTAKE_VEL = 125;
int OP_INTAKE_VEL = 120;
bool SENSING = false; // if color sensing is active or not
bool PRESSED = false; // if button has been pressed down
int AUTOSENSING = 0;


bool currentIntakeState = false;

bool intakeUnstuckActive = true;
int intakeStuckTime = 0;
int ladyBrownState = 0;

void turnOnUnstuck(bool state) {
    intakeUnstuckActive = state;
}


void doIntakeUnstuck() {
    ladyBrownState = getStakeState();
    if (fabs(intake.get_actual_velocity()) < 0.5 && fabs(intake.get_voltage()) > 2000 && ladyBrownState == 0) {
        if (intakeStuckTime == 0) {
            intakeStuckTime = pros::millis();
        }
        else if (pros::millis() - intakeStuckTime > 400) {
            master.print(0,0, "This happens");
            master.rumble("-");
            intake.move(OP_INTAKE_VEL);
            pros::delay(200);
            intake.move(-1 * OP_INTAKE_VEL);
            intakeStuckTime = 0;
        }
    }
}


void resetLadyBrownIntake() {
    pros::delay(10);
    intake.move(OP_INTAKE_VEL);
    pros::delay(50);
    intake.move(0);
}

void toggleColorSensing(bool state) {
    SENSING = state;
}

void setIntakeMode(bool mode) { // sets the mode of the intake
    intakeOpMode = mode; 
}

int autonIntakeVelocity = 0;
int autonFirstIntakeVelocity = 0;

void setIntakeVel(int vel) { // sets the velocity of the intake
    autonIntakeVelocity = vel;

}

void setIntake(bool state) { // sets the intake based on the state of the bot
    currentIntakeState = state;
    if (state) {
        autonIntakeVelocity = -OP_INTAKE_VEL;
        autonFirstIntakeVelocity = -OP_FIRST_INTAKE_VEL;
    }
    else {
        autonIntakeVelocity = 0;
        autonFirstIntakeVelocity = 0;
    }
}

void setFirstIntake(bool state) {
    if (state) {
        autonFirstIntakeVelocity = -OP_FIRST_INTAKE_VEL;
    }
    else {
        autonFirstIntakeVelocity = 0;
    }
}

void setSecondIntake(bool state) {
    currentIntakeState = state;
    if (state) {
        autonIntakeVelocity = -OP_INTAKE_VEL;
    }
    else {
        autonIntakeVelocity = 0;
    }
}


void setFirstExtake(bool state) {
    if (state) {
        autonFirstIntakeVelocity = OP_FIRST_INTAKE_VEL;
    }
    else {
        autonFirstIntakeVelocity = 0;
    }
}

void setSecondExtake(bool state) {
    if (state) {
        autonIntakeVelocity = OP_INTAKE_VEL;
    }
    else {
        autonIntakeVelocity = 0;
    }
}


void setAutoSensing(int state) {
    AUTOSENSING = state;
}



void intakeOpControl() { // the intake velocity switches based on which button is being pressed
    if (master.get_digital(DIGITAL_L1)) { // if l1 is pressed the intake moves in the backwards direction
        intake.move(-1 * OP_INTAKE_VEL);
        firstIntake.move(-1 * OP_FIRST_INTAKE_VEL);
    }
    else if (master.get_digital(DIGITAL_L2)) { // if l2 is pressed the intake moves in the forwards direction
        intake.move(OP_INTAKE_VEL);
        firstIntake.move(OP_FIRST_INTAKE_VEL);
    }
    else { // if another button is pressed, the intake doesn't move
        intake.move(0);
        firstIntake.move(0);
    }
}

bool intakeReadyState;

void intakeReady(bool state) {
    intakeReadyState = state;

}

void intakeTask(void* parameter) {
    intake.tare_position();
    while (true) {
        if (!pros::competition::is_autonomous()) { // if the intake is not in the autonomous state ex: op control
            
            // calls functions to get the values from the optical sensor
            double hue = optical.get_hue();
            double sat = optical.get_saturation();
            double bright = optical.get_brightness();
            // benchmark values for each ring, for each parameter
            double bHue = 150.00;
            double bSat = 0.31;
            double bBright = 0;

            double rHue = 11.5;
            double rSat = 0.84; 
            double rBright = 0; 
            // the range that the actual value can deviate from the read value to still be recongnized as the same color
            double blueRange = 85;
            double redRange  = 10; 
        
            double satRange = 0.2;
            double brightRange = 0.2;

            

            if(master.get_digital(DIGITAL_DOWN) && !PRESSED) { // if down arrow is pressed, the color sensing is toggled
                PRESSED = true;
                SENSING = !SENSING;

            }
            else if(!master.get_digital(DIGITAL_DOWN)) {
                PRESSED = false;
            }



            
        
            // printing if the macros are both on
            if (SENSING) {
                //master.print(0,0,"ON ");
            }
            else {
                //master.print(0,0,"OFF");
            }

            

            // if(master.get_digital(DIGITAL_L1) || master.get_digital(DIGITAL_L2)) {
            //     if(abs(intake.get_actual_velocity() - 0) <= 10) {
            //         master.print(2,0,"Velocity%8.2f",intake.get_actual_velocity());
            //         intake.move(-1*OP_INTAKE_VEL);
            //         pros::delay(2);
            //         intake.move(OP_INTAKE_VEL);
            //     }
            //     else {
            //         master.print(2,0,"12345678909IGNORETHIS");
            //     }
            // }



            //master.print(2,0,"Velocity%8.2f",intake.get_actual_velocity());



            
    
            //master.print(2,0,"Hue%8.2f",hue);
            //master.print(2,0,"Sat%8.2f",sat);
            //master.print(2,0,"Bright%8.2f",bright); 
            

            // if the actual values from the color sensor are in the range for blue and it is sensing --- color sesning macro
            if (abs(hue-bHue) <= blueRange && abs(sat-bSat) <= satRange && abs(bright-bBright) <= brightRange && SENSING) { 
                //master.print(2,0,"BLU"); 
                pros::delay(128);
                OP_INTAKE_VEL = 0;
                intake.move(OP_INTAKE_VEL);
                pros::delay(300);
                OP_INTAKE_VEL = 120;
                ;

                
                
            }
            // if the actual values jfrom the color sensor are in the range for red and it is sensing
            else if(abs(hue-rHue) <= redRange && abs(sat-rSat) <= satRange && abs(bright-rBright) <= brightRange && SENSING){
                //master.print(2,0,"RED");
                pros::delay(120);
                OP_INTAKE_VEL = 0;
                intake.move(OP_INTAKE_VEL);
                pros::delay(300);
                OP_INTAKE_VEL = 120;
                ;
            
                
            }
            else {
                //master.print(2,0,"NEI"); 
                ;
            }


        
            //master.print(2,0,"Test%8.2f",optical.get_rgb());
            intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
            intakeOpControl();

            if (intakeUnstuckActive) {
                doIntakeUnstuck();
            }

        }
        else if (pros::competition::is_autonomous()) {
            intake.move(autonIntakeVelocity);
            firstIntake.move(autonFirstIntakeVelocity);

            double hue = optical.get_hue();
            double sat = optical.get_saturation();
            double bright = optical.get_brightness();
            // benchmark values for each ring, for each parameter
            double bHue = 150.00;
            double bSat = 0.31;
            double bBright = 0;

            double rHue = 11.5;
            double rSat = 0.84; 
            double rBright = 0; 
            // the range that the actual value can deviate from the read value to still be recongnized as the same color
            double blueRange = 108;
            double redRange  = 15; 
        
            double satRange = 0.2;
            double brightRange = 0.2;


            if (abs(hue-bHue) <= blueRange && abs(sat-bSat) <= satRange && abs(bright-bBright) <= brightRange && AUTOSENSING == 1 && autonIntakeVelocity != 0) { 
                //master.print(2,0,"BLU"); 
                pros::delay(100);
                autonIntakeVelocity = 0;
                intake.move(autonIntakeVelocity);
                pros::delay(300);
                autonIntakeVelocity = -OP_INTAKE_VEL;
                ;

                
                
            }
            // if the actual values jfrom the color sensor are in the range for red and it is sensing
            else if(abs(hue-rHue) <= redRange && abs(sat-rSat) <= satRange && abs(bright-rBright) <= brightRange && AUTOSENSING == 2 && autonIntakeVelocity != 0){
                //master.print(2,0,"RED");
                pros::delay(95);
                autonIntakeVelocity = 0;
                intake.move(autonIntakeVelocity);
                pros::delay(300);
                autonIntakeVelocity = -OP_INTAKE_VEL;
                ;
            
                
            }
            else {
                //master.print(2,0,"NEI"); 
                ;
            }

            if (intakeUnstuckActive) {
                doIntakeUnstuck();
            }

        }

        pros::delay(20);
    }
}







