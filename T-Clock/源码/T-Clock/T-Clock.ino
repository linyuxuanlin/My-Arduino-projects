/*
name:T-Clock
Description: a tiny clock 
IDE version:  1.8.2
Author:  Lin <linyuxuanlin.github.io>
Date:    2016-10-3
*/
#include "U8glib.h"
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"
U8GLIB_SSD1306_128X64 u8g(10, 9, 12, 11, 13);
//这里适用的OLED屏的引脚是：D0,D1,RST,DC
/*接线：
  OLED-Arduino
  D0-D10
  D1-D9
  RST-D13
  DC-D11
*/
RTC_DS1307 RTC;//RTC按照IIC接线
char monthString[37] =
{
  "JanFebMarAprMayJunJulAugSepOctNovDec"
}
;
int  monthIndex[122] =
{
  0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33
}
;
String thisMonth = "";
String thisTime = "";
String thisDay = "";
//用于定义表盘的中心
int clockCentreX = 64;
int clockCentreY = 32;
void draw(void)
{
  u8g.setFont(u8g_font_profont15);
  DateTime now = RTC.now();
  //在底部显示日期
  thisDay = String(now.day(), DEC) + "/";
  thisMonth = "";
  for (int i = 0; i <= 2; i++)
  {
    thisMonth += monthString[monthIndex[now.month() - 1] + i];
  }
  thisDay = thisDay + thisMonth + "/";
  thisDay = thisDay + String(now.year() , DEC);
  const char* newDay = (const char*) thisDay.c_str();
  u8g.drawStr(32, 63, newDay);
  thisTime = "";
  thisTime = String(now.hour()) + ":";
  if (now.minute() < 10)
  {
    thisTime = thisTime + "0";    // 在单数数字前头加个0
  }
  //数字时间
  thisTime = thisTime + String(now.minute()) ;
  const char* newTime = (const char*) thisTime.c_str();
  u8g.drawStr(10, 10, newTime);
  //画时钟盘面
  u8g.drawCircle(clockCentreX, clockCentreY, 20); // 外面的大圆
  u8g.drawCircle(clockCentreX, clockCentreY, 2);  // 里面的小圆
  //跳动显示
  for ( int z = 0; z < 360; z = z + 30 )
  {
    //始于0°,止于360°
    float angle = z ;
    angle = (angle / 57.29577951) ;   //化度数为弧度
    int x2 = (clockCentreX + (sin(angle) * 20));
    int y2 = (clockCentreY - (cos(angle) * 20));
    int x3 = (clockCentreX + (sin(angle) * (20 - 5)));
    int y3 = (clockCentreY - (cos(angle) * (20 - 5)));
    u8g.drawLine(x2, y2, x3, y3);
  }
  // 秒针
  float angle = now.second() * 6 ;
  angle = (angle / 57.29577951) ; //化度数为弧度
  int x3 = (clockCentreX + (sin(angle) * (20)));
  int y3 = (clockCentreY - (cos(angle) * (20)));
  u8g.drawLine(clockCentreX, clockCentreY, x3, y3);
  // 分针
  angle = now.minute() * 6 ;
  angle = (angle / 57.29577951) ; //化度数为弧度
  x3 = (clockCentreX + (sin(angle) * (20 - 3)));
  y3 = (clockCentreY - (cos(angle) * (20 - 3)));
  u8g.drawLine(clockCentreX, clockCentreY, x3, y3);
  // 时针
  angle = now.hour() * 30 + int((now.minute() / 12) * 6 )   ;
  angle = (angle / 57.29577951) ; //化度数为弧度
  x3 = (clockCentreX + (sin(angle) * (20 - 11)));
  y3 = (clockCentreY - (cos(angle) * (20 - 11)));
  u8g.drawLine(clockCentreX, clockCentreY, x3, y3);
  //显示自己的定制字符
  u8g.setPrintPos(100, 10);
  u8g.print("Lin");
}
void setup(void)
{
  Serial.begin(9600);
  analogReference(EXTERNAL);
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning())
  {
    Serial.println("RTC is NOT running!");
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}
void loop(void)
{
  u8g.firstPage();
  do
  {
    draw();
  }
  while ( u8g.nextPage() );
  delay(10);
}
