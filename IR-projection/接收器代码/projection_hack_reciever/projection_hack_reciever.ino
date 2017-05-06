
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
IRrecv ir_recieve(11);//红外接收模块接在D11
decode_results results;
LiquidCrystal_I2C lcd(0x27,20,4);
void setup()
{
  Serial.begin(9600);//开启串口,方便调试
  ir_recieve.enableIRIn();  //初始化红外遥控

  lcd.init(); // 初始化lcd 
  lcd.init(); //再来一次,防止不彻底
  
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Projection Hack");
  Serial.println("hello");
}
void loop()
{
  if (ir_recieve.decode(&results))
  {
    Serial.println(results.value);
    //输出到串口
    lcd.setCursor(4,1);
    lcd.print(results.value,HEX );
    //以16进制输出
  }
  ir_recieve.resume();// 接收下一个值
  delay(500);//必要的一点延时
}
