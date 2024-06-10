#include <Arduino.h>
#include <stdint.h>
#include <TimerOne.h>

#define sw 11 //puerto de lectura SW

int SWin; //valor del switch ingresa
int SWout; //valor del switch controlado antirebote
int bandera; //Se cumplió el estado de transición
int cont; //Contador para la interrupción
int Intervalo; //tiempo de tolerancia para confirmar el cambio de estados
int SWanterior;

void timerDelay() {
  //Serial.print(cont);
  cont++;
}

void setup(){
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(sw, INPUT_PULLUP);

  //Inicialización
  SWin = 0; // 
  SWout = 0; //
  Intervalo = 50; // En este caso son 50 milisegundos
  cont = 0;
  bandera = 0;
  SWanterior=0;


  Timer1.initialize(1000); // Configura el timer para 1000 microsegundos es igual a 1 milisegundo
                           // Para que sea visual se puede probar con 5 segundos, reemplazar 1000000
  Timer1.attachInterrupt(timerDelay); // Asocia la interrupción a la función retencion
}

void loop() {
  // put your main code here, to run repeatedly:

  SWin = !digitalRead(sw);
  Serial.print("SWin:");
  Serial.println(SWin);
 
 

if (SWin != SWanterior){
cont=0;
bandera = 1;
}

//Segundo estado DOWN->UP
if ((bandera == 1) && (cont == Intervalo)){
  //se cuenta 50ms para confirmar que se quiere cambiar de estado
    //Primer estado DOWN: Comienza en 0
  if ((SWin == 0)){ //bandera = 1 significa que se realizó un cambio
    SWout = 0;
  }
  //Tercer estado UP
  if (SWin == 1){//bandera = 1 significa que se realizó un cambio
    SWout = 1;
  }
  bandera = 0;
  cont=0;
}

if (cont >500){
  cont = 0;
}


  SWanterior = SWin;


  Serial.print("SWout:");
  Serial.println(SWout);
}


