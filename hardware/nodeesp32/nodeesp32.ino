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
void setup(){
  Serial.begin(115200);
  SPIFFS.begin();
  dht.begin();
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Dang ket noi");
  while (WiFi.status() != WL_CONNECTED) {
  Serial.print(".");
  delay(500);
  }
  Serial.println ("");
  Serial.println ("Da ket noi WiFi!");
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
}
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Đọc nhiệt độ theo độ C
  Serial.print("Nhiet do: ");
  Serial.print(t);
  Serial.print("*C  ");
  Serial.print("Do am: ");
  Serial.print(h);
  Serial.println("%  ");
  firebase.setFloat( "sensor/Nhietdo", t);
  firebase.setFloat ( "sensor/Doam", h);
  delay(100);

}
