#include <Arduino.h>
#include "bluetooth.hpp"
#include "wifi.hpp"
#include "led.hpp"

const char *WIFI_SSID = "SSID";
const char *WIFI_PASS = "PASSWORD";
WifiConnection* WIFI = new WifiConnection(WIFI_SSID, WIFI_PASS);

void setup()
{
  Serial.begin(9600);
  
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  delay(2000);

  Serial.println();
  Serial.println("Running Firmware.");

  // Connect to Wifi.
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WIFI->initialize();
  initBluetooth();
}

void loop()
{
  delay(200);
}
