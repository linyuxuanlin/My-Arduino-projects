// OLED 屏幕定义
#define OLED_SDA 1
#define OLED_SCL 0
#define brightness 1 // OLED 亮度，0~255

// 定义 OLED 屏幕对象
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2, OLED_SCL, OLED_SDA, U8X8_PIN_NONE);

// 初始化 OLED 屏幕
void OLEDInit(void) {
  u8g2.begin();
  u8g2.setContrast(brightness);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_resoledmedium_tr);
}

void netStartUI(char* title, int num) {
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  u8g2.firstPage();
  do {
    u8g2.setCursor(14, 30);
    u8g2.print(title);
    u8g2.drawRFrame(9, 17, 110, 30, 5);
    u8g2.drawFrame(14, 36, 100, 6);
    u8g2.drawBox(14, 36, num, 6);
  } while (u8g2.nextPage());
}
