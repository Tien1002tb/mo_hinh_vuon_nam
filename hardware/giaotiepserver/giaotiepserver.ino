#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <WiFi.h>
#include <ESP32Firebase.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define FIREBASE_HOST "https://garden-54e21-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "ECbbulUCJtIhSzDclYpt26a4Lf67Ehqq8sMm2jLH"
#define WIFI_SSID "B20DCDT183"
#define WIFI_PASSWORD "tien1022002"

Firebase firebase(FIREBASE_HOST);
AsyncWebServer server(80);

#define AOUT_PIN 14 // cam bien do am dat
const int max_kho = 3000;   
const int max_am = 1000;  

#define DHTPIN 4    // D4
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);
void lcd_button();
const int menu = 34; 
const int back = 35; 
const int len = 19; 
const int xuong = 18; 

const int den = 25;
const int quat = 26;
const int phunsuong = 27;
int fan , light, phunsuong1;

const int Rx = 16;
const int Tx = 17;

int gtmenu, gtback, gtlen, gtxuong;
int macdinh = 1;
int congtru_tong = 0;
int demback = 0;
int demtong = 0;

int congtru_setting = 0; // 0: Thiết lập nhiệt độ, 1: Thiết lập độ ẩm

int nhietdo_hientai = 25; 
int nhietdo_thietlap = 22; 
int doam_thietlap = 50;
int percentage =20 ; 

bool button_pressed = false; 
bool dataChanged = false; 
unsigned long lastUpdateTime = 0; // Biến lưu thời gian lần cập nhật cuối cùng
const unsigned long updateInterval = 2000; // Khoảng thời gian cập nhật (2 giây)

SemaphoreHandle_t xSemaphore = xSemaphoreCreateMutex();

void manhinh()  // HIỂN THỊ MÀN HÌNH CHÍNH
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" MAN HINH CHINH "); 
  lcd.setCursor(0, 1);
  lcd.print("       MENU >>>"); 
}

void menu_tong() // HIỂN THỊ MENU TỔNG
{
  lcd.clear();
  if (congtru_tong == 0)
  {
    lcd.print("> THONG TIN");
    lcd.setCursor(2, 1);
    lcd.print("CAI DAT");  
  }
  else if (congtru_tong == 1)
  { 
    lcd.setCursor(2, 0);
    lcd.print("THONG TIN");
    lcd.setCursor(0, 1);
    lcd.print("> CAI DAT");    
  }
}

void hien_thi() {
  if (xSemaphoreTake(xSemaphore, portMAX_DELAY)) { // Take the semaphore
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Nhiet do :");
    lcd.setCursor(10, 0);
    lcd.print(nhietdo_hientai);
    lcd.setCursor(13, 0);
    lcd.print("*C");

    lcd.setCursor(0, 1);
    lcd.print("Do am :");
    lcd.setCursor(7, 1);
    lcd.print(percentage);
    lcd.setCursor(10, 1);
    lcd.print("%");

    xSemaphoreGive(xSemaphore); // Give the semaphore
  }
}

void setting() // THIẾT LẬP NHIỆT ĐỘ VÀ ĐỘ ẨM
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nhiet do :");
  lcd.setCursor(10,0);
  lcd.print(nhietdo_thietlap);
  lcd.setCursor(12, 0);
  lcd.print("*C");

  lcd.setCursor(0, 1);
  lcd.print("Do am :");
  lcd.setCursor(7,1);
  lcd.print(doam_thietlap);
  lcd.setCursor(10, 1);
  lcd.print("%");
  
}

void chon_setting(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nhiet do :");
  lcd.setCursor(10,0);
  lcd.print(nhietdo_thietlap);
  lcd.setCursor(12, 0);
  lcd.print("*C");

  lcd.setCursor(0, 1);
  lcd.print("Do am :");
  lcd.setCursor(7,1);
  lcd.print(doam_thietlap);
  lcd.setCursor(10, 1);
  lcd.print("%");

  if (congtru_setting == 0) {
    lcd.setCursor(15, 0);
    lcd.print("<");
  } else {
    lcd.setCursor(15, 1);
    lcd.print("<");
  }
}

void lcd_button(void){
  gtlen = digitalRead(len);  
  gtxuong = digitalRead(xuong);  
  gtmenu = digitalRead(menu);
  gtback = digitalRead(back);

  button_pressed = false; // Reset button pressed flag at the start of each loop

  if (gtlen != macdinh)  // NÚT LÊN
  {
    if (gtlen == 0) // Khi nhấn nút lên
    {
      button_pressed = true; // Set flag to true when any button is pressed

      if (demtong == 1)   // LÊN Ở MENU TỔNG  
      {
        if (congtru_tong >= 1)
        { 
          congtru_tong = 1;  
        }
        else
        { 
          congtru_tong++;  
        }   
        menu_tong();
      }
      else if (demtong == 3 && congtru_setting == 0)   
      {
        if (nhietdo_thietlap <= 0)
        { 
          nhietdo_thietlap = 0;  
        }
        else
        { 
          nhietdo_thietlap--;  
        }
        chon_setting();
      }  
      else if (demtong == 4 && congtru_setting == 1)   
      {
        if (doam_thietlap <= 0)
        { 
          doam_thietlap = 0;  
        }
        else
        { 
          doam_thietlap--;  
        }
        chon_setting();
      }  
      delay(500);
    }
    macdinh = gtlen;
  }

  if (gtxuong != macdinh) // NÚT XUỐNG
  {
    if (gtxuong == 0) //Khi nhấn nút xuống
    {
      button_pressed = true; // Set flag to true when any button is pressed

      if (demtong == 1)   // XUỐNG Ở MENU TỔNG
      {
        if (congtru_tong <= 0)
        { 
          congtru_tong = 0;  
        }
        else
        { 
          congtru_tong--;  
        }
        menu_tong();
      }
      else if (demtong == 3 && congtru_setting == 0)   
      {
        if (nhietdo_thietlap >= 100)
        { 
          nhietdo_thietlap = 100;  
        }
        else
        { 
          nhietdo_thietlap++;  
        }
        chon_setting();
      }  
      else if (demtong == 4 && congtru_setting == 1)   
      {
        if (doam_thietlap >= 100)
        { 
          doam_thietlap = 100;  
        }
        else
        { 
          doam_thietlap++;  
        }
        chon_setting();
      }  
      delay(500);
    }
    macdinh = gtxuong;
  }

  if (gtmenu != macdinh)    // NÚT MENU
  {  
    if (gtmenu == 0) //Khi nhấn nút
    {
      button_pressed = true; // 

      if (demtong == 2 && congtru_tong == 0) {
        demtong = 2;
      } else {
        demtong++;
      }

      if (demtong == 0) // Ở menu tổng
      { 
        demback = 0;
        manhinh(); 
      }
      if (demtong == 1) // Ở menu tổng
      { 
        demback = 0;
        menu_tong(); 
      }
      else if (demtong == 2 && congtru_tong == 0) // Ở menu 1
      {
        demback = 0;
        hien_thi();
      }
      else if (demtong == 2 && congtru_tong == 1) // Ở menu 2
      {
        demback = 0;
        setting(); 
      }
      else if (demtong == 3) // Chọn setting
      {
        demback = 0;
        congtru_setting = 0;
        chon_setting();
      }
      else if (demtong == 4) // Chọn setting
      {
        demback = 0;
        congtru_setting = 1;
        chon_setting();
      }  
      else if (demtong > 4)
      {
        demtong = 4;
        demback = 0;
      }
      delay(500);
    }
    macdinh = gtmenu;
  }

  if (gtback != macdinh)    // NÚT BACK
  {  
    if (gtback == 0) // Khi nhấn nút
    {
      button_pressed = true; // 

      demback++;
      if (demback == 1)
      {
        if (demtong == 1 && (congtru_tong == 0 || congtru_tong == 1))
        {
          demtong = demtong - 1;
          demback = 0;
          manhinh();
        }
        else if (demtong == 2 && congtru_tong == 0) // TỪ MENU 1 TRỞ VỀ MENU TỔNG
        { 
          demtong = demtong - 1;
          demback = 0;
          menu_tong();
        }
        else if (demtong == 2 && congtru_tong == 1) // TỪ MENU 2 VỀ MENU TỔNG
        {
          demtong = demtong - 1;
          congtru_tong = congtru_tong - 1; 
          demback = 0;
          menu_tong(); 
        }
        else if (demtong == 3 || demtong == 4) // TỪ MENU 2 VỀ MENU TỔNG
        {
          demtong = 1;
          demback = 0;
          menu_tong();
        }
        else
        {
          demback = 0;
        }
        delay(500);
      }
      macdinh = gtback;
    }      
  }

}

void taskDataCollection(void *pvParameters) {
  char data[50];
  bool fanState = false;
  bool lightState = false;
  bool phunsuongState = false;

  while (true) {
    if (!button_pressed) {
      if (xSemaphoreTake(xSemaphore, portMAX_DELAY)) { 
        int newTemperature = dht.readTemperature();
        int newSoilMoisture = analogRead(14);
        int newPercentage = map(newSoilMoisture, 0 , 4095 , 100, 0);
        if (newPercentage < 0) newPercentage = 0;
        if (newPercentage > 100) newPercentage = 100;
        
        // Kiểm tra sự thay đổi trạng thái của các thiết bị
        bool fanStateChanged = (fanState != fan);
        bool lightStateChanged = (lightState != light);
        bool phunsuongStateChanged = (phunsuongState != phunsuong1);

        if (newTemperature != nhietdo_hientai || newPercentage != percentage || fanStateChanged || lightStateChanged || phunsuongStateChanged) { 
          nhietdo_hientai = newTemperature;
          percentage = newPercentage;
          dataChanged = true;
          fanState = fan;
          lightState = light;
          phunsuongState = phunsuong1;
        }

        if (dataChanged) { // Kiểm tra nếu có dữ liệu mới
          Serial.println(nhietdo_hientai);
          Serial.println(nhietdo_thietlap);
          Serial.print("quat:");
          Serial.println(fan);
          Serial.print("den:");
          Serial.println(light);
          Serial.print("phunsuong:");
          Serial.println(phunsuong1);

          sprintf(data, "%d/%d/%d/%d/%d", nhietdo_hientai, percentage, fan, light, phunsuong1);
          
          Serial2.println(data);
          Serial.println(data);
          dataChanged = false; 
        }

        xSemaphoreGive(xSemaphore);
      }
    }
   
    vTaskDelay(pdMS_TO_TICKS(updateInterval)); 
  }
}

void taskHandleButtons(void *pvParameters) {
  while (1) {
    lcd_button();
    vTaskDelay(pdMS_TO_TICKS(100)); 
  }
}

void taskUpdateLCD(void *pvParameters) {
  while (1) {
    if (dataChanged && demtong == 2 && congtru_tong == 0) { 
      hien_thi();
      dataChanged = false; 
    }
    if (dataChanged &&  demtong == 2 && congtru_tong == 1){
      setting();
      chon_setting();
      dataChanged = false; 
    }

    vTaskDelay(pdMS_TO_TICKS(100)); 
  }
}

void control(void *p) {
   while(1){
  if (nhietdo_hientai < nhietdo_thietlap) {
    digitalWrite(den, HIGH); // Turn on the light
    digitalWrite(quat, LOW); // Turn off the fan
    fan = 0;
    light = 1;
  } else if (nhietdo_hientai >= nhietdo_thietlap) {
    digitalWrite(quat, HIGH); // Turn on the fan
    digitalWrite(den, LOW); // Turn off the light
    fan = 1;
    light = 0;
  } else {
    digitalWrite(den, LOW); // Turn off the light
    digitalWrite(quat, LOW); // Turn off the fan
    fan = 0;
    light = 0;
  }

  if (percentage < doam_thietlap) {
    digitalWrite(phunsuong, HIGH); // Turn on the mist
    phunsuong1 = 1;
  } else if (percentage >= doam_thietlap) {
    digitalWrite(phunsuong, LOW); // Turn off the mist
    phunsuong1 = 0;
  } else {
    digitalWrite(phunsuong, LOW); // Turn off the mist
    phunsuong1 = 0;
  }
   vTaskDelay(1000); 
}
}

void taskSetData(void *pvParameters) {
  int nhietdoweb_new;
  int doamweb_new;
  int nhietdoweb;
  int doamweb;

  while (true) {
    nhietdoweb_new = firebase.getInt("sensorset/Nhietdoset");
    doamweb_new = firebase.getInt("sensorset/Doamset");

    if (nhietdoweb_new != nhietdoweb) {
      nhietdo_thietlap = nhietdoweb_new;
      nhietdoweb = nhietdoweb_new;
      dataChanged = true; 
    }
    if (doamweb_new != doamweb) {
      doam_thietlap = doamweb_new;
      doamweb = doamweb_new;
      dataChanged = true; 
    }
    vTaskDelay(100);
  }
}
void setup() {
  Serial.begin(115200);  
  Serial2.begin(9600, SERIAL_8N1, Rx , Tx);
  lcd.begin();
  lcd.backlight();
  dht.begin();
  pinMode(menu, INPUT);
  pinMode(back, INPUT);
  pinMode(len, INPUT);
  pinMode(xuong, INPUT);
  pinMode(den, OUTPUT);
  pinMode(quat, OUTPUT);
  pinMode(phunsuong, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  manhinh();
  xTaskCreatePinnedToCore(control, "TaskDieukhien", 1000, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(taskDataCollection, "TaskDocNhietDo", 10000, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(taskHandleButtons, "TaskHandleButtons", 10000, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(taskUpdateLCD, "TaskUpdateLCD", 10000, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(taskSetData, "TaskSEtDat",10000, NULL, 1, NULL, 0);
}

void loop() {
  // The loop function can remain empty if all tasks are handled by FreeRTOS
}