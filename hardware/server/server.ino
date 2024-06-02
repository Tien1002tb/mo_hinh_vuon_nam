#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <WiFi.h>
#include <ESP32Firebase.h>
#include <DHT.h>
#include "Webpage.h"
#include "SPIFFS.h"

#define FIREBASE_HOST "https://garden-54e21-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "ECbbulUCJtIhSzDclYpt26a4Lf67Ehqq8sMm2jLH"
#define WIFI_SSID "B20DCDT183" // Thay đổi tên wifi của bạn
#define WIFI_PASSWORD "tien1022002" // Thay đổi password wifi của bạn
#define DHTPIN 4    //  D4
#define DHTTYPE DHT11  

AsyncWebServer server(80);
DHT dht(DHTPIN, DHTTYPE);
Firebase firebase(FIREBASE_HOST);

#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <WiFi.h>
#include <ESP32Firebase.h>
#include <DHT.h>
#include "Webpage.h"
#include "SPIFFS.h"

#define FIREBASE_HOST "https://garden-54e21-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "ECbbulUCJtIhSzDclYpt26a4Lf67Ehqq8sMm2jLH"
#define WIFI_SSID "B20DCDT183" // Thay đổi tên wifi của bạn
#define WIFI_PASSWORD "tien1022002" // Thay đổi password wifi của bạn
#define DHTPIN 4    //  D4
#define DHTTYPE DHT11  

AsyncWebServer server(80);
DHT dht(DHTPIN, DHTTYPE);
Firebase firebase(FIREBASE_HOST);

bool taskCompleted = false; // Biến cờ để kiểm soát việc chạy task

void Taskserver(void *pvParameters){
  if (!taskCompleted) { // Kiểm tra nếu task chưa hoàn thành
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Dang ket noi");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      vTaskDelay(pdMS_TO_TICKS(500));
    }
    Serial.println("");
    Serial.println("Da ket noi WiFi!");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "text/html", Webpage);
    });
    server.on("/ptit", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/ptit.png", "image/png");
    });
    server.on("/doam", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/doam.png", "image/png");
    });
    server.on("/nhietke", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/nhietke.png", "image/png");
    });
    server.on("/fan_off", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/fan_off.png", "image/png");
    }); 
    server.on("/fan_on", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/fan_on.png", "image/png"); 
    });
    server.on("/light_on", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/light_on.png", "image/png");
    });
    server.on("/light_off", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/light_off.png", "image/png");
    }); 
    server.on("/PSoff", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/PSoff.png", "image/png");
    }); 
    server.on("/PSon", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/PSon.png", "image/png");
    }); 
    
    // Start the server
    server.begin();

    taskCompleted = true; // Đặt cờ task đã hoàn thành
  }

  // Thay vì xóa task, giữ nó trong vòng lặp trống để server duy trì hoạt động
  while (1) {
    vTaskDelay(pdMS_TO_TICKS(1000)); // Delay to prevent watchdog timer reset
  }
}

void setup(){
  Serial.begin(115200);
  SPIFFS.begin();
  xTaskCreatePinnedToCore(Taskserver, "Ket noi Server", 10000, NULL, 1, NULL, 2);
}

void loop() {
  // Bỏ trống loop vì mọi thứ đều chạy trong các task
}

void setup(){
  Serial.begin(115200);
  SPIFFS.begin();
  xTaskCreatePinnedToCore(Taskserver, "Ket noi Server", 10000, NULL, 1, NULL, 2);
  }

void loop() {

}
