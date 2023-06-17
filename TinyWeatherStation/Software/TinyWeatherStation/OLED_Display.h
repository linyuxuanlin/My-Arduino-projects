// OLED 屏幕定义
#define OLED_SDA 1
#define OLED_SCL 0
#define brightness 1 // OLED 亮度，0~255

// 定义 OLED 屏幕对象
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2, OLED_SCL, OLED_SDA, U8X8_PIN_NONE);

// 初始化 OLED 屏幕
void OLEDInit(void)
{
  u8g2.begin();
  u8g2.setContrast(brightness);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_resoledmedium_tr);
  u8g2.setFontMode(0); // 透明模式（transparent mode），刷新更快
}

// 加载的 UI
void netStartUI(char *title, int num)
{
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  u8g2.firstPage();
  do
  {
    u8g2.setCursor(14, 30);
    u8g2.print(title);
    u8g2.drawRFrame(9, 17, 110, 30, 5);
    u8g2.drawFrame(14, 36, 100, 6);
    u8g2.drawBox(14, 36, num, 6);
  } while (u8g2.nextPage());
}

void drawIcon(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h, const char *weather_code)
{
  const uint8_t *icon;
  int weather_code_int = atoi(weather_code); // 数据类型转换
  switch (weather_code_int)
  {
  case 0 && 1 && 2 && 3:
    icon = sunny;
    break;
  case 4:
    icon = cloudy;
    break;
  case 5 && 6 && 7 && 8:
    icon = partlyCloudy;
    break;
  case 9:
    icon = overcast;
    break;
  case 11:
    icon = thunderShower;
    break;
  case 13:
    icon = lightRain;
    break;
  case 14:
    icon = moderateRain;
    break;
  case 15:
    icon = heavyRain;
    break;
  case 20:
    icon = sleet;
    break;
  case 22:
    icon = lightSnow;
    break;
  case 23:
    icon = moderateSnow;
    break;
  case 24:
    icon = heavySnow;
    break;
  default:
    icon = unknown;
    break;
  }
  u8g2.drawXBM(x, y, w, h, icon); // 画天气的 icon
}
