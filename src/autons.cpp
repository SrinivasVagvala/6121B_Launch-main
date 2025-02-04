#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;

///
// Constants
///
void default_constants() {
  // P, I, D, and Start I

  // kP 20 kD 100 for driving
  // turn in place constants are kP 4 and kD 23.0 and kI 0.05, then 15.0
  chassis.pid_drive_constants_set(11.0, 0.0, 52.5);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.7, 0.0, 24.5, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(7_in, 60);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  //chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  chassis.pid_turn_set(180_deg, TURN_SPEED, true);
  chassis.pid_wait();
}

void tuningDrivePID() {
  toggleColorSensing(false);
  chassis.pid_drive_set(26_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

void tuningTurnPID() {
  toggleColorSensing(false);
  chassis.pid_turn_set(180_deg, TURN_SPEED, true);
  chassis.pid_wait();

}

void blueNegative() {
  toggleColorSensing(false);
  chassis.pid_drive_set(-13_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(29_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setMogo(true);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-172_deg, TURN_SPEED, true);
  chassis.pid_wait();
  setIntake(true);
  chassis.pid_drive_set(26_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_drive_set(-14_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(61_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(14.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(75);
  chassis.pid_drive_set(-5.5_in, DRIVE_SPEED, false);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-65_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(14.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(75);
  chassis.pid_drive_set(-11.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-157.5_deg, TURN_SPEED, true);
  chassis.pid_wait();
  setStack(true);
  chassis.pid_drive_set(37.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_drive_set(15_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(150);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(130_deg, TURN_SPEED, true);
  chassis.pid_wait();
  nextState();
  nextState();
  chassis.pid_drive_set(11_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  
  
}


void launchSoloAWP() {
  chassis.pid_drive_set(-12_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(-90_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setIntake(true);


}

void redPositive() {
  toggleColorSensing(false);
  chassis.pid_drive_set(-13.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(30_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-9_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setMogo(true);
  pros::delay(450);
  chassis.pid_turn_set(-106_deg, TURN_SPEED, true);
  chassis.pid_wait();
  setIntake(true);
  chassis.pid_drive_set(25.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-2.5_in, DRIVE_SPEED, false);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  pros::delay(100);
  chassis.pid_turn_set(170_deg, TURN_SPEED, true);
  chassis.pid_wait();
  setStack(true);
  chassis.pid_drive_set(42_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(700);
  setStack(false);
  pros::delay(100);
  chassis.pid_drive_set(-6_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(115_deg, TURN_SPEED, true);
  chassis.pid_wait();
  setIntake(false);
  nextState();
  nextState();
  chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  /*
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-81_deg, TURN_SPEED, true);
  chassis.pid_wait();
  setStack(false);  
  setIntake(false);
  setFirstIntake(true);
  setIntakeVel(-60);
  pros::delay(150);
  chassis.pid_drive_set(8.75_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setIntake(false);
  pros::delay(300);
  chassis.pid_drive_set(2_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-154_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(40_deg, TURN_SPEED, true);
  chassis.pid_wait();
  */
}

void redNegative() {
  toggleColorSensing(false);
  chassis.pid_drive_set(-13_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(-29_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setMogo(true);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(169_deg, TURN_SPEED, true);
  chassis.pid_wait();
  setIntake(true);
  chassis.pid_drive_set(25_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(75);
  chassis.pid_drive_set(-16_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-54.5_deg, TURN_SPEED, true);
  chassis.pid_wait();
  pros::delay(15);
  chassis.pid_drive_set(15.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(75);
  chassis.pid_drive_set(-6.5_in, DRIVE_SPEED, false);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(60_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(14.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(150);
  chassis.pid_drive_set(-11.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(161.5_deg, TURN_SPEED, true);
  chassis.pid_wait();
  setStack(true);
  chassis.pid_drive_set(38_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(75);
  chassis.pid_drive_set(14.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(75);
  setIntake(false);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(65_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(5.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setStakeTarget(145);
  pros::delay(300);
  chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  //pros::delay(100);
  chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  nextState();
  nextState();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_odom_set({{3.75_in, -9_in}, fwd, 110});
  chassis.pid_wait();
  
}

void bluePositive() {
  chassis.pid_drive_set(-13.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(-29_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-9_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setMogo(true);
  pros::delay(450);
  chassis.pid_turn_set(105_deg, TURN_SPEED, true);
  chassis.pid_wait();
  setIntake(true);
  chassis.pid_drive_set(25_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  pros::delay(350);
  chassis.pid_turn_set(-169_deg, TURN_SPEED, true);
  chassis.pid_wait();
  setStack(true);
  chassis.pid_drive_set(41.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(300);
  setStack(false);
  pros::delay(200);
  chassis.pid_drive_set(16_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-140_deg, TURN_SPEED, true);
  chassis.pid_wait();
  nextState();
  nextState();
  chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  
  /*
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(89.5_deg, TURN_SPEED, true);
  chassis.pid_wait();
  setStack(false);  
  setIntake(false);
  setFirstIntake(true);
  setIntakeVel(-60);
  pros::delay(150);
  chassis.pid_drive_set(6_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setIntake(false);
  setStakeTarget(145);
  pros::delay(300);
  chassis.pid_drive_set(7_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(150_deg, TURN_SPEED, true);
  chassis.pid_wait();
  nextState();
  nextState();
  chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  */
}

void testIntake() {
  setIntake(true);
  pros::delay(3000);
  intakeReady(true);
}


void ringRushRed() {
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_drive_set(40_in, DRIVE_SPEED, true);
  setFrame(true);
  chassis.pid_wait_quick();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-15_deg, TURN_SPEED, false);
  pros::delay(315);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_drive_set(-25_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setFrame(false);
  chassis.pid_drive_set(-15_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-140_deg, TURN_SPEED, false);
  chassis.pid_wait();
  chassis.pid_drive_set(-20_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setMogo(true);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(90_deg, TURN_SPEED, false);
  chassis.pid_wait();
  setIntake(true);
  chassis.pid_drive_set(7.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_drive_set(7.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(15_deg, TURN_SPEED, false);
  chassis.pid_wait();
  chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

void ringRushBlue() {
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_drive_set(40_in, DRIVE_SPEED, true);
  setFrame(true);
  chassis.pid_wait_quick();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(15_deg, TURN_SPEED, false);
  pros::delay(315);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_drive_set(-25_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setFrame(false);
  chassis.pid_drive_set(-15_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(140_deg, TURN_SPEED, false);
  chassis.pid_wait();
  chassis.pid_drive_set(-20_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setMogo(true);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-90_deg, TURN_SPEED, false);
  chassis.pid_wait();
  setIntake(true);
  chassis.pid_drive_set(7.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_drive_set(7.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-15_deg, TURN_SPEED, false);
  chassis.pid_wait();
  chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}


void launchProgSkills() {
  turnOnUnstuck(true);
  setIntake(true);
  pros::delay(400);
  setIntake(false);
  chassis.pid_drive_set(14.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(90_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-17.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setMogo(true);
  pros::delay(50);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-108_deg, TURN_SPEED, true);
  chassis.pid_wait();
  setIntake(true);
  chassis.pid_drive_set(24.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-5_in, DRIVE_SPEED, false);
  chassis.pid_wait();
  pros::delay(110);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-65.5_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(25_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-5_in, DRIVE_SPEED, false);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(77_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(52_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-4_in, DRIVE_SPEED, false);
  chassis.pid_wait();
  pros::delay(100);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_odom_set({{5_in, -25.5_in}, rev, DRIVE_SPEED}, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-73.5_deg, TURN_SPEED, true);
  chassis.pid_wait();
  pros::delay(50);
  setStakeTarget(37);
  turnOnUnstuck(false);
  chassis.pid_drive_set(18.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(1000);
  setIntake(false);
  setStakeTarget(164);
  pros::delay(970);
  chassis.pid_drive_set(3_in, DRIVE_SPEED, false);
  chassis.pid_wait();
  setStakeTarget(0);
  setIntake(true);
  chassis.pid_drive_set(-13_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  turnOnUnstuck(true);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-87_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(45_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(350);
  chassis.pid_drive_set(13_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_drive_set(-23_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(10);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(51.5_deg, TURN_SPEED, true);
  chassis.pid_wait();
  pros::delay(10);
  chassis.pid_drive_set(-7.5_in, DRIVE_SPEED, false);
  chassis.pid_wait();
  chassis.pid_drive_set(22.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(200);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(158.5_deg, TURN_SPEED, true);
  chassis.pid_wait();
  setIntake(false);
  setSecondExtake(true);
  chassis.pid_drive_set(-21_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(35);
  setMogo(false);
  pros::delay(150);
  chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setIntake(false);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-80_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-17.25_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-44_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-28.25_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-28.25_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setMogo(true);
  pros::delay(100);
  setIntake(true);
  chassis.pid_drive_set(-6_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(89_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(23_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-3_in, DRIVE_SPEED, false);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(85_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(26.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-9.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-78.5_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(48_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_odom_set({{-5_in, -25_in}, rev, DRIVE_SPEED}, true);
  chassis.pid_wait();
  pros::delay(10);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(74.5_deg, TURN_SPEED, true);
  chassis.pid_wait();
  pros::delay(50);
  setStakeTarget(37);
  chassis.pid_drive_set(17.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(900);
  setIntake(false);
  setStakeTarget(165);
  pros::delay(970);
  chassis.pid_drive_set(1.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setStakeTarget(0);
  setIntake(true);
  chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(92_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(45_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(190);
  chassis.pid_drive_set(13_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_drive_set(-23_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(10);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-45_deg, TURN_SPEED, true);
  chassis.pid_wait();
  pros::delay(10);
  chassis.pid_drive_set(14.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_drive_set(-9.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-150_deg, TURN_SPEED, true);
  chassis.pid_wait();
  setIntake(false);
  setSecondExtake(true);
  chassis.pid_drive_set(-21_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(35);
  setMogo(false);
}

void progSkills() {
  setIntake(true);
  pros::delay(400);
  setIntake(false);
  chassis.pid_drive_set(13_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(90_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-16_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setMogo(true);
  pros::delay(50);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-110_deg, TURN_SPEED, true);
  chassis.pid_wait();
  setIntake(true);
  chassis.pid_drive_set(18_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(110);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-60_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(74_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(48_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_odom_set({{5_in, -25_in}, rev, DRIVE_SPEED}, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-73.5_deg, TURN_SPEED, true);
  chassis.pid_wait();
  pros::delay(50);
  setStakeTarget(40);
  chassis.pid_drive_set(17.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(900);
  setIntake(false);
  setStakeTarget(155);
  pros::delay(970);
  chassis.pid_drive_set(1.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setStakeTarget(0);
  setIntake(true);
  chassis.pid_drive_set(-13_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-88_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(45_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(180);
  chassis.pid_drive_set(13_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_drive_set(-23_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(10);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(50_deg, TURN_SPEED, true);
  chassis.pid_wait();
  pros::delay(10);
  chassis.pid_drive_set(14.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_drive_set(-9.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(160_deg, TURN_SPEED, true);
  chassis.pid_wait();
  setIntake(false);
  setSecondExtake(true);
  chassis.pid_drive_set(-21_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(35);
  setMogo(false);
  pros::delay(150);
  chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setIntake(false);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-80_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-17.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-40_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-26.25_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-26.25_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setMogo(true);
  pros::delay(100);
  setIntake(true);
  chassis.pid_drive_set(-6_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(90_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(83_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(24.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-7.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-78_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(48_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_odom_set({{-5_in, -28.5_in}, rev, DRIVE_SPEED}, true);
  chassis.pid_wait();
  pros::delay(10);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(73.5_deg, TURN_SPEED, true);
  chassis.pid_wait();
  pros::delay(50);
  setStakeTarget(40);
  chassis.pid_drive_set(17.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(900);
  setIntake(false);
  setStakeTarget(155);
  pros::delay(970);
  chassis.pid_drive_set(1.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  setStakeTarget(0);
  setIntake(true);
  chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(92_deg, TURN_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(45_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(190);
  chassis.pid_drive_set(13_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_drive_set(-23_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(10);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-45_deg, TURN_SPEED, true);
  chassis.pid_wait();
  pros::delay(10);
  chassis.pid_drive_set(14.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_drive_set(-9.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.pid_turn_set(-150_deg, TURN_SPEED, true);
  chassis.pid_wait();
  setIntake(false);
  setSecondExtake(true);
  chassis.pid_drive_set(-21_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  pros::delay(35);
  setMogo(false);
}



void checkColorSensing() {
  setAutoSensing(1);
  toggleColorSensing(true);
  setIntake(true);
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Odom Drive PID
///
void odom_drive_example() {
  // This works the same as pid_drive_set, but it uses odom instead!
  // You can replace pid_drive_set with pid_odom_set and your robot will
  // have better error correction.

  chassis.pid_odom_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Odom Pure Pursuit
///
void odom_pure_pursuit_example() {
  // Drive to 0, 30 and pass through 6, 10 and 0, 20 on the way, with slew
  chassis.pid_odom_set({{{6_in, 10_in}, fwd, DRIVE_SPEED},
                        {{0_in, 20_in}, fwd, DRIVE_SPEED},
                        {{0_in, 30_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  // Drive to 0, 0 backwards
  chassis.pid_odom_set({{0_in, 0_in}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Odom Pure Pursuit Wait Until
///
void odom_pure_pursuit_wait_until_example() {
  chassis.pid_odom_set({{{0_in, 24_in}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait_until_index(1);  // Waits until the robot passes 12, 24
  // Intake.move(127);  // Set your intake to start moving once it passes through the second point in the index
  chassis.pid_wait();
  // Intake.move(0);  // Turn the intake off
}

///
// Odom Boomerang
///
void odom_boomerang_example() {
  chassis.pid_odom_set({{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Odom Boomerang Injected Pure Pursuit
///
void odom_boomerang_injected_pure_pursuit_example() {
  chassis.pid_odom_set({{{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Calculate the offsets of your tracking wheels
///
void measure_offsets() {
  // Number of times to test
  int iterations = 10;

  // Our final offsets
  double l_offset = 0.0, r_offset = 0.0, b_offset = 0.0, f_offset = 0.0;

  // Reset all trackers if they exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->reset();
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->reset();
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->reset();
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->reset();
  
  for (int i = 0; i < iterations; i++) {
    // Reset pid targets and get ready for running an auton
    chassis.pid_targets_reset();
    chassis.drive_imu_reset();
    chassis.drive_sensor_reset();
    chassis.drive_brake_set(MOTOR_BRAKE_HOLD);
    chassis.odom_xyt_set(0_in, 0_in, 0_deg);
    double imu_start = chassis.odom_theta_get();
    double target = i % 2 == 0 ? 90 : 270;  // Switch the turn target every run from 270 to 90

    // Turn to target at half power
    chassis.pid_turn_set(target, 63, ez::raw);
    chassis.pid_wait();
    pros::delay(250);

    // Calculate delta in angle
    double t_delta = util::to_rad(fabs(util::wrap_angle(chassis.odom_theta_get() - imu_start)));

    // Calculate delta in sensor values that exist
    double l_delta = chassis.odom_tracker_left != nullptr ? chassis.odom_tracker_left->get() : 0.0;
    double r_delta = chassis.odom_tracker_right != nullptr ? chassis.odom_tracker_right->get() : 0.0;
    double b_delta = chassis.odom_tracker_back != nullptr ? chassis.odom_tracker_back->get() : 0.0;
    double f_delta = chassis.odom_tracker_front != nullptr ? chassis.odom_tracker_front->get() : 0.0;

    // Calculate the radius that the robot traveled
    l_offset += l_delta / t_delta;
    r_offset += r_delta / t_delta;
    b_offset += b_delta / t_delta;
    f_offset += f_delta / t_delta;
  }

  // Average all offsets
  l_offset /= iterations;
  r_offset /= iterations;
  b_offset /= iterations;
  f_offset /= iterations;

  // Set new offsets to trackers that exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->distance_to_center_set(l_offset);
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->distance_to_center_set(r_offset);
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->distance_to_center_set(b_offset);
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->distance_to_center_set(f_offset);
}

// . . .
// Make your own autonomous functions here!
// . . .