#include <Servo.h> //舵机库
char BluetoothData;
Servo servo1; //创建一个舵机控制类
Servo servo2;
Servo servo3;
Servo servo4;

void setup()
{
  Serial.begin(9600);

  //接线:
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
}

void loop()
{
  if (Serial.available()) {
    BluetoothData = Serial.read();
    if (BluetoothData == 'A')  servo1.write(Serial.parseInt());
    if (BluetoothData == 'B')  servo2.write(Serial.parseInt());
    if (BluetoothData == 'C')  servo3.write(Serial.parseInt());
    if (BluetoothData == 'D')  servo4.write(Serial.parseInt());
  }
  delay(100); //延时一段时间让舵机转动到对应位置
}
