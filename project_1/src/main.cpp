#define BLYNK_TEMPLATE_ID "TMPL3o-q8T5WA"
#define BLYNK_TEMPLATE_NAME "mmWave Setup"
#define BLYNK_AUTH_TOKEN  "6uY52Kq5pzSZdoC3I8KQmZ1efea5ltTp"

#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#ifndef STASSID
#define STASSID "TP-Link_5GTB_L"
#define STAPSK  "5gtb3210"
#endif

#define BLYNK_PRINT Serial

char ssid[] = STASSID;
char pass[] = STAPSK;

void OTAsetup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(5000);
    ESP.restart();
  }
  ArduinoOTA.begin();
}

void ensureWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi disconnected, reconnecting...");
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("\nReconnected to Wi-Fi!");
  }
}

void OTAloop() {
  ArduinoOTA.handle();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  OTAsetup();

  // Print the IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  // GPIO default state
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  Serial.println("GPIO2 set to HIGH.");

  // Connect to Blynk
  Serial.println("Connecting to Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  Serial.println("Blynk connected!");
}

void loop() {
  ensureWiFi();
  OTAloop();
  Blynk.run();
}
