/**
*	\file		NEEDOS.cpp
*	\author		TPO
*	\date		16/06/2015
*	\brief		Arquivo responsavel pela criacao de threads.
*	\details	Este arquivo contem a logica de funcionaento das threads
*	\copyright 	GNU V2.0
*/

#include "NEEDOS.h"
extern volatile struct task_s list_task_s[TASKS_MAX_N];
extern void (*task_functionP[TASKS_MAX_N])(void);

void NEEDOS()
{
		#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega88P__)

			NEEDOS_AVR(0x3E,(1<<CS02)); //default for ms min time with timer 0
	
		#endif 

	needosInit();
}
void NEEDOS_AVR(uint8_t ocr, uint8_t CS0x)
{
	#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega88P__)

	// Set the Timer Mode to CTC
	TCCR0A = (1 << WGM01);

	// Set the value that you want to count to
	OCR0A = ocr;

	TIMSK0 = (1 << OCIE0A);    //Set the ISR COMPA vect

	sei();         //enable interrupts


	TCCR0B = CS0x;
	// set prescaler to 256 and start the timer
#endif 

	
	needosInit();

}

int8_t needosLoop(void)
{
	static uint32_t timerOverflow=0;
	timerOverflow++;
	if(NEEDOS_FLAG)
	{
		taskIncrement();
		taskRun();
		NEEDOS_FLAG = 0;
		timerOverflow=0;
	}
	if(timerOverflow>700000)
	{
		timerOverflow=0;
		NEEDOS_FLAG = 0;
		
		return -1;
	}
	return 1;


}

void needosInit()
{
	for(int i=0;i<TASKS_MAX_N;i++)
	{
		list_task_s[i].STATUS =	TASK_STATUS_N_IMPLEMENTED;
	}
}

int8_t taskSleep(uint8_t index)
{
	//if(list_task_s[index].STATUS == TASK_STATUS_RUNNING)
	{
		list_task_s[index].STATUS =	TASK_STATUS_STOPPED;
		return 1;
	}
	//return -1;
}
int8_t taskForce(uint8_t index)
{
	
	
	(*list_task_s[index].p2f)();
	list_task_s[index].count =0;
	list_task_s[index].STATUS = TASK_STATUS_RUNNING;
	return 0;
}
int8_t taskWakeup(uint8_t index)
{
	if(list_task_s[index].STATUS == TASK_STATUS_STOPPED)
	{
	//	task_reset(index);
		list_task_s[index].STATUS =	TASK_STATUS_RUNNING;
		
		return 1;
	}
	else
	return -1;
	
}

int8_t taskConstruct(void(*p2f)(void), uint32_t dec_ms, uint8_t index, uint8_t repeatFlag)
{
	list_task_s[index].STATUS =	TASK_STATUS_IDLE;
	task_functionP[index] = p2f;
	list_task_s[index].p2f = p2f;
	list_task_s[index].count = 0;
	list_task_s[index].count_top = dec_ms;
	list_task_s[index].index = index;
	list_task_s[index].repeatFlag = (uint8_t)repeatFlag;
	list_task_s[index].timerFlag =0;
	return 0;
}

int8_t taskChangeTime(uint8_t index, uint32_t dec_ms)
{
	list_task_s[index].count_top = dec_ms;
	return 0;
}

int8_t taskIncrement(void)
{
	for(int i=0;i<TASKS_MAX_N;i++)
	{
		if(list_task_s[i].STATUS == TASK_STATUS_RUNNING)
		{
			list_task_s[i].count++;
		}
		else if(list_task_s[i].STATUS == TASK_STATUS_IDLE)
		{
			list_task_s[i].STATUS = TASK_STATUS_RUNNING;
			list_task_s[i].count = 0;
		}
	}
	return 0;
}
int8_t taskRun(void)
{
	for(int i=0;i<TASKS_MAX_N;i++)
	{
		if(list_task_s[i].STATUS == TASK_STATUS_RUNNING)
		{
			if(list_task_s[i].count >= list_task_s[i].count_top)
			{
				list_task_s[i].count = 0;
				//(*task_functionP[i])();
				if(isTaskRepeatOn(i) == 0 ) taskSleep(i);
				(*list_task_s[i].p2f)();
				
			}
		}
	}
	return 0;
}
enum TASK_STATUS_e taskStatus(uint8_t index)
{
	return list_task_s[index].STATUS;
}

int8_t isTaskRunning(uint8_t index)
{
	if(list_task_s[index].STATUS == TASK_STATUS_RUNNING)
	return 1;
	else
	return 0;
}

int8_t isTaskStopped(uint8_t index)
{
	if(list_task_s[index].STATUS == TASK_STATUS_STOPPED)
	return 1;
	else
	return 0;
}
int8_t taskReset(uint8_t index)
{
	if(list_task_s[index].STATUS == TASK_STATUS_RUNNING)
	{
		list_task_s[index].count = 0;
		return 1;
	}

	return-1;
}

int8_t taskTimerStart(uint8_t index)
{
	if(isTaskRunning(index))
	{
		return -1;
	}
	else
	{
		taskWakeup(index);
		taskReset(index);
	}
	return 0;
}

uint32_t taskTimerStop(uint8_t index)
{
	if(isTaskRunning(index))
	{
		taskSleep(index);
	}
	else
	{
		
	}
	return list_task_s[index].count;
}

int8_t isTaskRepeatOn(uint8_t index)
{
	return list_task_s[index].repeatFlag ;
}

int8_t taskSetRepeatMode(uint8_t index, enum TASK_REPAET_MODE_e repeatFlag)
{
	list_task_s[index].repeatFlag = (uint8_t)repeatFlag;
	return 0;
}



//**********NEEDOS TIMER**********//
ISR(TIMER0_COMPA_vect)  // timer0 overflow interrupt
{
  NEEDOS_CHECK();
}
//****************************************//

/*
int8_t taskSetasTimer(uint8_t index)
{
	//NOT IMPLEMENTED
}*/
