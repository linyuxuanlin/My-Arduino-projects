/*
  Description:
  IDE version: 1.8.6
  Author: YX Lin @ radiastu.com
  Date: 2018
  note: v1 = servo1_vertical_pos
        vertical,horizontal,oblique,bend,parallel,grab
*/

#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;

int delay_time = 100;

//Arm 纵向 vertical
int v1 = 50;
int v3 = 135;
int v5 = 120;
int v7 = 50;

//Arm 横向 horizontal
int h1 = 140;
int h3 = 45;
int h5 = 30;
int h7 = 140;

//Arm 斜向 oblique
int o1 = 105;
int o3 = 90;
int o5 = 75;
int o7 = 95;

//Arm 65°脚 strange
int s1 = 80.5;
int s3 = 110;
int s5 = 95;
int s7 = 75;

//Leg 弯曲 bend
int b2 = 30;
int b4 = 130;
int b6 = 140;
int b8 = 40;

//Leg 垂直 vertical
int v2 = 45;
int v4 = 110;
int v6 = 125;
int v8 = 55;

//Leg 平行 parallel
int p2 = 140;
int p4 = 30;
int p6 = 40;
int p8 = 150;

//Leg 抓地 grab
int g2 = 80;
int g4 = 80;
int g6 = 90; 
int g8 = 100;

void setup() {
  Serial.begin(9600);
  servo1.attach(11);
  servo2.attach(10);
  servo3.attach(9);
  servo4.attach(8);
  servo5.attach(7);
  servo6.attach(6);
  servo7.attach(5);
  servo8.attach(4);
  //pos();
  stand();
  Serial.println("hello");
}

void loop() {
  //pos();
  //sleep();

  char i = Serial.read();
  if (-1 != i) {
    if (i == 'p') {
      pos();
      Serial.println("pos");
    }
    else if (i == 'o') {
      sleep();
      Serial.println("sleep");
    }
    else if (i == 'l') {
      stand();
      Serial.println("stand");
    }
    else if (i == 'w') {
      walk_forward();
      Serial.println("walk_forward");
    }
    else if (i == 's') {
      walk_backward();
      Serial.println("walk_backward");
    }
    /*
    else if (i == 'a') {
      walk_forward();
      Serial.println("walk_left");
    }
    else if (i == 'd') {
      walk_backward();
      Serial.println("walk_right");
    }
    */
    else if (i == 'q') {
      rotate_left();
      Serial.println("rotate_left");
    }
    else if (i == 'e') {
      rotate_right();
      Serial.println("rotate_right");
    }
  }
}

void walk_forward() {
  pos();
  
  //场景1
  servo8.write(p8);  
  delay(delay_time);
  servo7.write(h7);  
  delay(delay_time);
  servo8.write(g8);  
  delay(delay_time);

  servo4.write(p4);  
  delay(delay_time);
  servo3.write(s3);  
  delay(delay_time);
  servo4.write(g4);  
  delay(delay_time);


  //场景2
  servo1.write(h1);servo3.write(o3);servo5.write(s5);servo7.write(o7);
  delay(delay_time);


  //场景3
  servo6.write(p6);  
  delay(delay_time);
  servo5.write(h5);  
  delay(delay_time);
  servo6.write(g6);  
  delay(delay_time);

  servo2.write(p2);  
  delay(delay_time);
  servo1.write(s1);  
  delay(delay_time);
  servo2.write(g2);  
  delay(delay_time);


  //场景4
  servo1.write(o1);servo3.write(h3);servo5.write(o5);servo7.write(s7);
  delay(delay_time);


  //回归
  servo4.write(p4);  
  delay(delay_time);
  servo3.write(o3);  
  delay(delay_time);
  servo4.write(g4);  
  delay(delay_time);

  servo8.write(p8);  
  delay(delay_time);
  servo7.write(o7);  
  delay(delay_time);
  servo8.write(g8);  
  delay(delay_time);

  
}
void walk_backward() {
  
}

/*老版本
void walk_forward() {
  pos();
  
  servo8.write(p8);   
  delay(delay_time);
  servo7.write(h7);
  delay(delay_time);
  servo8.write(g8);
  delay(delay_time);

  servo4.write(p4);   servo6.write(p6);
  delay(delay_time);
  servo1.write(h1);    servo7.write(o7);
  delay(delay_time);
  servo4.write(g4);   servo6.write(g6);
  delay(delay_time);

  servo2.write(p2);   
  delay(delay_time);
  servo1.write(o1);   
  delay(delay_time);
  servo2.write(g2);   
  delay(delay_time);

  delay(delay_time);
  
  servo6.write(p6);   
  delay(delay_time);
  servo5.write(h5);   
  delay(delay_time);
  servo6.write(g6);   
  delay(delay_time);

  servo2.write(p2);   servo8.write(p8);
  delay(delay_time);
  servo3.write(h3);    servo5.write(o5);
  delay(delay_time);
  servo2.write(g2);   servo8.write(g8);
  delay(delay_time); 

  servo4.write(p4);   
  delay(delay_time);
  servo3.write(o3);   
  delay(delay_time);
  servo4.write(g4);   
  delay(delay_time);
  
}

void walk_backward() {
  pos();
  
  servo2.write(p2);   
  delay(delay_time);
  servo1.write(h1);
  delay(delay_time);
  servo2.write(g2);
  delay(delay_time);

  servo4.write(p4);   servo6.write(p6);
  delay(delay_time);
  servo7.write(h7);    servo1.write(o1);
  delay(delay_time);
  servo4.write(g4);   servo6.write(g6);
  delay(delay_time);

  servo8.write(p8);   
  delay(delay_time);
  servo7.write(o7);   
  delay(delay_time);
  servo8.write(g8);   
  delay(delay_time);

  delay(delay_time);
  
  servo4.write(p4);   
  delay(delay_time);
  servo3.write(h3);   
  delay(delay_time);
  servo4.write(g4);   
  delay(delay_time);

  servo2.write(p2);   servo8.write(p8);
  delay(delay_time);
  servo5.write(h5);    servo3.write(o3);
  delay(delay_time);
  servo2.write(g2);   servo8.write(g8);
  delay(delay_time); 

  servo6.write(p6);   
  delay(delay_time);
  servo5.write(o5);   
  delay(delay_time);
  servo6.write(g6);   
  delay(delay_time);
}
*/
/*
void walk_right() {
  pos();
  
  servo6.write(p6);   
  delay(delay_time);
  servo5.write(v5);
  delay(delay_time);
  servo6.write(g6);
  delay(delay_time);

  servo2.write(p2);   servo8.write(p8);
  delay(delay_time);
  servo3.write(v3);    servo5.write(o5);
  delay(delay_time);
  servo2.write(g2);   servo8.write(g8);
  delay(delay_time);

  servo4.write(p4);   
  delay(delay_time);
  servo3.write(o3);   
  delay(delay_time);
  servo4.write(g4);   
  delay(delay_time);

  delay(delay_time);
  
  servo2.write(p2);   
  delay(delay_time);
  servo1.write(v1);   
  delay(delay_time);
  servo2.write(g2);   
  delay(delay_time);

  servo4.write(p4);   servo6.write(p6);
  delay(delay_time);
  servo7.write(v7);    servo1.write(o1);
  delay(delay_time);
  servo4.write(g4);   servo6.write(g6);
  delay(delay_time); 

  servo8.write(p8);   
  delay(delay_time);
  servo7.write(o7);   
  delay(delay_time);
  servo8.write(g8);   
  delay(delay_time);
}

void walk_left() {
  pos();
  
  servo4.write(p4);   
  delay(delay_time);
  servo3.write(v3);
  delay(delay_time);
  servo4.write(g4);
  delay(delay_time);

  servo2.write(p2);   servo8.write(p8);
  delay(delay_time);
  servo5.write(v5);    servo3.write(o3);
  delay(delay_time);
  servo2.write(g2);   servo8.write(g8);
  delay(delay_time);

  servo6.write(p6);   
  delay(delay_time);
  servo5.write(o5);   
  delay(delay_time);
  servo6.write(g6);   
  delay(delay_time);

  delay(delay_time);
  
  servo8.write(p8);   
  delay(delay_time);
  servo7.write(v7);   
  delay(delay_time);
  servo8.write(g8);   
  delay(delay_time);

  servo4.write(p4);   servo6.write(p6);
  delay(delay_time);
  servo1.write(v1);    servo7.write(o7);
  delay(delay_time);
  servo4.write(g4);   servo6.write(g6);
  delay(delay_time); 

  servo2.write(p2);   
  delay(delay_time);
  servo1.write(o1);   
  delay(delay_time);
  servo2.write(g2);   
  delay(delay_time);
}

*/

void rotate_left() {
  pos();
  
  servo2.write(p2);   servo8.write(p8);
  delay(delay_time);
  servo1.write(h1);   servo7.write(h7); 
  delay(delay_time); 
  servo2.write(g2);   servo8.write(g8);
  delay(delay_time); 

  servo4.write(p4);   servo6.write(p6);
  delay(delay_time);
  servo1.write(o1);    servo7.write(o7);
  delay(delay_time);
  servo4.write(g4);   servo6.write(g6);
  delay(delay_time); 
}

void rotate_right() {
  pos();
  
  servo4.write(p4);   servo6.write(p6);
  delay(delay_time);
  servo3.write(h3);   servo5.write(h5); 
  delay(delay_time); 
  servo4.write(g4);   servo6.write(g6);
  delay(delay_time); 

  servo2.write(p2);   servo6.write(p6);
  delay(delay_time);
  servo3.write(o3);    servo5.write(o5);
  delay(delay_time);
  servo2.write(g2);   servo6.write(g6);
  delay(delay_time); 
}


void pos() {
  servo1.write(o1);
  servo3.write(o3);
  servo5.write(o5);
  servo7.write(o7);

  servo2.write(g2);
  servo4.write(g4);
  servo6.write(g6);
  servo8.write(g8);
}

void stand() {
  servo1.write(o1);
  servo3.write(o3);
  servo5.write(o5);
  servo7.write(o7);

  servo2.write(v2);
  servo4.write(v4);
  servo6.write(v6);
  servo8.write(v8);
}

void sleep() {
  servo1.write(o1);
  servo3.write(o3);
  servo5.write(o5);
  servo7.write(o7);

  servo2.write(p2);
  servo4.write(p4);
  servo6.write(p6);
  servo8.write(p8);
}

void hello() {
  servo1.write(o1);
  servo3.write(o3);
  servo5.write(o5);
  servo7.write(o7);

  servo2.write(p2);
  servo4.write(p4);
  servo6.write(p6);
  servo8.write(p8);
}


