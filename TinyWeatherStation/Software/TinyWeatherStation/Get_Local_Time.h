const char *ntpServer = "cn.pool.ntp.org";
const long gmtOffset_sec = 8 * 3600;
const int daylightOffset_sec = 0;
struct tm timeinfo;

void printLocalTime()
{
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.print("Time: ");
  Serial.println(&timeinfo, "%F %T %A"); // 格式化输出时间
}