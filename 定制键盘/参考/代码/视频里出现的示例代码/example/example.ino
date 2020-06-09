#include <Keyboard.h>
const int buttons[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};

void setup() {
  Keyboard.begin();
  for(int i = 0; i<9; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 9; i++) {
    if (digitalRead(buttons[i]) == LOW) {
      // software de-bounce improves accuracy
      delay(20);
      if (digitalRead(buttons[i]) == LOW) {
        doAction(buttons[i]);
        delay(DELAY);
      }
    }
  }
}


void doAction(int pin) {
  // perform tasks
  switch (pin) {
    case 2:
      //    quick_open("safari");
      open_safari();
      delay(100);
      open_website_in_safari("bilibili.com");
      break;
    case 3:
      //    quick_open("safari");
      open_safari();
      delay(100);
      open_website_in_safari("youtube.com");
      break;
    case 4:
      open_safari();
      delay(100);
      open_website_in_safari("google.com");
      break;
    case 5:
      //    quick_open("yunyinyue");
      quick_open("chrome");
      break;
    case 6: 
      quick_open("yunyinyue");
      break;
    case 7:
      emoji(xiaoku);
      break;
    case 8:
      yanwenzi(happy);
      break;
  }
}


void open_xunlei() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('l');
  Keyboard.releaseAll();
  delay(200);
}

void open_website_in_safari(String url) {
  delay(100);
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('t');
  Keyboard.releaseAll();
  Keyboard.println(url);
  //多敲一下回车，应对中文输入法情况
//  Keyboard.println();
}
