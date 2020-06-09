#include <PID_v1.h>
#include <LCD5110_CN.h>
#define IN1 4
#define IN2 3
#define IN3 8
#define IN4 7
#define ENA 6
#define ENB 5
#define BL 2
 
 
LCD5110 myGLCD(9,10,11,13,12);
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];
 
double Setpoint_X, Input_X, Output_X,X_plus; 
double p_X = 1,i_X = 0,d_X = 0.01;
double Setpoint_Y, Input_Y, Output_Y,Y_plus; 
double p_Y = 1,i_Y = 0,d_Y = 0.01;
int i,on_put;
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
  myGLCD.InitLCD();
  myGLCD.setFont(BigNumbers);
 
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
 
  Serial.begin(115200);
 
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
}
 
void loop()
{
  while (Serial.available() > 0)  
  {
    nullByte= char(Serial.read());
    if(nullByte == 'w')
    {
      Setpoint_X+=10;
      //inByte =Serial.read();
    }
    else if(nullByte == 'q')
    {
      Setpoint_X-=10;
    }
    else if(nullByte == 's')
    {
      Setpoint_Y+=10;
    }
    else if(nullByte == 'a')
    {
      Setpoint_Y-=10;
    }
    else if(nullByte == 'o')
    {
      run_flag=!run_flag;
      run_dirict = 1;
      Setpoint_X=560;
      Setpoint_Y=560;
    }
    else if(nullByte =='p')
    {
      run_flag=!run_flag;
      run_dirict = 0;
      Setpoint_X=560;
      Setpoint_Y=560;
    }
    else if(nullByte =='x')
    {
      nullByte=char(Serial.read());
      if(nullByte>20)
      {inByte=nullByte;
      Setpoint_X = 10*(inByte-'0')+480;
      }
      nullByte=char(Serial.read());
      if(nullByte>20)
      {inByte=nullByte;
      Setpoint_Y = 10*(inByte-'0')+480;
      }
    }
 
 
    if(Setpoint_X>575)
      Setpoint_X=575;
    if(Setpoint_Y>575)
      Setpoint_Y=575;
    if(Setpoint_X<480)
      Setpoint_X=480;
    if(Setpoint_Y<480)
      Setpoint_Y=480;
    nullByte ='?';
  }
 
  Input_X = analogRead(A1);
  Input_Y = analogRead(A0);
  if(analogRead(A2)<450)
  {
    digitalWrite(BL,1);
    on_put=1;
  }
  else
  {
    digitalWrite(BL,0);
    on_put=0;
  }
 
  i++;
  /*if(i==500)
  {
    Serial.print(inByte);
    Serial.print(",");
    Serial.println(Setpoint_Y);
  }*/
  if(i==1000)
  {
    myGLCD.printNumI(Setpoint_X, RIGHT, 0);
    myGLCD.printNumI(Setpoint_Y, RIGHT, 24);
    i=0;
  }
 
  if(on_put)
  {
    PID_X.Compute();
    PID_Y.Compute();
    turn_X(Output_X+X_plus);
    turn_Y(Output_Y+Y_plus);
 
    if(run_flag)
    {
      if(millis()-time>2)
      {
        time = millis();
        if(run_dirict)
        {
          X_plus = 25*cos(go_step);
          Y_plus = 25*sin(go_step);
        }
        else
        {
          X_plus = 25*sin(go_step);
          Y_plus = 25*cos(go_step);
        }
        go_step+=0.07;
        if(go_step>6.3)
          go_step=0;
      }
    }
  }
  else
  {
    turn_X(0);
    turn_Y(0);
  }
 
  // myGLCD.printNumI(Input_X, RIGHT, 0);
  // myGLCD.printNumI(Input_Y, RIGHT, 24);
  // myPID.SetTunings(kp,ki,kd);  
}
