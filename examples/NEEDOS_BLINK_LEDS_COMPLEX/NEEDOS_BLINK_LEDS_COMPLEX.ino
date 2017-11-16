#define NEEDOS_ENG 1 //Keep it for NEEDOS in english.
#include <NEEDOS.h>



//****NEEDOS HEADERS****//
 volatile uint8_t NEEDOS_FLAG;
void (*task_functionP[TASKS_MAX_N])(void);
volatile struct task_s list_task_s[TASKS_MAX_N];
//****END NEEDOS HEADERS****//



bool led1State =0;
bool led2State =0;
int  led1Pin = 3;
int  led2Pin = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Init NEEDOS
  NEEDOS();

  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  
  //Init task
  TASK_INIT(BLINK_LED1_TASK, 1000,  0,  1); //(NAME, 1000ms, ID_TASK =0, REPEAT MODE= ON
  TASK_INIT(BLINK_LED2_TASK, 4000,  1,  0); //(NAME, 1000ms, ID_TASK =1, REPEAT MODE= OFF -> TASK EXECUTE ONLY ONCE AND ENTER SLEEP MODE
  
}

//Create task
NEEDOS_TASK(BLINK_LED1_TASK)
{
  digitalWrite(led1Pin,led1State);
  Serial.println("Blinking LED1 at each 1000 ms!");
  TOGGLE_PIN(led1State);
  TASK_WAKEUP(1);//WAKE UP ID_TASK = 1   
}

NEEDOS_TASK(BLINK_LED2_TASK)
{
  digitalWrite(led2Pin,led2State);
  Serial.println("Blinking LED2 at each 4000 ms!");
  TOGGLE_PIN(led2State);

}


//NO NEED TO USE LOOP, NOW YOU CAN CREATE YOUR OWN TASKS WITH THE RIGHT TIMING.
void loop() {
  // put your main code here, to run repeatedly:
  if(needosLoop()<0)
  {
    Serial.println("Error in NEEDOS!");
  }
}
