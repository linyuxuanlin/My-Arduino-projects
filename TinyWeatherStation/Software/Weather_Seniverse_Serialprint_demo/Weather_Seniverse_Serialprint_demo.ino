#include <WiFi.h>
#include <ArduinoJson.h>

const char* ssid = "WiFi_SSID";       // Wi-Fi SSID
const char* password = "********";  // Wi-Fi 密码

const char* host = "api.seniverse.com";   // 心知天气 API 地址
String location = "shanghai";             // 位置变量
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
  String url = "/v3/weather/daily.json?key=" + privateKey + "&location=" + location + "&language=en&unit=c&start=0&days=3";
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

void setup() {
  // Serial
  Serial.begin(9600);
  WiFi_Connect();
}

void loop() {

  getWeatherData();
  serialPrintResult();

  delay(30000);
}
