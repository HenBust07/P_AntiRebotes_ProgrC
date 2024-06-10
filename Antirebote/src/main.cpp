#include <Arduino.h>
#include <stdint.h>


#define sw 11

int SWctrl; //valor del switch controlado

void setup(){
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(sw, INPUT_PULLUP);
  SWctrl = !digitalRead(sw);


}

void loop() {
  // put your main code here, to run repeatedly:

  SWctrl = !digitalRead(sw);
  delay(1000);
  Serial.print("SW:");
  Serial.println(SWctrl);


}

