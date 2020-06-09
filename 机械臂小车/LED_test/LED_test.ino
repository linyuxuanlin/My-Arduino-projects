#include <Servo.h>

int LED=2;

void setup() {
 Serial.begin(9600);
 pinMode(LED,OUTPUT);
}

void loop() {
  /*
  int LEDstate = Serial.read();
  if (LEDstate = 1){
    digitalWrite(LED,HIGH);
  }
  else if (LEDstate = 0){
    digitalWrite(LED,LOW);
  }

  */
digitalWrite(LED,LOW);
delay(1000);
  digitalWrite(LED,HIGH);
  delay(1000);
}
