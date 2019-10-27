/**
    Home Hue Switch
    Created on: 11.10.2019

*/

#include <M5Stack.h>
#include <WiFi.h>

#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid     = "xxxxx";
const char* password = "xxxx";

const String statusURL = String("http://192.168.xx.x/api/xxxxxxxxxxxxxxxxxxxx/lights/1");
const String actionURL = String("http://192.168.xx.x/api/xxxxxxxxxxxxxxxxxxxx/groups/1/action");
const String lightOn = String("{\"on\": true}");
const String lightOff = String("{\"on\": false}");


void postData(WiFiClient client, String url, String payload) {

  HTTPClient http;
  if (http.begin(client, url)) {

    http.addHeader("Content-Type", "text/json");
    int httpCode = http.PUT(payload);

  }
  http.end();

  return;
}

void OnOff(bool turnOff) {
  WiFiClient client;
  if (turnOff) {
    Serial.println("lights are on!");
    postData(client, actionURL, lightOff);
  } else {
    Serial.println("lights are off!");
    postData(client, actionURL, lightOn);
  }

}



void setup() {

  M5.begin();
  Serial.begin(115200);
  delay(100);
  Serial.setDebugOutput(true);
  M5.Lcd.print("Connecting to ");
  M5.Lcd.print(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      M5.Lcd.print("Wifi status:");
      M5.Lcd.print(WiFi.status());
      M5.Lcd.print(".");
      delay(10000);
      WiFi.begin(ssid, password);
      
  }

  if (WiFi.status() == WL_CONNECTED) {

    M5.Lcd.print("Wifi status:");
    M5.Lcd.print(WiFi.status());
    M5.Lcd.print("WiFi connected");
    M5.Lcd.print("IP address: ");
    M5.Lcd.print(WiFi.localIP());
    M5.Lcd.print("\n");

  }

}

void loop() {

  M5.update();
  if (M5.BtnA.isPressed() == 1) {
    M5.Lcd.print("Press A\n");
    OnOff(true);
  }
  if (M5.BtnB.isPressed() == 1) {
    M5.Lcd.print("Press B\n");
    OnOff(false);
  }

  delay(100);
}