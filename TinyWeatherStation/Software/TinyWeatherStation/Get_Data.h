String privateKey = "S_iTqDZOILpZdLBZS";  // 心知天气的私钥，请修改为你自己申请的
String location = "shanghai";             // 位置变量
String language = "en";             // api 返回的语言
const char* host = "api.seniverse.com";   // 心知天气 API 地址

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

Weather_get day[3];

const char* city;    // 存放城市位置的变量

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
  String url = "https://api.seniverse.com/v3/weather/daily.json?";
  url += "key=" + privateKey; //添加API私钥
  url += "&location=" + location; //添加请求地点
  url += "&language=" + language; //添加语言
  url += "&unit=c"; //设置温度单位为摄氏度
  url += "&start=0"; //设置从第一天开始获取
  url += "&days=3"; //设置获取数据的天数
  
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
  //可以利用 https://arduinojson.org/v6/assistant/ 生成相关j son 解析代码
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 3 * JSON_OBJECT_SIZE(12) + 700;
  DynamicJsonDocument doc(capacity);

  //如果无法从 API 获取数据，可以先使用静态的 json 测试
  //char json_weather_data[] = "{\"results\":[{\"location\":{\"id\":\"key\",\"name\":\"Shanghai\",\"country\":\"CN\",\"path\":\"Shanghai,Shanghai,China\",\"timezone\":\"Asia/Shanghai\",\"timezone_offset\":\"+08:00\"},\"daily\":[{\"date\":\"2023-06-08\",\"text_day\":\"Overcast\",\"code_day\":\"9\",\"text_night\":\"Cloudy\",\"code_night\":\"4\",\"high\":\"31\",\"low\":\"20\",\"rainfall\":\"0.00\",\"precip\":\"0.00\",\"wind_direction\":\"W\",\"wind_direction_degree\":\"270\",\"wind_speed\":\"8.4\",\"wind_scale\":\"2\",\"humidity\":\"71\"},{\"date\":\"2023-06-09\",\"text_day\":\"Sunny\",\"code_day\":\"0\",\"text_night\":\"Clear\",\"code_night\":\"1\",\"high\":\"34\",\"low\":\"22\",\"rainfall\":\"0.00\",\"precip\":\"0.00\",\"wind_direction\":\"E\",\"wind_direction_degree\":\"90\",\"wind_speed\":\"8.4\",\"wind_scale\":\"2\",\"humidity\":\"63\"},{\"date\":\"2023-06-10\",\"text_day\":\"Cloudy\",\"code_day\":\"4\",\"text_night\":\"Overcast\",\"code_night\":\"9\",\"high\":\"33\",\"low\":\"23\",\"rainfall\":\"0.00\",\"precip\":\"0.00\",\"wind_direction\":\"S\",\"wind_direction_degree\":\"180\",\"wind_speed\":\"3.0\",\"wind_scale\":\"1\",\"humidity\":\"53\"}],\"last_update\":\"2023-06-08T08:00:00+08:00\"}]}";

  DeserializationError error = deserializeJson(doc, json_weather_data);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    netStartUI("deJson failed...", 60); //如果数据解析失败，从串口看错误代码，查文档
    return;
  }

  netStartUI("Get city name...", 80);


  JsonObject results_0 = doc["results"][0];

  JsonObject results_0_location = results_0["location"];
  const char* results_0_location_name = results_0_location["name"];  // "shanghai"
  city = results_0_location_name;

  //const char* results_0_daily_0_date = results_0["daily"][0]["date"];  // "2023-06-08" work

  netStartUI("Get data...", 90);

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
  netStartUI("Success, pls wait..", 100);
}
