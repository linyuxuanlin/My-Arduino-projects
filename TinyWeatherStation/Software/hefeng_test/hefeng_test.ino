#include <WiFi.h>
#include <HTTPClient.h>
#include <U8g2lib.h>
#include <ArduinoJson.h>

// OLED 屏幕定义
#define OLED_SDA 1
#define OLED_SCL 0

// 定义 OLED 屏幕对象
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2, OLED_SCL, OLED_SDA, U8X8_PIN_NONE);

const char* ssid = "Power_Wi-Fi_p2.4";
const char* password = "82467627171982547";

const char* server = "https://devapi.qweather.com/v7/weather/3d?location=101010100&key=dd33cabb69224a8e9c1599d550e17408&lang=en&gzip=n";
HTTPClient http;

static const unsigned char PROGMEM weather_xbm[] = {
  0x00, 0x00, 0xf0, 0x07, 0xf8, 0x1f, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
  0x18, 0x18, 0x18, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Wifi connecting...");
  }
  Serial.println("Wifi connected.");
  u8g2.begin();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    http.begin(server);
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("point");
      Serial.println(payload);
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);
      const char* weather = doc["now"]["text"];
      const char* temperature = doc["now"]["temp"];
      delay(10000);
      u8g2.clearBuffer();
u8g2.setFont(u8g2_font_profont12_tr);
    u8g2.setCursor(0, 12);
    u8g2.print("Server Monitoring");
delay(10000);
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_t0_16_mr);
      u8g2.drawStr(0, 18, weather);
      u8g2.drawXBMP(85, 4, 20, 20, weather_xbm);
      u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
      u8g2.setCursor(0, 46);
      u8g2.print(temperature);
      u8g2.print("C");
      u8g2.sendBuffer();
    } else {
      Serial.printf("HTTP GET error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}


