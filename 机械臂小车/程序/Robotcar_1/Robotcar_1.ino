//by Lin

#include <Servo.h>

Servo servo_pin_5;
Servo servo_pin_6;
Servo servo_pin_7;
Servo servo_pin_8;
Servo servo_pin_9;

void setup() {

  Serial.begin(9600);
  servo_pin_9.attach(39);
  servo_pin_6.attach(43);
  servo_pin_8.attach(40);
  servo_pin_7.attach(41);
  servo_pin_5.attach(44);
  pinMode( 30 , OUTPUT);
  pinMode( 31 , OUTPUT);
  pinMode( 32 , OUTPUT);
  pinMode( 33 , OUTPUT);
  pinMode( 34 , OUTPUT);
  pinMode( 35 , OUTPUT);
  pinMode( 36 , OUTPUT);
  pinMode( 37 , OUTPUT);
  pinMode( 2  , OUTPUT);
}

void loop() {
  char val = Serial.read();
  if (-1 != val) {
    if ('1' == val) {
      
      servo_pin_8.write( 90 );
      servo_pin_6.write( 90 );
      servo_pin_6.write( 95 );
      delay( 300 );
      servo_pin_5.write( 70 );
      servo_pin_5.write( 75 );
      delay( 300 );
      servo_pin_7.write( 140 );
      delay( 300 );
      servo_pin_9.write( 28 );
    }

    if ('0' == val) {
      servo_pin_9.write( 100 );
      delay( 300 );
      servo_pin_6.write( 90 );
      delay( 100 );
      servo_pin_5.write( 130 );
      delay( 100 );
      servo_pin_7.write( 150 );
    }

    if ('W' == val) {

      digitalWrite( 30 , LOW );
      digitalWrite( 31 , HIGH );
      digitalWrite( 32 , HIGH );
      digitalWrite( 33 , LOW );
      digitalWrite( 34 , LOW );
      digitalWrite( 35 , HIGH );
      digitalWrite( 36 , HIGH );
      digitalWrite( 37 , LOW );
    }



    if ('S' == val) {

      digitalWrite( 30 , HIGH );
      digitalWrite( 31 , LOW );
      digitalWrite( 32 , LOW );
      digitalWrite( 33 , HIGH );
      digitalWrite( 34 , HIGH );
      digitalWrite( 35 , LOW );
      digitalWrite( 36 , LOW );
      digitalWrite( 37 , HIGH );
    }



    if ('A' == val) {

      digitalWrite( 30 , HIGH );
      digitalWrite( 31 , LOW );
      digitalWrite( 32 , LOW );
      digitalWrite( 33 , HIGH );
      digitalWrite( 34 , LOW );
      digitalWrite( 35 , HIGH );
      digitalWrite( 36 , HIGH );
      digitalWrite( 37 , LOW );
    }



    if ('D' == val) {

      digitalWrite( 30 , LOW );
      digitalWrite( 31 , HIGH );
      digitalWrite( 32 , HIGH );
      digitalWrite( 33 , LOW );
      digitalWrite( 34 , HIGH );
      digitalWrite( 35 , LOW );
      digitalWrite( 36 , LOW );
      digitalWrite( 37 , HIGH );
    }


    if ('F' == val) {

      digitalWrite( 30 , LOW );
      digitalWrite( 31 , LOW );
      digitalWrite( 32 , LOW );
      digitalWrite( 33 , LOW );
      digitalWrite( 34 , LOW );
      digitalWrite( 35 , LOW );
      digitalWrite( 36 , LOW );
      digitalWrite( 37 , LOW );
    }

    if ('L' == val) {
      digitalWrite( 2 , HIGH );
    }
    if ('K' == val) {
      digitalWrite( 2 , LOW );
    }

  }
}
