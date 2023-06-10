#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600);
  while (!Serial) continue;
  StaticJsonDocument<1024> doc;
  //  char json[] =
  //      "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
  char json[] = "{\"results\":[{\"location\":{\"id\":\"WTW3SJ5ZBJUY\",\"name\":\"Shanghai\",\"country\":\"CN\",\"path\":\"Shanghai,Shanghai,China\",\"timezone\":\"Asia/Shanghai\",\"timezone_offset\":\"+08:00\"},\"daily\":[{\"date\":\"2023-06-08\",\"text_day\":\"Overcast\",\"code_day\":\"9\",\"text_night\":\"Cloudy\",\"code_night\":\"4\",\"high\":\"31\",\"low\":\"20\",\"rainfall\":\"0.00\",\"precip\":\"0.00\",\"wind_direction\":\"W\",\"wind_direction_degree\":\"270\",\"wind_speed\":\"8.4\",\"wind_scale\":\"2\",\"humidity\":\"71\"},{\"date\":\"2023-06-09\",\"text_day\":\"Sunny\",\"code_day\":\"0\",\"text_night\":\"Clear\",\"code_night\":\"1\",\"high\":\"34\",\"low\":\"22\",\"rainfall\":\"0.00\",\"precip\":\"0.00\",\"wind_direction\":\"E\",\"wind_direction_degree\":\"90\",\"wind_speed\":\"8.4\",\"wind_scale\":\"2\",\"humidity\":\"63\"},{\"date\":\"2023-06-10\",\"text_day\":\"Cloudy\",\"code_day\":\"4\",\"text_night\":\"Overcast\",\"code_night\":\"9\",\"high\":\"33\",\"low\":\"23\",\"rainfall\":\"0.00\",\"precip\":\"0.00\",\"wind_direction\":\"S\",\"wind_direction_degree\":\"180\",\"wind_speed\":\"3.0\",\"wind_scale\":\"1\",\"humidity\":\"53\"}],\"last_update\":\"2023-06-08T08:00:00+08:00\"}]}";

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, json);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  JsonObject results_0 = doc["results"][0];
  JsonObject results_0_location = results_0["location"];
  const char* results_0_location_name = results_0_location["name"]; // "上海"

  //const char* location_name = doc["results"]["location"]["name"];
  //int results_daily_0_code_day = doc["results"]["daily"][0]["code_day"];
  //  const char* sensor = doc["sensor"];
  //  long time = doc["time"];
  //  double latitude = doc["data"][0];
  //  double longitude = doc["data"][1];



  // Print values.
  //  Serial.println(sensor);
  //  Serial.println(time);
  //  Serial.println(latitude, 6);
  //  Serial.println(longitude, 6);
  Serial.println(results_0_location_name);
}

void loop() {
  // not used in this example
}
