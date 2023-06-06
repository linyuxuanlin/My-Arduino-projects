#include <ESPJarvis.h>  
//函数定义  
void ShowSoftwareInfo();  
void InitWifi();  
void InitHardware();  
//****用户无线网络设置参数****//  
const char* ssid = "xxxx";     // 无线网络名称  
const char* password = "xxxx"; // 无线网络密码  
//OLED屏设置  
#define SCREEN_WIDTH 128 // 定义显示屏宽度为128像素  
#define SCREEN_HEIGHT 64 // 定义显示屏高度为64像素  
#define SCREEN_RESET -1 // -1表示共享和ESP32的复位信号  
#define SCREEN_ADDRESS 0x3C // OLED显示屏I2C总线的地址，查数据手册可知，一般为0x3C或者0x3D  
/* 初始化OLED显示屏对象,传入我们之前定义好的值*/  
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, SCREEN_RESET);  
/* 初始化Jarvis对象,192.168.0.18是树莓派的IP地址请根据自己的地址修改，1883是MQTT服务器的默认端口号*/  
ESPJarvis Jarvis = ESPJarvis(display, "192.168.0.18", 1883);  
int iTime;//记录当前运行时间  
void setup(void) {    
  InitHardware();  
  InitWifi();  
  Jarvis.setClientData("ESP32Client","test","2022");//这里填上登入MQTT的用户名和密码，"ESP32Client"是ID号可以随便写  
  while (Jarvis.connect()!=true)  
  {  
    Jarvis.printMSG(4,"ConnectBroker...[ERR]");  
    char text[21];  
    sprintf(text,"ErrorCode: %d",Jarvis.getServerState());  
    Jarvis.printMSG(5,text);       
    delay(2000);  
  }    
  Jarvis.printMSG(7,"System is Online...");   
  delay(1000);  
  Jarvis.showVersion();     
}  
void loop(void) {  
    iTime=(int)(millis()/1000)%60;  
    Jarvis.run();  
    if(iTime <= 20){  
      Jarvis.showCPUPage();//显示CPU状态  
    }else if(iTime <= 35){  
      Jarvis.showGPUPage();//显示GPU状态  
    }else if(iTime <= 50){  
      Jarvis.showMemoryPage();//显示内存，SWAP空间和硬盘的使用状态  
    }else{  
      Jarvis.showCPUGPUPage();//显示CPU和GPU的状态  
    }  
    delay(200);   
}  
void InitHardware(){  
  Wire.begin();  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {  
      Serial.println("SSD1306 allocation failed");  
      for(;;); // 表示连接主控失败  
    }
  display.clearDisplay();// 清空显示缓存  
  display.setTextColor(WHITE);  
  display.setTextSize(1);   
  Jarvis.printMSG(1,"**ESPJarvis System**");  
  Jarvis.printMSG(2,"Init Hardware...[OK]");  
}  
void InitWifi(){  
  unsigned char connectionTime = 0;   
  WiFi.mode(WIFI_STA);  
  WiFi.begin(ssid, password);  
  Jarvis.printMSG(3,"Init WIFI...");  
  while (WiFi.status() != WL_CONNECTED) {  
    Serial.print('.');  
    delay(1000);  
    connectionTime = connectionTime + 1;  
    if(connectionTime > 15){  
      Jarvis.printMSG(3,"Init WIFI...[ERR]");  
      Jarvis.printMSG(4,"Please check");  
      Jarvis.printMSG(5,"User WIFI Settings!");  
      delay(60000);  
      connectionTime = 0;   
    }  
  }  
  WiFi.setAutoReconnect(true);  
  Jarvis.printMSG(3,"Init WIFI...[OK]");  
  Jarvis.printMSG(4,"IP Address: ");  
  Jarvis.printMSG(5,WiFi.localIP().toString().c_str());  
}  