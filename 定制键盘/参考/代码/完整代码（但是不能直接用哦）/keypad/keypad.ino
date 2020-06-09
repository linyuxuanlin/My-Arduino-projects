#include <Keyboard.h>
const int buttons[] = {2, 3, 4, 5, 6, 7, 8, 9, 10}; // array of all button pins


//unicode from https://apps.timwhitlock.info/emoji/tables/unicode
//solution 1 use emoji's Byte(utf-8)
//solution2 use emoji's Unicode
//solution3 use hex input and emoji's Surrogates
#define   xiaoku  "d83dde02"//solution3     // for solution 1"\\xF0\\x9F\\x98\\x82"
#define   kaixin       "\\xF0\\x9F\\x98\\x83" // for solution 1
#define   ganga       "U+1F605" //for solution 2 

//Hexadecimal  https://r12a.github.io/app-conversion/
#define love "FF083065FFE30033FFE3FF093065256D2764FF5E000A" //（づ￣3￣）づ╭❤～
#define happy "30FD0028273FFF9F25BDFF9F002930CE" //ヽ(✿ﾟ▽ﾟ)ノ

#define   DELAY   200

void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);
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

void quick_open(String software_name) {
  delay(50);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(' ');
  Keyboard.releaseAll();
  delay(100);
  Keyboard.println(software_name);
  delay(100);
  Keyboard.println();
}

void open_safari() {
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('s');
  Keyboard.releaseAll();
  delay(200);
}

void emoji(String emoji) {
  //Solution 1  not work on chinese mode
  //    quick_open("terminal.app");
  //    delay(150);
  //    String command = "echo -e \"" + emoji + "\" | pbcopy";
  //    Keyboard.println(command);
  //    Keyboard.press('\n');
  //    delay(100);
  //    Keyboard.releaseAll();
  //
  //    Keyboard.press(KEY_LEFT_GUI);
  //    Keyboard.press('h');
  //    Keyboard.releaseAll();
  //    delay(100);
  //
  //    Keyboard.press(KEY_LEFT_GUI);
  //    Keyboard.press('v');
  //    Keyboard.releaseAll();
  //    Keyboard.press(KEY_BACKSPACE);
  //    Keyboard.releaseAll();

  //Solution2  not work on chinese mode
  //    Keyboard.press(KEY_LEFT_CTRL);
  //    Keyboard.press(KEY_LEFT_GUI);
  //    Keyboard.press(' ');
  //    delay(250);
  //    Keyboard.releaseAll();
  //    //wait for emoji window open
  //    delay(250);
  //    Keyboard.print(emoji);

  //solution3 only work in hex input mode
  Keyboard.press(KEY_LEFT_ALT);
  delay(100);
  Keyboard.print(emoji);
  Keyboard.releaseAll();
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

void yanwenzi(String code) {
  //mac 需要使用其他键盘里的16进制输入法
  Keyboard.press(KEY_LEFT_ALT);
  delay(10);
  Keyboard.print(code);
  Keyboard.releaseAll();
}

