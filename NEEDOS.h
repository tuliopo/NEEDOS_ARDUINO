/**
*	\file		NEEDOS.h
*	\author		TPO
*	\date		16/06/2015
*	\brief		Arquivo responsavel pela criacao de threads.
*	\details	Este arquivo contem a logica de funcionaento das threads
*	\copyright 	GNU V2.0
*/



#ifndef NEEDOS_H
#define NEEDOS_H

#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
//Define the max number of threads used
#define TASKS_MAX_N		10
// Min time in ms. 
#define TASK_TEMP_MIN	1

//This flag needs to be set in the timmer interrupt it gives the OS the ticks.
extern volatile uint8_t NEEDOS_FLAG;
#define NEEDOS_CHECK()	(NEEDOS_FLAG =1)


enum TASK_STATUS_e  {TASK_STATUS_IDLE, TASK_STATUS_RUNNING, TASK_STATUS_STOPPED, TASK_STATUS_END, TASK_STATUS_ABORTED, TASK_STATUS_N_IMPLEMENTED };
enum TASK_REPAET_MODE_e {REPEAT_MODE_OFF =0 , REPEAT_MODE_ON =1};
struct task_s
{
	uint32_t		count_interactions; /**< Number times thread was invoked without being cleared the flag*/
	uint32_t		count;		/**< Actual count value. */
	uint32_t		count_top;	/**< Top value. */
	enum			TASK_STATUS_e	STATUS;		/**< Thread state. */
	uint8_t			repeatFlag;	/**<Thread is single shot. */
	uint16_t		index;		/**< Index and priority of the task. */
	void			(*p2f)(void); /**< Function pointer. */
	uint8_t			timerFlag;
};

		//enum TASK_STATUS_e  {TASK_STATUS_IDLE, TASK_STATUS_RUNNING, TASK_STATUS_STOPPED, TASK_STATUS_END, TASK_STATUS_ABORTED, TASK_STATUS_N_IMPLEMENTED };

void		NEEDOS();
void 		NEEDOS_AVR(uint8_t ocr, uint8_t CS0x);		
void 		needosInit(void);
int8_t		taskRun(void);
int8_t		taskConstruct(void(*p2f)(void), uint32_t dec_ms, uint8_t index, uint8_t repeatFlag);
int8_t		taskIncrement(void);
int8_t		taskChangeTime(uint8_t index, uint32_t dec_ms);
int8_t		taskReset(uint8_t index);
int8_t		taskSleep(uint8_t index);
int8_t		taskWakeup(uint8_t index);
int8_t		taskForce(uint8_t index);
int8_t		taskSetRepeatMode(uint8_t index, uint8_t repeatFlag);
int8_t		needosLoop(void);

int8_t		isTaskRepeatOn(uint8_t index);
int8_t		isTaskRunning(uint8_t index);
int8_t		isTaskStopped(uint8_t index);

 int8_t		taskTimerStart(uint8_t index); //NOT IMPLEMENTED YET
 uint32_t	taskTimerStop(uint8_t index);//NOT IMPLEMENTED YET

enum TASK_STATUS_e taskStatus(uint8_t index);
	
	
#if defined(NEEDOS_PT)
	#define TAREFA_NEEDOS(name)					void name(void)
	#define INICIAR_TAREFA(taskName,timer,index,repeatFlag) taskConstruct(taskName,timer,index,repeatFlag)
	#define ALTERAR_TEMPO_TAREFA(index, ms)			taskChangeTime(index,ms)
	#define RESETAR_TAREFA(idx)					taskReset(idx)
	#define DORMIR_TAREFA(index)				taskSleep(index)
	#define ACORDAR_TAREFA(index)				taskWakeup(index)
	#define ESTA_TAREFA_RODANDO(idx)			isTaskRunning(idx)
	#define ESTA_TAREFA_PARADA(idx)				isTaskStopped(idx)
	#define FORCAR_TAREFA(idx)					taskForce(idx)
	#define CONFIGURAR_MODO_REPETICAO(idx,modo) taskSetRepeatMode(idx,modo)
	#define INVERTER_PINO(toggle)   toggle = !toggle

#elif defined (NEEDOS_ES)
	#define TAREA_NEEDOS(name)					void name(void)
	#define INICIAR_TAREA(taskName,timer,index,repeatFlag) taskConstruct(taskName,timer,index,repeatFlag)
	#define ALTERAR_TIEMPO_TAREA(index, ms)			taskChangeTime(index,ms)
	#define REINICIAR_TAREA(idx)					taskReset(idx)
	#define DORMIR_TAREA(index)				taskSleep(index)
	#define DESPERTAR_TAREA(index)				taskWakeup(index)
	#define ESTA_TAREA_RODANDO(idx)			isTaskRunning(idx)
	#define ESTA_TAREA_DETENIDA(idx)				isTaskStopped(idx)
	#define FORZAR_TAREA(idx)					taskForce(idx)
	#define CONFIGURAR_MODO_REPETICION(idx,modo) taskSetRepeatMode(idx,modo)
	#define INVERTIR_PINO(toggle)   toggle = !toggle
#else 
	
	#define NEEDOS_TASK(name)  void name(void)
	#define TASK_INIT(taskName,timer,index,repeatFlag) taskConstruct(taskName,timer,index,repeatFlag)
	#define TASK_CHANGETIME(idx, ms)		taskChangeTime(idx,ms)
	#define TASK_RESET(idx)					taskReset(idx)
	#define TASK_SLEEP(idx)					taskSleep(idx)
	#define TASK_WAKEUP(idx)				taskWakeup(idx)
	#define TASK_ISRUNNING(idx)				isTaskRunning(idx)
	#define TASK_ISSTOPPED(idx)				isTaskStopped(idx)
	#define TASK_FORCE(idx)					taskForce(idx)
	#define TASK_SET_REPEAT_MODE(idx,mode) taskSetRepeatMode(idx,mode)

	#define TOGGLE_PIN(toggle)  		    toggle = !toggle
	
#endif

#endif /* NEEDOS_H */