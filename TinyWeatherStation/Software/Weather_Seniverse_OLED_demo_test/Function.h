
#include <ArduinoJson.h>

void netStartUI(char* title, int num) {
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

//	WiFi的初始化和连接
void WiFi_Connect() {
  delay(10);
  Serial.println();
  netStartUI("WiFi Connecting...", 10);
  Serial.print("Connecting to WIFI");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {  // 阻塞程序，直到连接成功
    delay(300);
    Serial.print(".");
  }

  netStartUI("WiFi Connected...", 20);

  Serial.println("");  //换行
  Serial.println("WiFi connected Successful!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// 获取天气数据
void getWeatherData() {
  Serial.print("正在尝试访问心知天气 API: ");
  Serial.println(host);
  netStartUI("API accessing...", 30);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    netStartUI("API failed...", 20);
    return;
  }

  netStartUI("API success...", 40);

  // 给请求创建一个 URL
  String url = "/v3/weather/daily.json?key=" + privateKey + "&location=" + loaction + "&language=en&unit=c&start=0&days=3";
  Serial.print("Requesting URL: ");
  Serial.println(url);

  // 向服务器发送请求
  netStartUI("Sending request...", 50);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  delay(100);
  String weather_data;
  while (client.available()) {
    String line = client.readStringUntil('\r');
    weather_data += line;
  }
  netStartUI("Request success...", 60);

  //关闭连接
  client.stop();
  netStartUI("Request done...", 70);
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

  Serial.println(json_weather_data);

  //利用 ArduinoJson 库解析心知返回的 json 天气数据
  //可以利用 https://arduinojson.org/v5/assistant/ Arduinojson 助手生成相关json解析代码
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 3 * JSON_OBJECT_SIZE(12) + 700;
  //DynamicJsonDocument jsonBuffer(1024);  //原先是 capacity
  //StaticJsonDocument<2048> doc;

  DynamicJsonDocument doc(capacity);

  char weather_data_test[] = "{\"results\":[{\"location\":{\"id\":\"WTW3SJ5ZBJUY\",\"name\":\"Shanghai\",\"country\":\"CN\",\"path\":\"Shanghai,Shanghai,China\",\"timezone\":\"Asia/Shanghai\",\"timezone_offset\":\"+08:00\"},\"daily\":[{\"date\":\"2023-06-08\",\"text_day\":\"Overcast\",\"code_day\":\"9\",\"text_night\":\"Cloudy\",\"code_night\":\"4\",\"high\":\"31\",\"low\":\"20\",\"rainfall\":\"0.00\",\"precip\":\"0.00\",\"wind_direction\":\"W\",\"wind_direction_degree\":\"270\",\"wind_speed\":\"8.4\",\"wind_scale\":\"2\",\"humidity\":\"71\"},{\"date\":\"2023-06-09\",\"text_day\":\"Sunny\",\"code_day\":\"0\",\"text_night\":\"Clear\",\"code_night\":\"1\",\"high\":\"34\",\"low\":\"22\",\"rainfall\":\"0.00\",\"precip\":\"0.00\",\"wind_direction\":\"E\",\"wind_direction_degree\":\"90\",\"wind_speed\":\"8.4\",\"wind_scale\":\"2\",\"humidity\":\"63\"},{\"date\":\"2023-06-10\",\"text_day\":\"Cloudy\",\"code_day\":\"4\",\"text_night\":\"Overcast\",\"code_night\":\"9\",\"high\":\"33\",\"low\":\"23\",\"rainfall\":\"0.00\",\"precip\":\"0.00\",\"wind_direction\":\"S\",\"wind_direction_degree\":\"180\",\"wind_speed\":\"3.0\",\"wind_scale\":\"1\",\"humidity\":\"53\"}],\"last_update\":\"2023-06-08T08:00:00+08:00\"}]}";


  DeserializationError error = deserializeJson(doc, json_weather_data);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    netStartUI("deJson failed...", 60);
    return;
  }


  netStartUI("Get city name...", 80);


  JsonObject results_0 = doc["results"][0];

  JsonObject results_0_location = results_0["location"];
  const char* results_0_location_name = results_0_location["name"];  // "shanghai"
  city = results_0_location_name;
  //Serial.println(results_0_location_name);

  //const char* results_0_daily_0_date = results_0["daily"][0]["date"];  // "2023-06-08" work


  netStartUI("Get data...", 90);

  // const char* results_0_daily_0_date = results_0["daily"][0]["date"];  // "2023-06-08"
  // const char* results_0_daily_0_text_day = results_0["daily"][0]["text_day"];
  // const char* results_0_daily_0_code_day = results_0["daily"][0]["code_day"];
  // const char* results_0_daily_0_text_night = results_0["daily"][0]["text_night"];
  // const char* results_0_daily_0_high = results_0["daily"][0]["high"];
  // const char* results_0_daily_0_low = results_0["daily"][0]["low"];
  // const char* results_0_daily_0_wind_direction = results_0["daily"][0]["wind_direction"];
  // const char* results_0_daily_0_wind_speed = results_0["daily"][0]["wind_speed"];
  // const char* results_0_daily_0_wind_scale = results_0["daily"][0]["wind_scale"];
  // const char* results_0_daily_0_rainfall = results_0["daily"][0]["rainfall"];
  // const char* results_0_daily_0_humidity = results_0["daily"][0]["humidity"];

  //JsonObject results_0_daily = results_0["daily"];

  int dayNum = 0;

  for (JsonObject results_0_daily_item : results_0["daily"].as<JsonArray>()) {
    const char* results_0_daily_item_date = results_0_daily_item["date"];                      // "2023-06-08", "2023-06-09", ...
    const char* results_0_daily_item_text_day = results_0_daily_item["text_day"];              // "阴", "晴", "多云"
    const char* results_0_daily_item_code_day = results_0_daily_item["code_day"];              // "9", "0", "4"
    const char* results_0_daily_item_text_night = results_0_daily_item["text_night"];          // "多云", "晴", "阴"
    const char* results_0_daily_item_code_night = results_0_daily_item["code_night"];          // "4", "1", "9"
    const char* results_0_daily_item_high = results_0_daily_item["high"];                      // "31", "34", "33"
    const char* results_0_daily_item_low = results_0_daily_item["low"];                        // "20", "22", "23"
    const char* results_0_daily_item_rainfall = results_0_daily_item["rainfall"];              // "0.00", "0.00", "0.00"
    const char* results_0_daily_item_precip = results_0_daily_item["precip"];                  // "0.00", "0.00", "0.00"
    const char* results_0_daily_item_wind_direction = results_0_daily_item["wind_direction"];  // "西", "东", ...
    const char* results_0_daily_item_wind_direction_degree = results_0_daily_item["wind_direction_degree"];
    const char* results_0_daily_item_wind_speed = results_0_daily_item["wind_speed"];  // "8.4", "8.4", "3.0"
    const char* results_0_daily_item_wind_scale = results_0_daily_item["wind_scale"];  // "2", "2", "1"
    const char* results_0_daily_item_humidity = results_0_daily_item["humidity"];      // "71", "63", "53"

    day[dayNum].v_date = results_0_daily_item_date;
    day[dayNum].v_text_day = results_0_daily_item_text_day;
    day[dayNum].v_code_day = results_0_daily_item_code_day;
    day[dayNum].v_text_night = results_0_daily_item_text_night;
    day[dayNum].v_high = results_0_daily_item_high;
    day[dayNum].v_low = results_0_daily_item_low;
    day[dayNum].v_wind_direction = results_0_daily_item_wind_direction;
    day[dayNum].v_wind_speed = results_0_daily_item_wind_speed;
    day[dayNum].v_wind_scale = results_0_daily_item_wind_scale;
    day[dayNum].v_rainfall = results_0_daily_item_rainfall;
    day[dayNum].v_humidity = results_0_daily_item_humidity;

    dayNum++;
    if (dayNum == 3)
      dayNum = 0;
  }

  // if (!root.success()) {
  //   return;
  // }

  netStartUI("Success, pls wait..", 100);
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
