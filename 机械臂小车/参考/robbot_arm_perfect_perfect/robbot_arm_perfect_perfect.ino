#include <Servo.h>

Servo servo_pin_4;
Servo servo_pin_5;
Servo servo_pin_6;
Servo servo_pin_7;
Servo servo_pin_8;
Servo servo_pin_9;

void setup()
{
servo_pin_9.attach(9);
pinMode( 11 , INPUT);
pinMode( 12 , INPUT);
servo_pin_6.attach(6);
servo_pin_8.attach(8);
servo_pin_7.attach(7);
servo_pin_4.attach(4);
servo_pin_5.attach(5);
}

void loop()
{
if (digitalRead( 12))
{
}
else
{
servo_pin_7.write( 180 );
delay( 200 );
servo_pin_6.write( 80 );
delay( 400 );
servo_pin_5.write( 60 );
servo_pin_5.write( 65 );
delay( 100 );
servo_pin_8.write( 90 );
servo_pin_4.write( 90 );
delay( 300 );
servo_pin_9.write( 28 );
}
if (digitalRead( 11))
{
}
else
{
servo_pin_9.write( 100 );
delay( 200 );
servo_pin_5.write( 120 );
servo_pin_6.write( 130 );
servo_pin_7.write( 90 );
servo_pin_8.write( 90 );
servo_pin_4.write( 90 );
}
}


