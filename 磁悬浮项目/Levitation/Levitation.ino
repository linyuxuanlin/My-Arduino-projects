#include <PID_v1.h>
#define IN1 4
#define IN2 3
#define IN3 7
#define IN4 8
#define ENA 6
#define ENB 5
#define BL 2

double Setpoint_X, Input_X, Output_X,X_plus;
double p_X = 1,i_X = 0,d_X = 0.01;
double Setpoint_Y, Input_Y, Output_Y,Y_plus;
double p_Y = 1,i_Y = 0,d_Y = 0.01;

int i,on_put=1;

unsigned long time;

PID PID_X(&Input_X, &Output_X, &Setpoint_X,p_X,i_X,d_X, DIRECT);
PID PID_Y(&Input_Y, &Output_Y, &Setpoint_Y,p_Y,i_Y,d_Y, DIRECT);

char inByte='9',nullByte,run_flag,run_dirict;
float go_step;

void turn_X(int a)
{
  if(a>=0)
  {
    digitalWrite(IN1,1);
    digitalWrite(IN2,0);
    analogWrite(ENA,a);
  }
  else
  {
    a=-a;
    digitalWrite(IN1,0);
    digitalWrite(IN2,1);
    analogWrite(ENA,a);
  }
}

void turn_Y(int a)
{
  if(a>=0)
  {
    digitalWrite(IN3,0);
    digitalWrite(IN4,1);
    analogWrite(ENB,a);
  }
  else
  {
    a=-a;
    digitalWrite(IN3,1);
    digitalWrite(IN4,0);
    analogWrite(ENB,a);
  }
}

void setup()
{
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(BL,OUTPUT);
  digitalWrite(IN1,0);
  digitalWrite(IN2,0);
  digitalWrite(IN3,0);
  digitalWrite(IN4,0);
  analogWrite(ENA,0);
  analogWrite(ENB,0);
  Setpoint_X = 560;//560;
  Setpoint_Y = 560;//560;
  PID_X.SetTunings(p_X,i_X,d_X);
  PID_Y.SetTunings(p_Y,i_Y,d_Y);
  PID_X.SetOutputLimits(-255,255);
  PID_Y.SetOutputLimits(-255,255);
  PID_X.SetSampleTime(5);
  PID_Y.SetSampleTime(5);
  PID_X.SetMode(AUTOMATIC);
  PID_Y.SetMode(AUTOMATIC);
  Serial.begin(9600);
}

void loop()
{  
  Input_X = analogRead(A1);
  Input_Y = analogRead(A0);

  
  
  PID_X.Compute();
  PID_Y.Compute();
  turn_X(Output_X);
  turn_Y(Output_Y);
}
