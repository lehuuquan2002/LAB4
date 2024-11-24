/*
 * scheduler.c
 *
 *  Created on: Nov 20, 2024
 *      Author: Admin
 */

#include "scheduler.h"
#include <stdint.h>


sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;


void SCH_Init(void)
{
	current_index_task = 0;
}

void SCH_Add_Task(void (*pFunction)(), uint32_t delay, uint32_t period, sState state)
{
	if (current_index_task < SCH_MAX_TASKS)
	{
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = delay/10;
		SCH_tasks_G[current_index_task].Period = period/10;
		SCH_tasks_G[current_index_task].RunMe = 0;
		SCH_tasks_G[current_index_task].TaskID = current_index_task;
		SCH_tasks_G[current_index_task].state = state;
		current_index_task++;
	}
}

void SCH_Update(void)
{
	for (int i = 0; i < current_index_task; i++)
	{
		if (SCH_tasks_G[i].Delay > 0)
		{
			SCH_tasks_G[i].Delay--;
		}else {
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe += 1;
		}
	}
}


void SCH_Dispatch_Tasks(void)
{
	for (int i = 0; i < current_index_task; i++)
	{
		if (SCH_tasks_G[i].RunMe > 0)
		{
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();
			if (SCH_tasks_G[i].state == oneshot)
			{
				SCH_Delete(i);
				i--;
			}
		}
	}
}

void SCH_Delete(uint32_t Id)
{
	if (Id >= current_index_task)
			return;
	for (uint8_t i = Id; i < current_index_task - 1; i++)
	{
		SCH_tasks_G[i].pTask = SCH_tasks_G[i+1].pTask;
		SCH_tasks_G[i].Delay = SCH_tasks_G[i+1].Delay;
		SCH_tasks_G[i].Period = SCH_tasks_G[i+1].Period;
		SCH_tasks_G[i].RunMe = SCH_tasks_G[i+1].RunMe;
		SCH_tasks_G[i].TaskID = SCH_tasks_G[i+1].TaskID;
		SCH_tasks_G[i].state = SCH_tasks_G[i+1].state;
	}

	SCH_tasks_G[current_index_task - 1].pTask = NULL;
	SCH_tasks_G[current_index_task - 1].Delay = 0;
	SCH_tasks_G[current_index_task - 1].Period = 0;
	SCH_tasks_G[current_index_task - 1].RunMe = 0;
	SCH_tasks_G[current_index_task - 1].TaskID = 0;

	current_index_task--;

	return;
}



