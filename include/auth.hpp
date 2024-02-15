/*
curl -X 'POST' \
  'http://127.0.0.1:8000/token' \
  -H 'accept: application/json' \
  -H 'Content-Type: application/x-www-form-urlencoded' \
  -d 'grant_type=&username=johndoe&password=secret&scope=&client_id=&client_secret='
  */

#include <HTTPClient.h>
#include <Arduino.h>

const String SERVER_BASE_URL="http://192.168.1.108:8000";

String getUser(String token) {
    HTTPClient http;
    String apiUrl = SERVER_BASE_URL + "/users/me";

    http.begin(apiUrl.c_str());
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    http.addHeader("Authorization", "Bearer " + token);
    
    int httpResponseCode = http.GET();

    if (httpResponseCode == 200)
    {
      Serial.print("Connection OK");
      Serial.println();
      String payload = http.getString();
      Serial.println(payload);
      http.end();

      return payload;
    }

    http.end();
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    return "";
}