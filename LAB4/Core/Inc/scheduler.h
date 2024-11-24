/*
 * scheduler.h
 *
 *  Created on: Nov 20, 2024
 *      Author: Admin
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdio.h>
#include <stdint.h>

typedef enum {
	normal,
	oneshot
}sState;

typedef struct
{
	void (*pTask)(void);
	uint32_t 	Delay;
	uint32_t 	Period;
	uint8_t 	RunMe;
	uint8_t 	TaskID;
	sState 		state;
}sTasks;

#define SCH_MAX_TASKS		40

void SCH_Init(void);

void SCH_Add_Task(void (*pFunction)(), uint32_t delay, uint32_t period, sState state);

void SCH_Update(void);

void SCH_Dispatch_Tasks(void);

void SCH_Delete(uint32_t Id);

#endif /* INC_SCHEDULER_H_ */
