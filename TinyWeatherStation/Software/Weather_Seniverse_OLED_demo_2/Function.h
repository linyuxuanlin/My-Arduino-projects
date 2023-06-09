

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

  //利用 ArduinoJson 库解析心知返回的 json 天气数据
  //可以利用 https://arduinojson.org/v5/assistant/ Arduinojson 助手生成相关json解析代码
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 3 * JSON_OBJECT_SIZE(12) + 700;
  DynamicJsonBuffer jsonBuffer(capacity);

  netStartUI("Get city name...", 80);

  //获取城市名称
  JsonObject& root = jsonBuffer.parseObject(json_weather_data);
  JsonObject& results_0 = root["results"][0];
  JsonObject& results_0_location = results_0["location"];
  city = results_0_location["name"];
  JsonArray& results_0_daily = results_0["daily"];

  netStartUI("Get data...", 90);

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
    netStartUI("Get data failed...", 80);
    return;
  }

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

