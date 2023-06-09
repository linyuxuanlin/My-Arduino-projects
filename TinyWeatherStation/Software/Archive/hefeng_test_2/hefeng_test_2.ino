#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
//#include <u8g2_wqy.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <ArduinoJson.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, /* reset=*/U8X8_PIN_NONE, /* clock=*/0, /* data=*/1);  // ESP32 Thing, HW I2C with pin remapping

//	WiFi的初始化和连接
void WiFi_Connect() {
  WiFi.begin("WiFi_SSID", "********");
  while (WiFi.status() != WL_CONNECTED) {  //这里是阻塞程序，直到连接成功
    delay(300);
    Serial.print(".");
  }
}


// weather get api

String weatherUrl = "https://devapi.qweather.com/v7/weather/now?location=101210111&key=6676a2a9955e46d2903d85d50e4df07d&gzip=n";  // url
long int wendu = 0;                                                                                                               //温度数据
DynamicJsonDocument doc(1024);


//	获取天气
void getWeather() {
  HTTPClient http;
  http.begin(weatherUrl);
  int httpCode = http.GET();
  if (httpCode > 0) {
    // httpCode will be negative on error
    Serial.printf("HTTP Get Code: %d\r\n", httpCode);
    if (httpCode == HTTP_CODE_OK)  // 收到正确的内容
    {
      String resBuff = http.getString();


      Serial.println(resBuff);

      deserializeJson(doc, resBuff);
      const char *status = doc["now"]["text"];
      wendu = doc["now"]["temp"];
      Serial.printf("温度: %ld \r\n", wendu);
      Serial.printf("状态: ");
      Serial.println(status);
      u8g2.setFontDirection(0);
      u8g2.firstPage();
      do {
        u8g2.clear();
        u8g2.setCursor(50, 20);
        u8g2.print("杭州市");
        u8g2.setCursor(0, 40);
        u8g2.print("当前天气 :");
        u8g2.setCursor(60, 40);
        u8g2.print(wendu);
        u8g2.setCursor(75, 40);
        u8g2.print("度");
        u8g2.setCursor(95, 40);
        u8g2.print(status);
        u8g2.setCursor(55, 60);
        u8g2.print("By Qweather");

      } while (u8g2.nextPage());
    }
  } else {
    Serial.printf("HTTP Get Error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void setup() {

  Serial.begin(115200);  // open the serial port at 115200 bps;
  delay(100);

  Serial.print("连接中.. ");

  WiFi_Connect();

  Serial.println("WiFi connected");

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  u8g2.begin();
 
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  
  getWeather();
}


void loop() {

}