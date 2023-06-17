String privateKey = "S_iTqDZOILpZdLBZS"; // 心知天气的私钥，请修改为你自己申请的
String location = "shanghai";            // 位置变量
String language = "en";                  // api 返回的语言
const char *host = "api.seniverse.com";  // 心知天气 API 地址

typedef struct forecast_weather_data_struct
{
  const char *var_date;                  // 日期
  const char *var_text_day;              // 白天天气现象文字
  const char *var_code_day;              // 白天天气现象代码
  const char *var_text_night;            // 晚间天气现象文字
  const char *var_code_night;            // 晚间天气现象代码
  const char *var_high;                  // 当天最高温度
  const char *var_low;                   // 当天最低温度
  const char *var_precip;                // 降水概率，范围 0~100，单位百分比（目前仅支持国外城市）
  const char *var_wind_direction;        // 风向
  const char *var_wind_direction_degree; // 风向角度，范围 0~360
  const char *var_wind_speed;            // 风速，单位 km/h（当unit=c时）、mph（当unit=f时）
  const char *var_wind_scale;            // 风力等级
  const char *var_rainfall;              // 降水量，单位 mm
  const char *var_humidity;              // 相对湿度，0~100，单位为百分比

} Forecast_weather_data_struct;
Forecast_weather_data_struct day[3];

const char *var_city_name; // 存放读回城市位置返回值的变量

const char *var_now_text;        // 天气现象文字
const char *var_now_code;        // 天气现象代码
const char *var_now_temperature; // 当前气温

// 获取天气数据
void getWeatherData()
{
  Serial.print("Visiting API: ");
  Serial.println(host);
  netStartUI("API accessing...", 30);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort))
  {
    Serial.println("connection failed");
    netStartUI("Access failed...", 20);
    return;
  }
  netStartUI("Access success...", 40);

  // 给请求创建 URL
  // 三天天气预报
  String forecast_weather_url = "https://api.seniverse.com/v3/weather/daily.json?";
  forecast_weather_url += "key=" + privateKey;     // 添加API私钥
  forecast_weather_url += "&location=" + location; // 添加请求地点
  forecast_weather_url += "&language=" + language; // 添加语言
  forecast_weather_url += "&unit=c";               // 设置温度单位为摄氏度
  forecast_weather_url += "&start=0";              // 设置从第一天开始获取
  forecast_weather_url += "&days=3";               // 设置获取数据的天数

  // 天气实况
  String live_weather_url = "https://api.seniverse.com/v3/weather/now.json?";
  live_weather_url += "key=" + privateKey;     // 添加API私钥
  live_weather_url += "&location=" + location; // 添加请求地点
  live_weather_url += "&language=" + language; // 添加语言
  live_weather_url += "&unit=c";               // 设置温度单位为摄氏度

  // Debug 用途
  // Serial.print("forecast_weather_url: ");
  // Serial.println(forecast_weather_url);
  // Serial.print("live_weather_url: ");
  // Serial.println(live_weather_url);

  // 向服务器发送请求
  netStartUI("Sending request...", 50);

  client.print(String("GET ") + forecast_weather_url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  delay(100);
  String forecast_weather_data;
  while (client.available())
  {
    String line = client.readStringUntil('\r');
    forecast_weather_data += line;
  }

  // 重新创建连接
  client.stop();
  if (!client.connect(host, httpPort))
    return;

  netStartUI("Sending request...", 55);
  client.print(String("GET ") + live_weather_url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  delay(100);
  String live_weather_data;
  while (client.available())
  {
    String line = client.readStringUntil('\r');
    live_weather_data += line;
  }

  netStartUI("Request success...", 60);

  // 关闭连接
  client.stop();
  netStartUI("Request done...", 70);

  Serial.println("Done, closing connection");

  // 寻找 JSON 天气数据起始位置
  String json_forecast_weather_data;
  String json_live_weather_data;
  int jsonIndex_forecast;
  int jsonIndex_live;

  for (int i = 0; i < forecast_weather_data.length(); i++)
  {
    if (forecast_weather_data[i] == '{')
    {
      jsonIndex_forecast = i;
      break;
    }
  }

  for (int i = 0; i < live_weather_data.length(); i++)
  {
    if (live_weather_data[i] == '{')
    {
      jsonIndex_live = i;
      break;
    }
  }

  // 获取天气数据
  json_forecast_weather_data = forecast_weather_data.substring(jsonIndex_forecast);
  json_live_weather_data = live_weather_data.substring(jsonIndex_live);

  // Debug 用途
  // Serial.print("json_forecast_weather_data: ");
  // Serial.println(json_forecast_weather_data);
  // Serial.print("json_live_weather_data: ");
  // Serial.println(json_live_weather_data);

  // 利用 ArduinoJson 库解析心知返回的 json 天气数据
  // 可以利用 https://arduinojson.org/v6/assistant/ 生成相关json 解析代码
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 3 * JSON_OBJECT_SIZE(12) + 700;
  DynamicJsonDocument doc_forecast(capacity);
  DynamicJsonDocument doc_live(capacity);

  // 如果无法从 API 获取数据，可以先使用静态的 json 测试
  // char json_forecast_weather_data[] = "{\"results\":[{\"location\":{\"id\":\"key\",\"name\":\"Shanghai\",\"country\":\"CN\",\"path\":\"Shanghai,Shanghai,China\",\"timezone\":\"Asia/Shanghai\",\"timezone_offset\":\"+08:00\"},\"daily\":[{\"date\":\"2023-06-08\",\"text_day\":\"Overcast\",\"code_day\":\"9\",\"text_night\":\"Cloudy\",\"code_night\":\"4\",\"high\":\"31\",\"low\":\"20\",\"rainfall\":\"0.00\",\"precip\":\"0.00\",\"wind_direction\":\"W\",\"wind_direction_degree\":\"270\",\"wind_speed\":\"8.4\",\"wind_scale\":\"2\",\"humidity\":\"71\"},{\"date\":\"2023-06-09\",\"text_day\":\"Sunny\",\"code_day\":\"0\",\"text_night\":\"Clear\",\"code_night\":\"1\",\"high\":\"34\",\"low\":\"22\",\"rainfall\":\"0.00\",\"precip\":\"0.00\",\"wind_direction\":\"E\",\"wind_direction_degree\":\"90\",\"wind_speed\":\"8.4\",\"wind_scale\":\"2\",\"humidity\":\"63\"},{\"date\":\"2023-06-10\",\"text_day\":\"Cloudy\",\"code_day\":\"4\",\"text_night\":\"Overcast\",\"code_night\":\"9\",\"high\":\"33\",\"low\":\"23\",\"rainfall\":\"0.00\",\"precip\":\"0.00\",\"wind_direction\":\"S\",\"wind_direction_degree\":\"180\",\"wind_speed\":\"3.0\",\"wind_scale\":\"1\",\"humidity\":\"53\"}],\"last_update\":\"2023-06-08T08:00:00+08:00\"}]}";
  // char json_live_weather_data[] = "{\"results\":[{\"location\":{\"id\":\"WTW3SJ5ZBJUY\",\"name\":\"Shanghai\",\"country\":\"CN\",\"path\":\"Shanghai,Shanghai,China\",\"timezone\":\"Asia/Shanghai\",\"timezone_offset\":\"+08:00\"},\"now\":{\"text\":\"Cloudy\",\"code\":\"4\",\"temperature\":\"22\"},\"last_update\":\"2023-06-13T22:20:15+08:00\"}]}";

  DeserializationError error_forecast = deserializeJson(doc_forecast, json_forecast_weather_data);
  DeserializationError error_live = deserializeJson(doc_live, json_live_weather_data);

  if (error_forecast)
  {
    Serial.print("forecast data deserializeJson() failed: ");
    Serial.println(error_forecast.c_str());
    netStartUI("deJson failed...", 60); // 如果数据解析失败，从串口看错误代码，查文档
    return;
  }

  if (error_live)
  {
    Serial.print("live data deserializeJson() failed: ");
    Serial.println(error_live.c_str());
    netStartUI("deJson failed...", 60); // 如果数据解析失败，从串口看错误代码，查文档
    return;
  }

  netStartUI("Resolve data...", 80);

  JsonObject results_0 = doc_forecast["results"][0];
  JsonObject results_0_location = results_0["location"];
  var_city_name = results_0_location["name"]; // "shanghai"

  int dayNum = 0;

  for (JsonObject results_0_daily_item : results_0["daily"].as<JsonArray>())
  {
    day[dayNum].var_date = results_0_daily_item["date"];                     // "2023-06-08", "2023-06-09", ...
    day[dayNum].var_text_day = results_0_daily_item["text_day"];             // "阴", "晴", "多云"
    day[dayNum].var_code_day = results_0_daily_item["code_day"];             // "9", "0", "4"
    day[dayNum].var_text_night = results_0_daily_item["text_night"];         // "多云", "晴", "阴"
    day[dayNum].var_code_night = results_0_daily_item["code_night"];         // "4", "1", "9"
    day[dayNum].var_high = results_0_daily_item["high"];                     // "31", "34", "33"
    day[dayNum].var_low = results_0_daily_item["low"];                       // "20", "22", "23"
    day[dayNum].var_precip = results_0_daily_item["precip"];                 // "0.00", "0.00", "0.00"
    day[dayNum].var_wind_direction = results_0_daily_item["wind_direction"]; // "西", "东", ...
    day[dayNum].var_wind_direction_degree = results_0_daily_item["wind_direction_degree"];
    day[dayNum].var_wind_speed = results_0_daily_item["wind_speed"]; // "8.4", "8.4", "3.0"
    day[dayNum].var_wind_scale = results_0_daily_item["wind_scale"]; // "2", "2", "1"
    day[dayNum].var_rainfall = results_0_daily_item["rainfall"];     // "0.00", "0.00", "0.00"
    day[dayNum].var_humidity = results_0_daily_item["humidity"];     // "71", "63", "53"

    dayNum++;
    if (dayNum == 3)
      dayNum = 0;
  }

  netStartUI("Resolve data...", 90);

  JsonObject results_1 = doc_live["results"][0];
  JsonObject results_1_now = results_1["now"];
  var_now_text = results_1_now["text"];               // "Cloudy"
  var_now_code = results_1_now["code"];               // "4"
  var_now_temperature = results_1_now["temperature"]; // "22"

  netStartUI("Success, pls wait..", 100);
}
