// OLED 屏幕定义
#define OLED_SDA 1
#define OLED_SCL 0

// 定义 OLED 屏幕对象
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2, OLED_SCL, OLED_SDA, U8X8_PIN_NONE);

const char* ssid = "WiFi_SSID";     // Wi-Fi SSID
const char* password = "********";  // Wi-Fi 密码

const char* host = "api.seniverse.com";   // 心知天气 API 地址
String loaction = "shanghai";             // 位置变量
String privateKey = "S_iTqDZOILpZdLBZS";  // 心知天气的私钥

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

const char* city;    // 存放返回值的变量
Weather_get day[3];  // 获取天气信息

const int pageFlipTime = 5000;       // 设置翻页的时间间隔，单位毫秒
unsigned long displayStartMillis;    // 记录上一次屏幕刷新的时间
const int dataRefreshTime = 600000;  // 设置数据刷新的时间间隔，单位毫秒，10 分钟
unsigned long refreshStartMillis;    // 记录上一次数据更新的时间
