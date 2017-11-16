#define NEEDOS_ENG 1 //Keep it for NEEDOS in english.
#include <NEEDOS.h>



//****NEEDOS HEADERS****//
 volatile uint8_t NEEDOS_FLAG;
void (*task_functionP[TASKS_MAX_N])(void);
volatile struct task_s list_task_s[TASKS_MAX_N];
//****END NEEDOS HEADERS****//


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Init NEEDOS
  NEEDOS();

  //Init task
  TASK_INIT(PUT_TASK_NAME_HERE, 100,  0,  1); //(NAME, TIME_MS=1000, TASK_ID = 0, REPEAT MODE = ON
}

//Create task
NEEDOS_TASK(PUT_TASK_NAME_HERE)
{
  Serial.println("EXECUTING NEEDOS TASK AT EACH 100 milliseconds!");
}



//NO NEED TO USE LOOP, NOW YOU CAN CREATE YOUR OWN TASKS WITH THE RIGHT TIMING.
void loop() {
  // put your main code here, to run repeatedly:
  if(needosLoop()<0)
  {
    Serial.println("Error in NEEDOS!");
  }
}
