#include<U8glib.h>
U8GLIB_SSD1306_128X64 u8g(10, 9, 12, 11, 13);

const int TrigPin = 7; 
const int EchoPin = 8; 
unsigned int distance; 

void setup() {
      
        pinMode(TrigPin, OUTPUT); 
        pinMode(EchoPin, INPUT); 
        
 
    u8g.setColorIndex(1);         // pixel on
 
}

void loop() {
        digitalWrite(TrigPin, LOW); 
        delayMicroseconds(2); 
        digitalWrite(TrigPin, HIGH); 
        delayMicroseconds(10);
        digitalWrite(TrigPin, LOW); 
   
        distance = pulseIn(EchoPin, HIGH) / 58.00;
        
       
        
   u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );

  delay(100);
}

void draw(void) {
   u8g.setFont(u8g_font_ncenB24);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 80, 50, "cm");
  
  u8g.setPrintPos(5, 50);
  u8g.print(distance);
  

}
