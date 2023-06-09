#include <WiFi.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <U8g2lib.h>
#include "Icon.h"

// OLED 屏幕定义
#define OLED_SDA 1
#define OLED_SCL 0

#define Times 5000  // 页面显示时间(毫秒)

// 定义 OLED 屏幕对象
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2, OLED_SCL, OLED_SDA, U8X8_PIN_NONE);

const char* ssid = "WiFi_SSID";       // Wi-Fi SSID
const char* password = "********";  // Wi-Fi 密码

const char* host = "api.seniverse.com";   // 心知天气 API 地址
String loaction = "shanghai";             // 位置变量
String privateKey = "S_iTqDZOILpZdLBZS";  // 心知天气的私钥

typedef struct weather_get {
  const char* v_date;            // 日期
  const char* v_text_day;        // 白天天气现象文字
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

int sec = 0;
int num = 0;

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

void baseUI(int dotNum, int dotSec, bool isMes, bool isShow, bool isRefresh) {
  //side_dotNOSec(dotNum);
  int y = (64 - dotNum * 4 - (dotNum - 1) * 4);
  for (int i = 0; i < dotNum; i++)
    u8g2.drawCircle(4, y + 8 * i, 2);

  //side_dot(dotSec, dotNum);
  int y = (64 - dotNum * 4 - (dotNum - 1) * 4);
  u8g2.drawDisc(4, y + 8 * dotSec, 2);

  if (isShow) {
    Time(isMes, true, 0);
  }
  icon(0, 0, 0, 2);

  //side_temperature(isRefresh);
  if (isRefresh)
    u8g2.drawXBM(0, 53, 8, 10, refresh);
  else {}
}


//TBD
void TodyTime(int y) {
  str(weather.tody.date, 15, 60, y, u8g2_font_lucasfont_alternate_tr);
  str(Time_c.time, 15, 50, y, u8g2_font_courB18_tn);
  str(weather.now, 15, 17, y, u8g2_font_helvR10_tr);
  if (weather.tody.cod >= 300) {
    icon(67, 6, y, 1);  //伞
  }
  icon(88, 4, y, weather.tody.cod);
  str(weather.tody.status, 15, 28, y, u8g2_font_baby_tf);
  rectangle(y);
}

//TBD
void Tody(int y) {
  rectangle(y);
  icon(36, 9, y, weather.tody.cod);
  if (weather.tody.cod >= 300) {
    icon(12, 26, y, 1);  //伞
  }
  str(weather.now, 78, 25, y, u8g2_font_profont22_tr);                   // 12*22  现在温度
  str(weather.tody.range, 78, 40, y, u8g2_font_lucasfont_alternate_tr);  // 最高与最低温度
  str(weather.pm25, 78, 52, y, u8g2_font_trixel_square_tr);              // pm2.5
  str(weather.qlty, 78, 60, y, u8g2_font_trixel_square_tr);
  str(weather.city, 14, 60, y, u8g2_font_lucasfont_alternate_tr);  // 城市名字
}

//TBD
void Two(int y) {
  rectangle(y);
  icon(38, 6, y, weather.tom.cod);
  icon(82, 6, y, weather.afterTom.cod);
  str(weather.tom.range, 26, 56, y, u8g2_font_lucasfont_alternate_tr);       // 最高与最低温度
  str(weather.afterTom.range, 75, 56, y, u8g2_font_lucasfont_alternate_tr);  // 最高与最低温度
}

//TBD
void Message(int y) {
  //  u8g2_font_wqy12_t_gb2312
  //  u8g2_font_lucasfont_alternate_tr
  if (y == 0) {
    u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  }
  rectangle(y);
  strNoFont(weather.title, 41, 20, y);
  strNoFont(weather.detail1, 15, 32, y);
  strNoFont(weather.detail2, 15, 44, y);
  strNoFont(weather.detail3, 15, 56, y);
  strNoFont(weather.detail4, 15, 68, y);
  // str(weather.detail5, 15, 37, y, u8g2_font_lucasfont_alternate_tr);
}

//TBD
void strNoFont(const char* string, int x, int yy, int y) {
  u8g2.setCursor(x, yy - y);
  u8g2.print(string);
}


//TBD
void rectangle(int y) {
  u8g2.drawRFrame(10, 0 - y, 118, 64, 5);
}

//TBD
void icon(int x, int yy, int y, int statu) {

  switch (statu) {
    case 1:
      u8g2.drawXBM(x, yy - y, 24, 24, umbrella);
      break;
    case 2:
      u8g2.drawXBM(x, yy - y, 10, 10, netIcon);
      break;
    case 3:
      u8g2.drawXBM(x, yy - y, 8, 10, refresh);
      break;
    case 100:
      u8g2.drawXBM(x, yy - y, 40, 40, suny);
      break;
    case 101:
    case 103:
      u8g2.drawXBM(x, yy - y, 40, 40, cloudy);
      break;
    case 102:
      u8g2.drawXBM(x, yy - y, 40, 40, partlyCloudy);
      break;
    case 104:
      u8g2.drawXBM(x, yy - y, 40, 40, overcast);
      break;
    case 300:
    case 301:
    case 302:
    case 303:
    case 304:
      u8g2.drawXBM(x, yy - y, 40, 40, thunderShowe);
      break;
    case 305:
    case 309:
      u8g2.drawXBM(x, yy - y, 40, 40, lightRain);
      break;
    case 306:
    case 313:
      u8g2.drawXBM(x, yy - y, 40, 40, moderateRain);
      break;
    case 307:
    case 308:
    case 310:
    case 311:
    case 312:
      u8g2.drawXBM(x, yy - y, 40, 40, heavyRain);
      break;
    case 400:
      u8g2.drawXBM(x, yy - y, 40, 40, lightSnow);
      break;
    case 401:
    case 407:
      u8g2.drawXBM(x, yy - y, 40, 40, moderateSnow);
      break;
    case 402:
    case 403:
      u8g2.drawXBM(x, yy - y, 40, 40, heavySnow);
      break;
    case 404:
    case 405:
    case 406:
      u8g2.drawXBM(x, yy - y, 40, 40, sleet);
      break;
    default:
      u8g2.drawXBM(x, yy - y, 40, 40, unknown);
      break;
  }
}


void GDStart() {
  int y = 2;
  if (sec == 5)
    sec = 0;
  do {
    u8g2.firstPage();
    do {
      if (sec == 0)
        baseUI(4, sec, true, false, false);
      else {
        if (sec == 4)
          baseUI(4, 0, true, false, false);
        else
          baseUI(4, sec, true, true, false);
      }
      switch (sec) {
        case 0:
          TodyTime(0);
          break;
        case 1:
          TodyTime(y);
          Tody(-64 + y);
          break;
        case 2:
          Tody(y);
          Two(-64 + y);
          break;
        case 3:
          Two(y);
          Message(-64 + y);
          break;
        case 4:
          Message(y);
          TodyTime(-64 + y);
          break;
        default:
          break;
      }
    } while (
      u8g2.nextPage());
    if (sec == 0)
      break;
    y += 2;
  } while (y <= 64);
  if (sec != 4)
    delay(Times);
  else {
    if (num == 10) {
      GDWeatherGet(fingerprint, url, true);
      num = 0;
    } else if (num % 2 == 0) {
      NTPRequest(false);
    }
    num++;
  }
  sec++;
}

void setup() {
  // Serial
  Serial.begin(9600);
  u8g2.begin();  // 初始化 OLED 屏幕
  Wire.begin();  // 开始 I2C 传输
  WiFi_Connect();


  //u8g2.enableUTF8Print();
  //u8g2.setFont(u8g2_font_wqy12_t_gb2312);
}

void loop() {

  // netStartUI("数据解析中...", 20, isFirst);
  netStartUI("Preparing...", 0, 1);

  getWeatherData();
  //serialPrintResult();

  netStartUI("Preparing...", 50, 1);
  netStartUI("Preparing...", 80, 1);
  netStartUI("JsonParse Success", 100, 1);

  GDStart();


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
