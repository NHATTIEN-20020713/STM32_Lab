/*
 * software_timer.h
 *
 *  Created on: Nov 20, 2023
 *      Author: Administrator
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer_flag;
extern int timer_counter;

void setTimer(int duration);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
