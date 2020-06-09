/*
  Description:
  IDE version: 1.8.6
  Author: YX Lin @ radiastu.com
  Date: 2018
  note:
*/



void setup() {
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
  //char val = Serial.read();
  //if (-1 != val) {

  digitalWrite( 30 , LOW );
  digitalWrite( 31 , HIGH );
  digitalWrite( 32 , HIGH );
  digitalWrite( 33 , LOW );
  digitalWrite( 34 , LOW );
  digitalWrite( 35 , HIGH );
  digitalWrite( 36 , HIGH );
  digitalWrite( 37 , LOW );

}
