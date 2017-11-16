#define NEEDOS_ES 1
#include <NEEDOS.h>


//****CABEZA NEEDOS ****//
 volatile uint8_t NEEDOS_FLAG;
void (*task_functionP[TASKS_MAX_N])(void);
volatile struct task_s list_task_s[TASKS_MAX_N];
//****FIM DE LA CABEZA NEEDOS ****//


void setup() {
  // Iniciar serial.
  Serial.begin(9600);
  //Iniciar NEEDOS
  NEEDOS();

  //Iniciar tarea a cada 100ms, prioridade 0 e que si repete para siempre.
  INICIAR_TAREA(PONGA_EL_NOMBRE_DE_LA_TAREA, 100,  0,  1); //(NOMBRE, TIEMPO em ms=100, ID_TAREA=0, MODO DE REPETICION = PRENDIDO)
}

//Criando tarefa
TAREA_NEEDOS(PONGA_EL_NOMBRE_DE_LA_TAREA)
{
  Serial.println("EJECUTANDO TAREA NEEDOS A CADA 100ms!");
}



//Ahora si quieres no es mas necesário usar el loop. Ponga mas tareas y sea feliz.
void loop() {
  // put your main code here, to run repeatedly:
  if(needosLoop()<0)
  {
    //Si entrar en esa condiccion quieres decir que algo malo pasó con el sistema operativo.
    Serial.println("Erro de temporizaccion del NEEDOS!");
  }
}
