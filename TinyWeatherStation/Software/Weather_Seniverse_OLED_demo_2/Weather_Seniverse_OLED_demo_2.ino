#include <WiFi.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <U8g2lib.h>
#include "Icon.h"

// OLED 屏幕定义
#define OLED_SDA 1
#define OLED_SCL 0

// 定义 OLED 屏幕对象
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2, OLED_SCL, OLED_SDA, U8X8_PIN_NONE);

const char* ssid = "Power_Wi-Fi_p2.4";       // Wi-Fi SSID
const char* password = "82467627171982547";  // Wi-Fi 密码

const char* host = "api.seniverse.com";   // 心知天气 API 地址
String loaction = "shanghai";             // 位置变量
String privateKey = "S_iTqDZOILpZdLBZS";  // 心知天气的私钥

int i = 0;


typedef struct weather_get {
  const char* v_date;            // 日期
  const char* v_text_day;        // 白天天气现象文字
  const char* v_code_day;        // 白天天气现象代码
  const char* v_text_night;      // 晚间天气现象文字
  const char* v_high;            // 当天最高温度
  const char* v_low;             // 当天最低温度
  const char* v_wind_direction;  // 风向
  const char* v_wind_speed;      // 风速，单位 km/h（当unit=c时）、mph（当unit=f时）
  const char* v_wind_scale;      // 风力等级
  const char* v_rainfall;        // 降水量，单位 mm
  const char* v_humidity;        // 相对湿度，0~100，单位为百分比
} Weather_get;

const char* city;    // 存放返回值的变量
Weather_get day[3];  // 获取天气信息


const int DELAY_TIME = 5000;       // 设置延迟的时间，单位毫秒
unsigned long displayStartMillis;  //记录上一次屏幕刷新的时间

//	WiFi的初始化和连接
void WiFi_Connect() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to WIFI");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {  // 阻塞程序，直到连接成功
    delay(300);
    Serial.print(".");
  }

  Serial.println("");  //换行
  Serial.println("WiFi connected Successful!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// 获取天气数据
void getWeatherData() {
  Serial.print("正在尝试访问心知天气 API: ");
  Serial.println(host);
  //port:所要连接的服务器端口号,允许使用int类型
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // 给请求创建一个 URL
  String url = "/v3/weather/daily.json?key=" + privateKey + "&location=" + loaction + "&language=en&unit=c&start=0&days=3";
  Serial.print("Requesting URL: ");
  Serial.println(url);

  // 向服务器发送请求
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  delay(100);
  String weather_data;
  while (client.available()) {
    String line = client.readStringUntil('\r');
    weather_data += line;
  }

  //关闭连接
  client.stop();
  Serial.println();
  Serial.println("Done, closing connection");
  Serial.println();

  // 寻找 JSON 天气数据起始位置
  String json_weather_data;
  int jsonIndex;

  for (int i = 0; i < weather_data.length(); i++) {
    if (weather_data[i] == '{') {
      jsonIndex = i;
      break;
    }
  }

  // 获取天气数据
  json_weather_data = weather_data.substring(jsonIndex);

  //利用 ArduinoJson 库解析心知返回的 json 天气数据
  //可以利用 https://arduinojson.org/v5/assistant/ Arduinojson 助手生成相关json解析代码
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 3 * JSON_OBJECT_SIZE(12) + 700;
  DynamicJsonBuffer jsonBuffer(capacity);

  //获取城市名称
  JsonObject& root = jsonBuffer.parseObject(json_weather_data);
  JsonObject& results_0 = root["results"][0];
  JsonObject& results_0_location = results_0["location"];
  city = results_0_location["name"];
  JsonArray& results_0_daily = results_0["daily"];


  for (int dayNum = 0; dayNum < 3; dayNum++) {
    // 返回今明后三天的天气数据
    JsonObject& result = results_0_daily[dayNum];
    day[dayNum].v_date = result["date"];
    day[dayNum].v_text_day = result["text_day"];
    day[dayNum].v_code_day = result["code_day"];
    day[dayNum].v_text_night = result["text_night"];
    day[dayNum].v_high = result["high"];
    day[dayNum].v_low = result["low"];
    day[dayNum].v_wind_direction = result["wind_direction"];
    day[dayNum].v_wind_speed = result["wind_speed"];
    day[dayNum].v_wind_scale = result["wind_scale"];
    day[dayNum].v_rainfall = result["rainfall"];
    day[dayNum].v_humidity = result["humidity"];
  }

  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }
}

// 串口打印天气数据
void serialPrintResult() {
  for (int dayNum = 0; dayNum < 3; dayNum++) {
    Serial.print("城市: ");
    Serial.println(city);
    Serial.print("日期: ");
    Serial.println(day[dayNum].v_date);
    Serial.print("白天天气: ");
    Serial.println(day[dayNum].v_text_day);
    Serial.print("白天天气代码: ");
    Serial.println(day[dayNum].v_code_day);
    Serial.print("晚间天气: ");
    Serial.println(day[dayNum].v_text_night);
    Serial.print("当天最高温度(℃): ");
    Serial.println(day[dayNum].v_high);
    Serial.print("当天最低温度(℃): ");
    Serial.println(day[dayNum].v_low);
    Serial.print("风向: ");
    Serial.println(day[dayNum].v_wind_direction);
    Serial.print("风速(km/h): ");
    Serial.println(day[dayNum].v_wind_speed);
    Serial.print("风力等级: ");
    Serial.println(day[dayNum].v_wind_scale);
    Serial.print("降水量(mm): ");
    Serial.println(day[dayNum].v_rainfall);
    Serial.print("相对湿度(%): ");
    Serial.println(day[dayNum].v_humidity);
    Serial.println("--------------");
  }
}


void netStartUI(char* title, int num, bool isFirst) {
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  u8g2.firstPage();
  do {
    u8g2.setCursor(14, 30);
    u8g2.print(title);
    u8g2.drawRFrame(9, 17, 110, 30, 5);
    u8g2.drawFrame(14, 36, 100, 6);
    u8g2.drawBox(14, 36, num, 6);
  } while (u8g2.nextPage());
}


void setup() {
  // Serial
  Serial.begin(9600);
  u8g2.begin();  // 初始化 OLED 屏幕
  Wire.begin();  // 开始 I2C 传输
  WiFi_Connect();


  //
  // netStartUI("数据解析中...", 20, isFirst);
  netStartUI("Preparing...", 0, 1);

  getWeatherData();
  //serialPrintResult();

  //netStartUI("Preparing...", 50, 1);
  //netStartUI("Preparing...", 80, 1);
  netStartUI("Success, pls wait..", 100, 1);
  //


  //u8g2.enableUTF8Print();
  //u8g2.setFont(u8g2_font_wqy12_t_gb2312);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_resoledmedium_tr);
  //u8g2_font_5x7_tf


  displayStartMillis = millis();  //初始化刷新时间
}

void loop() {
  if (millis() - displayStartMillis > DELAY_TIME) {  //如果时间到了
    displayStartMillis = millis();                   //更新刷新时间

    for (int dayNum = 0; dayNum < 3; dayNum++) {
      u8g2.firstPage();  //第一页
      do {

        const uint8_t* icon;

        //icon = sunny;

        int v_code_day_int = atoi(day[dayNum].v_code_day);

        switch (v_code_day_int) {
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

        u8g2.setCursor((24 - u8g2.getUTF8Width(day[dayNum].v_text_day)) / 2 + 16, 60);
        u8g2.print(day[dayNum].v_text_day);  // 白天天气

        String whichDay;
        switch (dayNum) {
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
        u8g2.print(whichDay);  // 哪一天



        u8g2.setCursor(60, 30);
        u8g2.print(day[dayNum].v_low);  // 当天最低温度(℃)
        u8g2.print("-");
        u8g2.print(day[dayNum].v_high);  // 当天最高温度(℃)
        u8g2.print(" C");


        u8g2.setCursor(60, 40);
        u8g2.print("Wind: ");
        u8g2.print(day[dayNum].v_wind_direction);  // 风向
        u8g2.print(" L");
        u8g2.print(day[dayNum].v_wind_scale);  // 风力等级

        u8g2.setCursor(60, 50);
        u8g2.print("Humi: ");
        u8g2.print(day[dayNum].v_humidity);  // 相对湿度(%)
        u8g2.print(" %");

        
        u8g2.setCursor(60, 60);
        u8g2.print(day[dayNum].v_date);  // 日期

        //u8g2.print("Weather: ");
        //u8g2.setCursor(68, 20);

      } while (u8g2.nextPage());  //处理完第一页的内容后进入下一页
      delay(DELAY_TIME);          //等待一段时间再开始下一次循环
    }

    /*
    u8g2.firstPage();  //第二页
    do {
      u8g2.setFont(u8g2_font_profont11_mf);
      u8g2.setCursor(20, 20);
      u8g2.print("page 2");     //设置第二页的显示内容
    } while (u8g2.nextPage());  //处理完第二页的内容后进入下一页
    delay(DELAY_TIME);          //等待一段时间再开始下一次循环
*/
  }

  /*
  // 显示欢迎界面
  u8g2.firstPage();
  do {
    u8g2.clear();
    u8g2.setCursor(50, 20);
    u8g2.print("上海市");
    u8g2.setCursor(0, 40);
    u8g2.print("今天白天天气 :");
    u8g2.setCursor(60, 40);
    u8g2.print(day[0].v_text_day);
    u8g2.setCursor(55, 60);
    u8g2.print("by Power");
  } while (u8g2.nextPage());
*/
  //delay(30000);
}