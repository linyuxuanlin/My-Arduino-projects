#include <Servo.h>

Servo servo_pin_4;
Servo servo_pin_5;
Servo servo_pin_6;
Servo servo_pin_7;
Servo servo_pin_8;
Servo servo_pin_9;

void setup()
{
  Serial.begin(9600);
servo_pin_9.attach(9);
servo_pin_6.attach(6);
servo_pin_8.attach(8);
servo_pin_7.attach(7);
servo_pin_4.attach(4);
servo_pin_5.attach(5);
}

void loop(){
char val = Serial.read();

if (-1 != val) {
if ('1' == val){
servo_pin_4.write( 90 );
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
 
if('0' == val){
servo_pin_9.write( 100 );
delay( 300 );
servo_pin_6.write( 90 );
delay( 100 );
servo_pin_5.write( 130 );
delay( 100 );
servo_pin_7.write( 150 );
}
}

}
