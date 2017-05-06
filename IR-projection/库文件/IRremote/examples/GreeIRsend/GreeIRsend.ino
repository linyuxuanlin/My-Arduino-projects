#include "Arduino.h"
#include <IRremote.h>


#ifndef __Gree_h__
#define __Gree_h__

#include <arduino.h>
#include "IRremote.h"

//#define DEBUG 1

class GreeAC
{
  private:
    void sendpresumable();
    void send0();
    void send1();
    void sendGree(byte ircode, byte len);
  public:
    void setstate(byte mode, byte fan, byte temp, byte power);
    void test();
};

extern IRsend irsend;

#endif


void GreeAC::sendpresumable()
{
  irsend.mark(9000);
  irsend.space(4500);
}

void GreeAC::send0()
{
  irsend.mark(560);
  irsend.space(565);
}

void GreeAC::send1()
{
  irsend.mark(560);
  irsend.space(1690);
}

//
void GreeAC::sendGree(byte ircode, byte len)
{
  byte mask = 0x01;
  for(int i = 0;i < len;i++)
  {
    if (ircode & mask)
    {
      send1();
    }
    else
    {
      send0();
    }
    mask <<= 1;
  }
}

void GreeAC::test()
{
  irsend.enableIROut(38);
  sendpresumable();
  sendGree(0x39, 8);
  sendGree(0x0A, 8);
  sendGree(0x20, 8);
  sendGree(0x50, 8);
  sendGree(0x02, 3);
  irsend.mark(560);
  irsend.space(10000);
  irsend.space(10000);
  sendGree(0xff, 8);
  sendGree(0xff, 8);
  sendGree(0xff, 8);
  sendGree(0xff, 8);
  irsend.mark(560);
  irsend.space(0);
}





IRsend irsend;
GreeAC gree;
volatile boolean flag;

void trig()
{
  flag = true;
}

void setup()
{
  Serial.begin(9600);
  flag = false;
  attachInterrupt(0, trig, FALLING);
}

void loop()
{
  if (flag == true)
  {
    gree.test();
    flag = false;
  }
}


