#include <Arduino.h>
#include <U8g2lib.h> //导入字库
#include <Wire.h>

// OLED 屏幕定义
#define OLED_SDA 1
#define OLED_SCL 0

/*
---显示屏硬件I2C接口---
U8G2_R0 不旋转，横向，绘制方向从左到右
U8G2_R1 顺时针旋转90度，绘制方向从上到下
U8G2_R2 顺时针旋转180度，绘制方向从右到左
U8G2_R3 顺时针旋转270度，绘制方向从下到上
U8G2_MIRROR 正常显示镜像内容（v2.6.x版本以上使用)   注意:U8G2_MIRROR需要与setFlipMode（）配搭使用.
U8x8_PIN_NONE 表示引脚为空，不会使用复位引脚
---显示屏硬件SPI接口---
cs 按引脚接上即可（引脚可自己选择）
dc 按引脚接上即可（引脚可自己选择）
*/

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2,  OLED_SCL, OLED_SDA, /* reset= 8*/U8X8_PIN_NONE);


void setup() {
  Serial.begin(115200);
  u8g2.begin();
  u8g2.setFontPosTop();//使用drawStr显示字符串时，默认标准为显示字符的左下角坐标。本函数的功能可理解为将坐标位置改为显示字符串的左上角为坐标标准。
  //初始化传感器
  Serial.println("hello");
}

void loop() {
  //清理屏幕
  u8g2.clearBuffer();
  //将温度、湿度读取赋值用于显示
  float   temp = 111;
  float   humi = 222;  
  //显示温度
  u8g2.setFont(u8g2_font_osb18_tf);    // 选择字体以及大小（见官方）
  u8g2.drawStr(5,10,"Temp");//在指定位置写出字符
  u8g2.setFont(u8g2_font_t0_18b_tr);
  u8g2.setCursor(75, 15);//显示从该位置开始
  u8g2.print(temp);
  //显示湿度
  u8g2.setFont(u8g2_font_osb18_tf);    
  u8g2.drawStr(5,40,"Humi");
  u8g2.setFont(u8g2_font_t0_18b_tr);
  u8g2.setCursor(75, 45);
  u8g2.print(humi);
  u8g2.sendBuffer(); 
  delay(1000);
}