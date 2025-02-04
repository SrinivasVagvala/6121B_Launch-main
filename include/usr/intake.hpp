#ifndef _INTAKE_HPP_
#define _INTAKE_HPP_


void resetLadyBrownIntake();
void toggleColorSensing(bool state);
void setIntakeMode(bool mode);
void setIntakeVel(int vel);
void setIntake(bool state);
void setFirstIntake(bool state);
void setSecondIntake(bool state);
void setAutoSensing(int state);
void setFirstExtake(bool state);
void setSecondExtake(bool state);
void intakeOpControl();
void intakeTask(void* parameter);

void intakeReady(bool state);

void turnOnUnstuck(bool state);



#endif