#include <WiFi.h>
#include <ESP32Firebase.h>
#include <DHT.h>


#define FIREBASE_HOST "https://garden-54e21-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "ECbbulUCJtIhSzDclYpt26a4Lf67Ehqq8sMm2jLH"
#define WIFI_SSID "B20DCDT183" // Thay đổi tên wifi của bạn
#define WIFI_PASSWORD "tien1022002" // Thay đổi password wifi của bạn
#define DHTPIN 4    //  D4
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);
Firebase firebase(FIREBASE_HOST);
void setup(){
  Serial.begin(115200);
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
}
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Đọc nhiệt độ theo độ C
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Nhiet do: ");
  Serial.print(t);
  Serial.print("*C  ");
  Serial.print("Do am: ");
  Serial.print(h);
  Serial.println("%  ");
  firebase.setFloat( "Nhietdo", t);
  firebase.setFloat ( "Doam", h);
  firebase.setFloat( "device/light", 1);
  firebase.setFloat( "device/fan", 0);
  firebase.setFloat( "device/phunsuong", 1);
  delay(100);
  firebase.setFloat ( "device/light", 0);
    firebase.setFloat( "device/fan", 1);
      firebase.setFloat( "device/phunsuong", 0);
  delay(100);

}
