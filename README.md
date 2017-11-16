# NEEDOS
This is a simple scheduler developed by me for personal use and now ported to ARDUINO in english, portuguese and spanish version.
More documentation will be added along this week.

Check the examples into the libraries for more info!

## Getting Started

Simple download it and include it as simple arduino library.

### Important info

The system is currently ported only to AVR arduinos that uses ATMEGAS and ATXMEGAS, and it´s currently using TIMER0 with minimun
time stamp of 1ms.

### EASY TO USE

To make it work just import the templates and follow 2 simple steps: <br />
1.  Implement the task with **NEEDOS_TASK**;
2.  Initialize task with **TASK_INIT**

```
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Init NEEDOS
  NEEDOS();

  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  
  //Init task
  TASK_INIT(BLINK_LED1_TASK, 1000,  0,  1); //(NAME, TIME_MS=1000, TASK_ID =0, REPEAT MODE = ON
}

NEEDOS_TASK(BLINK_LED1_TASK)
{
  digitalWrite(led1Pin,led1State);
  Serial.println("Blinking LED1 at each 1000 ms!");
  TOGGLE_PIN(led1State);

}
```
