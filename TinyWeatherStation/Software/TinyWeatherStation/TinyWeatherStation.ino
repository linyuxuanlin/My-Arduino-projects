#include <WiFi.h>
#include <U8g2lib.h>
#include <ArduinoJson.h> //注意必须使用 v6 版本的库
#include "Icon.h"
#include "OLED_Display.h"
#include "Get_Weather_Data.h"
#include "Get_Local_Time.h"
#include "Serial_print.h"
#include "WiFi_Connect.h"

const int pageFlipTime = 1000;      // 设置翻页的时间间隔，单位毫秒
unsigned long displayStartMillis;   // 记录上一次屏幕刷新的时间
const int dataRefreshTime = 600000; // 设置数据刷新的时间间隔，单位毫秒，10 分钟
unsigned long refreshStartMillis;   // 记录上一次数据更新的时间

void setup()
{
  netStartUI("Init...", 0);

  Serial.begin(115200);

  OLEDInit();    // 初始化 OLED 屏幕
  WiFiConnect(); //	WiFi 的初始化和连接

  // 从网络时间服务器上获取并设置时间
  // 获取成功后芯片会使用RTC时钟保持时间的更新
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  getWeatherData();

  // serialPrintResult(); // 串口打印 json 数据，Debug 用途

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

    // 显示当前时间与天气实况
    u8g2.firstPage();
    do
    {
      u8g2.setFont(u8g2_font_maniac_tn); // u8g2_font_bubble_tr,u8g2_font_maniac_tn   u8g2_font_maniac_tn u8g2_font_bubble_tr
      getLocalTime(&timeinfo);
      char buffer[10];
      strftime(buffer, 10, "%R", &timeinfo);                    // 格式转换
      u8g2.setCursor((128 - u8g2.getStrWidth(buffer)) / 2, 26); // 计算文本宽度，居中显示
      u8g2.print(&timeinfo, "%R");                              // 格式化输出时间

      for (int i = 34; i < 36; i++)
        u8g2.drawLine(20, i, 105, i); // 画一条有粗细的分割线

      u8g2.setFont(u8g2_font_6x10_mf);
      u8g2.setCursor((128 - (u8g2.getUTF8Width(day[0].var_text_day) + 2 * u8g2.getUTF8Width(" "))) / 2, 38); // 居中显示
      u8g2.print(" ");
      u8g2.print(day[0].var_text_day); // 今天预报的天气文字
      u8g2.print(" ");

      u8g2.setFont(u8g2_font_6x12_mf);
      u8g2.setCursor((128 - (u8g2.getUTF8Width(var_now_temperature) + u8g2.getUTF8Width("C ") + u8g2.getUTF8Width(day[0].var_low) + u8g2.getUTF8Width("-") + u8g2.getUTF8Width(day[0].var_high) + u8g2.getUTF8Width("C ") + u8g2.getUTF8Width(day[0].var_humidity) + u8g2.getUTF8Width("%"))) / 2, 51); // 居中显示
      // u8g2.setCursor(21, 51);
      u8g2.print(var_now_temperature); // 当前气温
      u8g2.print("C ");
      u8g2.print(day[0].var_low); // 当天最低温度(℃)
      u8g2.print("-");
      u8g2.print(day[0].var_high); // 当天最高温度(℃)
      u8g2.print("C ");
      u8g2.print(day[0].var_humidity); // 相对湿度(%)
      u8g2.print("%");

      u8g2.setFont(u8g2_font_6x12_mf);
      // u8g2.setCursor(18, 63);
      u8g2.setCursor((128 - (u8g2.getUTF8Width(day[0].var_date) + u8g2.getUTF8Width(" ") + u8g2.getUTF8Width(day[0].var_rainfall))) / 2, 63); // 居中显示
      u8g2.print(day[0].var_date);                                                                                                            // 今天日期
      u8g2.print(" ");
      u8g2.print(day[0].var_rainfall); // 今天降水量

    } while (u8g2.nextPage()); // 处理完第二页的内容后进入下一页

    delay(pageFlipTime * 4); // 等待一段时间再开始下一次循环

    // 明后两天的天气预报
    for (int dayNum = 1; dayNum <= 2; dayNum++)
    {
      u8g2.firstPage();
      do
      {

        drawIcon(10, 6, 40, 40, day[dayNum].var_code_day);

        u8g2.setFont(u8g2_font_6x12_mf);


        const char *whichDay;
        switch (dayNum)
        {
        case 0:
          whichDay = "TodayFore";
          break;
        case 1:
          whichDay = "Tomorrow";
          break;
        case 2:
          whichDay = "AfterTom";
          break;
        }
        u8g2.setCursor((128 - u8g2.getUTF8Width(whichDay)) / 2 - 35, 60); // 居中显示
        u8g2.print(whichDay);                                             // 显示是哪一天

        u8g2.setFont(u8g2_font_7x13B_mf );// u8g2_font_t0_12b_mf u8g2_font_luBS08_te
        u8g2.setCursor(60, 15);
        u8g2.print(day[dayNum].var_text_day); // 白天天气文字


        u8g2.setFont(u8g2_font_6x12_mf);

        u8g2.setCursor(62, 34);
        u8g2.print(day[dayNum].var_low); // 当天最低温度(℃)
        u8g2.print("-");
        u8g2.print(day[dayNum].var_high); // 当天最高温度(℃)
        u8g2.print("C ");
        u8g2.print(day[dayNum].var_humidity); // 相对湿度(%)
        u8g2.print("%");

        u8g2.setCursor(62, 47);
        u8g2.print("Wind: L");
        u8g2.print(day[dayNum].var_wind_scale); // 风力等级
        u8g2.print(" ");
        u8g2.print(day[dayNum].var_wind_direction); // 风向

        u8g2.setCursor(62, 60);
        u8g2.print("Rain: ");
        u8g2.print(day[dayNum].var_rainfall); // 降水量，单位 mm
        //u8g2.print("mm");


      } while (u8g2.nextPage()); // 处理完第一页的内容后进入下一页

      delay(pageFlipTime); // 等待一段时间再开始下一次循环
    }
  }
}
