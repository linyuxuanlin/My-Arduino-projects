#include <Wire.h>
#include <U8g2lib.h>  //导入字库
#include <WiFi.h>
#include <PubSubClient.h>

// OLED 屏幕定义
#define OLED_SDA 1
#define OLED_SCL 0

// MQTT 定义
#define WIFI_SSID "WiFi_SSID"
#define WIFI_PASSWORD "********"
#define MQTT_BROKER "192.168.31.8"
#define MQTT_PORT 1883
#define MQTT_USERNAME "power"
#define MQTT_PASSWORD "123"
#define MQTT_TOPIC_CPU "USAGE_CPU"
#define MQTT_TOPIC_MEM "USAGE_MEM"

// 定义 OLED 屏幕对象
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2, OLED_SCL, OLED_SDA, U8X8_PIN_NONE);


// WIFI 客户端对象
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// MQTT 回调函数
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, MQTT_TOPIC_CPU) == 0) {
    // 显示 CPU 使用率
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_profont10_tr);
      u8g2.setCursor(0, 12);
      u8g2.print("CPU Usage: ");
      u8g2.print((char*)payload);
      u8g2.print("%");
    } while (u8g2.nextPage());
  } else if (strcmp(topic, MQTT_TOPIC_MEM) == 0) {
    // 显示内存使用率
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_profont10_tr);
      u8g2.setCursor(0, 28);
      u8g2.print("Memory Usage: ");
      u8g2.print((char*)payload);
      u8g2.print("%");
    } while (u8g2.nextPage());
  }
}

void setup() {
  // 开始串口通信
  Serial.begin(115200);

  // 初始化 OLED 屏幕
  u8g2.begin();

  // 开始 I2C 传输
  Wire.begin();

  // 连接 WIFI
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  // 连接 MQTT 代理服务器
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
  mqttClient.setCallback(mqttCallback);
  if (mqttClient.connect("ESP32", MQTT_USERNAME, MQTT_PASSWORD)) {
    mqttClient.subscribe(MQTT_TOPIC_CPU);
    mqttClient.subscribe(MQTT_TOPIC_MEM);
  }
}

void loop() {
  mqttClient.loop();  // 处理 MQTT 消息

  // 显示欢迎界面
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_profont12_tr);
    u8g2.setCursor(0, 12);
    u8g2.print("Server Monitoring");
    u8g2.setCursor(0, 28);
    u8g2.print("with ESP32 and MQTT");
  } while (u8g2.nextPage());
}