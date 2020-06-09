//by Lin

#include <Servo.h>

Servo servo_pin_5;
Servo servo_pin_6;
Servo servo_pin_7;
Servo servo_pin_8;
Servo servo_pin_9;
int i;//servo 9
int p;//servo 7
int k;//servo 6
int o;//servo 5
void setup() {

  Serial.begin(9600);
  servo_pin_9.attach(39, 832, 1575);
  servo_pin_6.attach(43, 544, 2400);
  servo_pin_8.attach(40, 1492, 1493);
  servo_pin_7.attach(41, 1988, 2091);
  servo_pin_5.attach(44, 994 , 1894);
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
  servo_pin_8.write( 90 );
  servo_pin_6.write( 90 );
  if (-1 != val) {

    i = servo_pin_9.read();
    p = servo_pin_7.read();
    o = servo_pin_5.read();
    k = servo_pin_6.read();
    if ('8' == val) {

      i = i + 3;
      servo_pin_9.write( i );

    }


    if ('A' == val) {
      i = i - 3;
      servo_pin_9.write( i );

    }

    if ('9' == val) {

      p = p - 1;
      o = o - 2;
      k = k - 2;
      servo_pin_5.write( o );
      servo_pin_7.write( p );
      servo_pin_8.write( 90 );
      servo_pin_6.write( k );

    }

    if ('7' == val) {

      p = p + 1;
      o = o + 2;
      k = k + 2;
      servo_pin_5.write( o );
      servo_pin_7.write(  p);
      servo_pin_8.write( 90 );
      servo_pin_6.write( k );
    }



    if ('1' == val) {

      digitalWrite( 30 , LOW );
      digitalWrite( 31 , HIGH );
      digitalWrite( 32 , HIGH );
      digitalWrite( 33 , LOW );
      digitalWrite( 34 , LOW );
      digitalWrite( 35 , HIGH );
      digitalWrite( 36 , HIGH );
      digitalWrite( 37 , LOW );
    }




    if ('2' == val) {

      digitalWrite( 30 , HIGH );
      digitalWrite( 31 , LOW );
      digitalWrite( 32 , LOW );
      digitalWrite( 33 , HIGH );
      digitalWrite( 34 , HIGH );
      digitalWrite( 35 , LOW );
      digitalWrite( 36 , LOW );
      digitalWrite( 37 , HIGH );
    }



    if ('3' == val) {

      digitalWrite( 30 , HIGH );
      digitalWrite( 31 , LOW );
      digitalWrite( 32 , LOW );
      digitalWrite( 33 , HIGH );
      digitalWrite( 34 , LOW );
      digitalWrite( 35 , HIGH );
      digitalWrite( 36 , HIGH );
      digitalWrite( 37 , LOW );
    }



    if ('4' == val) {

      digitalWrite( 30 , LOW );
      digitalWrite( 31 , HIGH );
      digitalWrite( 32 , HIGH );
      digitalWrite( 33 , LOW );
      digitalWrite( 34 , HIGH );
      digitalWrite( 35 , LOW );
      digitalWrite( 36 , LOW );
      digitalWrite( 37 , HIGH );
    }


    if ('0' == val) {

      digitalWrite( 30 , LOW );
      digitalWrite( 31 , LOW );
      digitalWrite( 32 , LOW );
      digitalWrite( 33 , LOW );
      digitalWrite( 34 , LOW );
      digitalWrite( 35 , LOW );
      digitalWrite( 36 , LOW );
      digitalWrite( 37 , LOW );
    }

    if ('6' == val) {
      digitalWrite( 2 , HIGH );
    }
    if ('5' == val) {
      digitalWrite( 2 , LOW );
    }

  }

}
