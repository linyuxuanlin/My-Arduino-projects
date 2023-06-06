#include <Wire.h>
#include <U8g2lib.h>
#include <WiFi.h>
#include <PubSubClient.h>

// 使用软件 I2C 方式连接 OLED，重新定义引脚
#define OLED_SDA 1
#define OLED_SCL 0

// MQTT 定义
#define WIFI_SSID "xx"
#define WIFI_PASSWORD "xxx"
#define MQTT_BROKER "192.168.31.x"
#define MQTT_PORT 1883
#define MQTT_USERNAME "power"
#define MQTT_PASSWORD "123"
#define MQTT_TOPIC_CPU "USAGE_CPU"
#define MQTT_TOPIC_MEM "USAGE_MEM"
#define MQTT_TOPIC_DISK "USAGE_DISK"

char msg_cpu_usage[10];
char msg_mem_usage[10];
char msg_disk_usage[10];

// 定义 OLED 屏幕对象
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2, OLED_SCL, OLED_SDA, U8X8_PIN_NONE);

// WIFI 客户端对象
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// MQTT 回调函数
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, MQTT_TOPIC_CPU) == 0) {
    // 记录 CPU 使用率
    for (int i = 0; i < length; i++)
      msg_cpu_usage[i] = (char)payload[i];
  } else if (strcmp(topic, MQTT_TOPIC_MEM) == 0) {
    // 记录内存使用率
    for (int i = 0; i < length; i++)
      msg_mem_usage[i] = (char)payload[i];
  } else if (strcmp(topic, MQTT_TOPIC_DISK) == 0) {
    // 记录磁盘使用率
    for (int i = 0; i < length; i++)
      msg_disk_usage[i] = (char)payload[i];
  }
}

void setup() {
  u8g2.begin();  // 初始化 OLED 屏幕
  Wire.begin();  // 开始 I2C 传输

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
    mqttClient.subscribe(MQTT_TOPIC_DISK);
  }
}

void loop() {
  mqttClient.loop();  // 处理 MQTT 消息
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_9x15_tf);

    // 显示 CPU 使用率
    u8g2.setCursor(0, 12);
    u8g2.print("CPU: ");
    for (int i = 0; i < 9; i++)
      u8g2.print(msg_cpu_usage[i]);
    u8g2.print(" %");

    // 显示内存使用率
    u8g2.setCursor(0, 35);
    u8g2.print("Mem: ");
    for (int i = 0; i < 9; i++)
      u8g2.print(msg_mem_usage[i]);
    u8g2.print(" %");

    // 显示磁盘使用率
    u8g2.setCursor(0, 58);
    u8g2.print("Disk: ");
    for (int i = 0; i < 9; i++)
      u8g2.print(msg_disk_usage[i]);
    u8g2.print(" %");

  } while (u8g2.nextPage());
}