#include "WiFi.h"
#include "time.h"

const char *ssid = "WIFI_SSID";
const char *pass = "WIFI_PASSWORD";

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

const int relayPin = 26;
bool relayOn;

tm getMyLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return timeinfo;
  }
  return timeinfo;
}

void setup()
{
  Serial.begin(115200);

  pinMode(relayPin, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    delay(1000);
  }

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void switchRelayOn()
{
  digitalWrite(relayPin, HIGH);
}

void switchRelayOff()
{
  digitalWrite(relayPin, LOW);
}

void loop()
{
  struct tm timeinfo = getMyLocalTime();
  // Wednesday, July 10 2024 13:57:32
  //     A    ,   B   d   Y   H: M: S
  // Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

  int minutes = timeinfo.tm_min;
  relayOn = minutes % 2 == 0;

  if (relayOn)
  {
    switchRelayOn();
  }
  else
  {
    switchRelayOff();
  }

  delay(1000);
}
