// 串口打印 json 数据
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
