#ifndef _STAKE_HPP_
#define _STAKE_HPP_


void nextState();
void setState(int state);
void liftControl();
void resetLadyBrown();
void liftTask(void *param);
void setStakeTarget(int targetPos);
int getStakeState();

#endif