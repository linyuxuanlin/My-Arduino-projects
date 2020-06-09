//by YX Lin
#include <AFMotor.h> //L293D 驱动库文件
#include <Servo.h>//舵机库文件

#define SR04_Trig 11
#define SR04_Echo 12

int distance = 0;
int delay_time = 300;
int micro_delay_time = 100;
int pos = 0;
int motor_speed = 200;

AF_DCMotor motor1(1);
AF_DCMotor motor2(4);
AF_DCMotor motor3(3);
AF_DCMotor motor4(2);

Servo myservo;

void setup() {
  Serial.begin(9600);
  myservo.attach(2);
  motor1.setSpeed(motor_speed);
  motor2.setSpeed(motor_speed);
  motor3.setSpeed(motor_speed);
  motor4.setSpeed(motor_speed);
  pinMode(SR04_Trig, OUTPUT);
  pinMode(SR04_Echo, INPUT);
  //serve();
}
void loop() {
  if (Serial.available()) {
    Serial.println("Hello");
    char x = Serial.read();
    if (x == 'W') move_forward();
    if (x == 'S') move_backward();
    if (x == 'D') move_right();
    if (x == 'A') move_left();
    if (x == 'E') right_front();
    if (x == 'Q') left_front();
    if (x == 'C') rotate_right();
    if (x == 'Z') rotate_left();
    if (x == 'X') off();

    if (x == 'F') serve();
    if (x == 'V')sr04(); //超声波测距

    Serial.println("ok");
  }
  delay(5);
}

void move_forward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(delay_time);
  off();
}
void move_backward() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(delay_time);
  off();
}

void move_right() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
  delay(delay_time);
  off();
}
void move_left() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
  delay(delay_time);
  off();
}
void right_front() {
  motor1.run(FORWARD);
  motor2.run(RELEASE);
  motor3.run(FORWARD);
  motor4.run(RELEASE);
  delay(delay_time);
  off();
}
void left_front() {
  motor1.run(RELEASE);
  motor2.run(FORWARD);
  motor3.run(RELEASE);
  motor4.run(FORWARD);
  delay(delay_time);
  off();
}
void rotate_right() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
  delay(micro_delay_time);
  off();
}
void rotate_left() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
  delay(micro_delay_time);
  off();
}
void off() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
void serve() {
  for (pos = 0; pos <= 180; pos += 5) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 5) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
void sr04() {
  digitalWrite(SR04_Trig, LOW); //给Trig发送一个低电平
  delayMicroseconds(2);    //等待 2微妙
  digitalWrite(SR04_Trig, HIGH); //给Trig发送一个高电平
  delayMicroseconds(10);    //等待 10微妙
  digitalWrite(SR04_Trig, LOW); //给Trig发送一个低电平
  distance = ((float(pulseIn(SR04_Echo, HIGH)) * 17 ) / 100); //把回波时间换算成毫米,并减去距离差值

  if (distance < 9999 && distance > 0) {
    Serial.print("测距:");
    Serial.println(distance);
  } else {
    Serial.println("距离过大");
  }
}

