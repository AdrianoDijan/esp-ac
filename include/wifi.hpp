#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

class WifiConnection
{
public:
  bool connected = false;
  const char *SSID;
  const char *password;

  wl_status_t status()
  {
    return WiFi.status();
  }

  bool checkInternet()
  {
    String testServer = "http://ifconfig.co/json";
    HTTPClient http;

    http.begin(testServer.c_str());
    
    int httpResponseCode = http.GET();

    if (httpResponseCode == 200)
    {
      Serial.print("Connection OK");
      Serial.println();
      String payload = http.getString();
      Serial.println(payload);
      http.end();

      return true;
    }

    http.end();
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    return false;
  }

  WifiConnection(const char *SSID, const char *password)
  {
    this->SSID = SSID;
    this->password = password;
  }
  void initialize();
};

void WifiConnection::initialize()
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  WiFi.begin(this->SSID, this->password);
  Serial.println("Connecting...");

  while (WiFi.status() != WL_CONNECTED)
  {
    if (WiFi.status() == WL_CONNECT_FAILED)
    {
      Serial.println("Failed to connect to WIFI. Please verify credentials: ");
      Serial.println();
      Serial.print("SSID: ");
      Serial.println(this->SSID);
      Serial.print("Password: ");
      Serial.println(this->password);
      Serial.println();
    }
    delay(5000);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
