// 串口打印 json 数据
void serialPrintResult()
{

  // 实时天气
  Serial.print("当前天气现象文字: ");
  Serial.println(var_now_text);
  Serial.print("当前天气现象代码: ");
  Serial.println(var_now_code);
  Serial.print("当前气温: ");
  Serial.println(var_now_temperature);
  Serial.println("--------------");

  // 三天天气预报
  for (int dayNum = 0; dayNum < 3; dayNum++)
  {
    Serial.print("城市: ");
    Serial.println(var_city_name);
    Serial.print("日期: ");
    Serial.println(day[dayNum].var_date);
    Serial.print("白天天气: ");
    Serial.println(day[dayNum].var_text_day);
    Serial.print("白天天气代码: ");
    Serial.println(day[dayNum].var_code_day);
    Serial.print("晚间天气: ");
    Serial.println(day[dayNum].var_text_night);
    Serial.print("晚间天气代码: ");
    Serial.println(day[dayNum].var_code_night);
    Serial.print("当天最高温度(℃): ");
    Serial.println(day[dayNum].var_high);
    Serial.print("当天最低温度(℃): ");
    Serial.println(day[dayNum].var_low);
    Serial.print("降水概率（仅支持国外城市）: ");
    Serial.println(day[dayNum].var_precip);
    Serial.print("风向: ");
    Serial.println(day[dayNum].var_wind_direction);
    Serial.print("风向角度: ");
    Serial.println(day[dayNum].var_wind_direction_degree);
    Serial.print("风速(km/h): ");
    Serial.println(day[dayNum].var_wind_speed);
    Serial.print("风力等级: ");
    Serial.println(day[dayNum].var_wind_scale);
    Serial.print("降水量(mm): ");
    Serial.println(day[dayNum].var_rainfall);
    Serial.print("相对湿度(%): ");
    Serial.println(day[dayNum].var_humidity);
    Serial.println("--------------");
  }
}
