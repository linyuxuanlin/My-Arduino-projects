#include <WiFi.h>
#include <U8g2lib.h>
#include <ArduinoJson.h>
#include "Icon.h"
#include "OLED_Display.h"
#include "Get_Data.h"
#include "Serial_print.h"
#include "WiFi_Connect.h"

const int pageFlipTime = 1000;      // 设置翻页的时间间隔，单位毫秒
unsigned long displayStartMillis;   // 记录上一次屏幕刷新的时间
const int dataRefreshTime = 600000; // 设置数据刷新的时间间隔，单位毫秒，10 分钟
unsigned long refreshStartMillis;   // 记录上一次数据更新的时间

void setup()
{
  netStartUI("Init...", 0);

  Serial.begin(9600);
  OLEDInit();    // 初始化 OLED 屏幕
  WiFiConnect(); //	WiFi 的初始化和连接
  getWeatherData();

  // serialPrintResult(); // 串口打印 json 数据，for debug

  displayStartMillis = millis(); // 初始化刷新时间
  refreshStartMillis = millis(); // 初始化刷新时间
}

void loop()
{
  if (millis() - refreshStartMillis > dataRefreshTime)
  {
    refreshStartMillis = millis(); // 更新刷新时间
    getWeatherData();
  }

  if (millis() - displayStartMillis > pageFlipTime) // 如果翻页时间间隔到了
  {
    displayStartMillis = millis(); // 更新刷新时间

    for (int dayNum = 0; dayNum < 3; dayNum++)
    {
      u8g2.firstPage();
      do
      {
        const uint8_t *icon;

        int v_code_day_int = atoi(day[dayNum].v_code_day);

        switch (v_code_day_int)
        {
          case 0 && 1 && 2 && 3:
            icon = sunny;
            break;
          case 4:
            icon = cloudy;
            break;
          case 5 && 6 && 7 && 8:
            icon = partlyCloudy;
            break;
          case 9:
            icon = overcast;
            break;
          case 11:
            icon = thunderShower;
            break;
          case 13:
            icon = lightRain;
            break;
          case 14:
            icon = moderateRain;
            break;
          case 15:
            icon = heavyRain;
            break;
          case 20:
            icon = sleet;
            break;
          case 22:
            icon = lightSnow;
            break;
          case 23:
            icon = moderateSnow;
            break;
          case 24:
            icon = heavySnow;
            break;
          default:
            icon = unknown;
            break;
        }

        u8g2.drawXBM(10, 6, 40, 40, icon);

        u8g2.setCursor((24 - u8g2.getUTF8Width(day[dayNum].v_text_day)) / 2 + 16, 60); // 让天气情况居中显示
        u8g2.print(day[dayNum].v_text_day);                                            // 白天天气

        String whichDay;
        switch (dayNum)
        {
          case 0:
            whichDay = "Today";
            break;
          case 1:
            whichDay = "Tomorrow";
            break;
          case 2:
            whichDay = "After Tom";
            break;
        }

        u8g2.setCursor(60, 10);
        u8g2.print(whichDay); // 哪一天

        u8g2.setCursor(60, 30);
        u8g2.print(day[dayNum].v_low); // 当天最低温度(℃)
        u8g2.print("-");
        u8g2.print(day[dayNum].v_high); // 当天最高温度(℃)
        u8g2.print(" C");

        u8g2.setCursor(60, 40);
        u8g2.print("Wind: ");
        u8g2.print(day[dayNum].v_wind_direction); // 风向
        u8g2.print(" L");
        u8g2.print(day[dayNum].v_wind_scale); // 风力等级

        u8g2.setCursor(60, 50);
        u8g2.print("Humi: ");
        u8g2.print(day[dayNum].v_humidity); // 相对湿度(%)
        u8g2.print(" %");

        u8g2.setCursor(60, 60);
        u8g2.print(day[dayNum].v_date); // 日期

      } while (u8g2.nextPage()); // 处理完第一页的内容后进入下一页
      delay(pageFlipTime);       // 等待一段时间再开始下一次循环
    }

    /*
      u8g2.firstPage();  //第二页
      do {
      u8g2.setFont(u8g2_font_profont11_mf);
      u8g2.setCursor(20, 20);
      u8g2.print("page 2");     //设置第二页的显示内容
      } while (u8g2.nextPage());  //处理完第二页的内容后进入下一页
      delay(pageFlipTime);          //等待一段时间再开始下一次循环
    */
  }
}
