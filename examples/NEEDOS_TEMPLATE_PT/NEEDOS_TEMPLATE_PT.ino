#define NEEDOS_PT 1
#include <NEEDOS.h>


//****CABEÇALHO NEEDOS ****//
 volatile uint8_t NEEDOS_FLAG;
void (*task_functionP[TASKS_MAX_N])(void);
volatile struct task_s list_task_s[TASKS_MAX_N];
//****FIM DO CABEÇALHO NEEDOS ****//


void setup() {
  // Inicializando serial
  Serial.begin(9600);
  //Inicializando NEEDOS
  NEEDOS();

  //Inicializar tarefa a cada 100ms, prioridade 0 e que se repete para sempre.
  INICIAR_TAREFA(COLOQUE_O_NOME_DA_TAREFA, 100,  0,  1); //(NOME, TEMPO em ms = 1000, ID_TAREFA = 0, MODO DE REPETICAO = LIGADO)
}

//Criando tarefa
TAREFA_NEEDOS(COLOQUE_O_NOME_DA_TAREFA)
{
  Serial.println("EXECUTANDO TAREFA NEEDOS A CADA 100 milesegundos!");
}



//Agora você não precisa mais usar o loop se não quiser
void loop() {
  // put your main code here, to run repeatedly:
  if(needosLoop()<0)
  {
    //Se entrar nesta condição algum problema ocorreu com o sistema.
    Serial.println("Erro de temporizacao do NEEDOS!");
  }
}
