#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <WiFi.h>
#include <ESP32Firebase.h>
#include "Webpage.h"
#include "SPIFFS.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include "esp_task_wdt.h"

#define RX_PIN 16
#define TX_PIN 17

#define FIREBASE_HOST "https://garden-54e21-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "ECbbulUCJtIhSzDclYpt26a4Lf67Ehqq8sMm2jLH"
#define WIFI_SSID "B20DCDT183"
#define WIFI_PASSWORD "tien1022002"

Firebase firebase(FIREBASE_HOST);
AsyncWebServer server(80);

QueueHandle_t dataQueue;
bool newdata = false;
typedef struct {
  int nhietdo;
  int doam;
  int quat;
  int den;
  int phunsuong;
} SensorData;

void receiveDataFromUART(void *p) {
  char data[100];
  SensorData sensorData;
  while (1) {
    if (Serial2.available()) {
      int length = Serial2.readBytesUntil('\n', data, 100);
      data[length] = '\0';
      if (sscanf(data, "%d/%d/%d/%d/%d", &sensorData.nhietdo, &sensorData.doam, &sensorData.quat, &sensorData.den, &sensorData.phunsuong) == 5) {
        Serial.println(sensorData.quat);
        Serial.println(sensorData.den);
        // Gửi dữ liệu lên Firebase từng giá trị một
        firebase.setInt("sensor/Nhietdo", sensorData.nhietdo);
        Serial.println("Nhietdo updated successfully");

        firebase.setInt("sensor/Doam", sensorData.doam);
        Serial.println("Doam updated successfully");

        firebase.setInt("device/fan", sensorData.quat);
        Serial.println("Fan updated successfully");

        firebase.setInt("device/light", sensorData.den);
        Serial.println("Light updated successfully");

        firebase.setInt("device/phunsuong", sensorData.phunsuong);
        Serial.println("Phunsuong updated successfully");
      }
    }
    vTaskDelay(pdMS_TO_TICKS(2));
  }
}
void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  SPIFFS.begin();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", Webpage);
  });
  server.on("/ptit", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/ptit.png", "image/png");
  });
  server.on("/doam", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/doam.png", "image/png");
  });
  server.on("/nhietke", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/nhietke.png", "image/png");
  });
  server.on("/fan_off", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/fan_off.png", "image/png");
  });
  server.on("/fan_on", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/fan_on.png", "image/png");
  });
  server.on("/light_on", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/light_on.png", "image/png");
  });
  server.on("/light_off", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/light_off.png", "image/png");
  });
  server.on("/PSoff", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/PSoff.png", "image/png");
  });
  server.on("/PSon", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/PSon.png", "image/png");
  });
  server.begin();
  xTaskCreatePinnedToCore(receiveDataFromUART, "Task receive UART data", 10000, NULL, 1, NULL, 0);
               
}
void loop() {
}
