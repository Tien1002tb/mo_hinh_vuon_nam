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

int nhietdo = 25;
int doam = 50;
int quat, den, phunsuong;

QueueHandle_t dataQueue;

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
      Serial2.readBytesUntil('\n', data, 100);
      if (sscanf(data, "%d/%d/%d/%d/%d", &sensorData.nhietdo, &sensorData.doam, &sensorData.quat, &sensorData.den, &sensorData.phunsuong) == 5) {
        Serial.println(sensorData.quat);
        Serial.println(sensorData.den);
        if(xQueueSend(dataQueue, &sensorData, portMAX_DELAY) != pdPASS) {
          Serial.println("Failed to send to queue");
        }
      }
      taskYIELD();
      esp_task_wdt_reset(); // Feed the watchdog
    } else {
      vTaskDelay(1000); // Delay for a short period if no data is available
    }
  }
}

void sendDataToFirebase(void *p) {
  SensorData sensorData;
  while (1) {
    if (xQueueReceive(dataQueue, &sensorData, portMAX_DELAY)) {
      firebase.setInt("sensor/Nhietdo", sensorData.nhietdo);
      firebase.setInt("sensor/Doam", sensorData.doam);
      firebase.setInt("device/fan", sensorData.quat);
      firebase.setInt("device/light", sensorData.den);
    }
   taskYIELD();
      esp_task_wdt_reset();  // Feed the watchdog
  }
}

void getDataFromFirebase(void *p) {
  char DataSet[100];
   while(1){
    int nhietdo_set = firebase.getInt("sensorset/Nhietdoset");
    int doam_set = firebase.getInt("sensorset/Doamset");
    

    // In ra giá trị đã nhận được từ Firebase để kiểm tra trên Serial Monitor
    Serial.print("Nhietdoset: ");
    Serial.println(nhietdo_set);
    Serial.print("Doamset: ");
    Serial.println(doam_set);

    // Gửi giá trị của hai biến qua UART
    sprintf(DataSet, "%d/%d", nhietdo_set, doam_set);
    Serial2.println(DataSet);
    Serial.println(DataSet);
    // Delay giữa các lần đọc dữ liệu từ Firebase
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    esp_task_wdt_reset(); // Feed the watchdog
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

  dataQueue = xQueueCreate(20, sizeof(SensorData)); // Tạo hàng đợi với 10 phần tử;
  xTaskCreatePinnedToCore(receiveDataFromUART, "Task receive UART data", 10000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(sendDataToFirebase, "Task send data to Firebase", 10000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(
    getDataFromFirebase,   /* Task function. */
    "TaskGetData",         /* String with name of task. */
    10000,                 /* Stack size in bytes. */
    NULL,                  /* Parameter passed as input of the task */
    1,                     /* Priority of the task. */
    NULL,                  /* Task handle. */
    );                 
}

void loop() {
}
