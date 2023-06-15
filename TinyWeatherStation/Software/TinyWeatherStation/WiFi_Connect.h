const char *ssid = "WiFi_SSID";    // Wi-Fi SSID
const char *password = "********"; // Wi-Fi 密码

// WiFi 的初始化和连接
void WiFiConnect()
{
  delay(10);
  netStartUI("WiFi Connecting...", 10);
  Serial.print("Connecting to WIFI: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  { // 阻塞程序，直到连接成功
    delay(300);
    Serial.print(".");
  }

  netStartUI("WiFi Connected...", 20);

  Serial.println(""); // 换行
  Serial.println("WiFi connected Successful!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
