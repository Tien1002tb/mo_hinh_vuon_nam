#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define AOUT_PIN 36 // cam bien do am dat
const int max_kho = 3000;   
const int max_am = 1000;  

#define DHTPIN 4    // D4
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);
void lcd_button();
const int menu = 16; 
const int back = 17; 
const int len = 19; 
const int xuong = 18; 
int gtmenu, gtback, gtlen, gtxuong;
int macdinh = 1;
int congtru_tong = 0;
int demback = 0;
int demtong = 0;

int congtru_setting = 0; // 0: Thiết lập nhiệt độ, 1: Thiết lập độ ẩm

int nhietdo_hientai = 25; 
int nhietdo_thietlap = 22; 
int doam_hientai = 22;
int doam_thietlap = 50;
int percentage = 0; 

bool button_pressed = false; // Biến cờ để kiểm soát việc đọc nhiệt độ và độ ẩm
unsigned long lastUpdateTime = 0; // Biến lưu thời gian lần cập nhật cuối cùng
const unsigned long updateInterval = 2000; // Khoảng thời gian cập nhật (2 giây)

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

void hien_thi() // HIỂN THỊ NHIỆT ĐỘ
{ 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nhiet do :");
  lcd.setCursor(10,0);
  lcd.print(nhietdo_hientai);
  lcd.setCursor(13, 0);
  lcd.print("*C");

  lcd.setCursor(0, 1);
  lcd.print("Do am :");
  lcd.setCursor(7,1);
  lcd.print(percentage);
  lcd.setCursor(10, 1);
  lcd.print("%");
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

  Serial.print("Đếm tổng: "); Serial.print(demtong); Serial.print("    ");
  Serial.print("+/- tổng: "); Serial.print(congtru_tong); Serial.print("    ");
  Serial.print("Đếm back: "); Serial.print(demback); Serial.print("    ");
  Serial.print("TRANG THAI SET: "); Serial.print(congtru_setting); Serial.println("    ");
}



void taskDataCollection(void *pvParameters) {
  while (true) {
    // Thu thập dữ liệu từ cảm biến và xử lý nút
    nhietdo_hientai = dht.readTemperature();  
    doam_hientai = analogRead(AOUT_PIN); 
    percentage = map(doam_hientai, max_kho, max_am, 100, 0);
    if (percentage < 0) percentage = 0;
    if (percentage > 100) percentage = 100; 
    //firebase.setFloat("sensor/Nhietdo", nhietdo_hientai);
   // firebase.setFloat("sensor/Doam", doam_hientai);
    vTaskDelay(pdMS_TO_TICKS(updateInterval)); // Đợi khoảng thời gian cập nhật
  }
}

void taskHandleButtons(void *pvParameters) {
  while (1) {
    lcd_button();
    vTaskDelay(pdMS_TO_TICKS(100)); // Poll buttons every 100ms
  }
}

void taskUpdateLCD(void *pvParameters) {
  while (1) {
    if (demtong == 2 && congtru_tong == 0) { // If in display mode
      hien_thi();
    }
    vTaskDelay(pdMS_TO_TICKS(updateInterval)); // Update LCD every update interval
  }
}

void setup() {
  Serial.begin(115200);  
  lcd.begin();
  lcd.backlight();
  dht.begin();
  pinMode(menu, INPUT);
  pinMode(back, INPUT);
  pinMode(len, INPUT);
  pinMode(xuong, INPUT);
  manhinh();

  // Create tasks and pin them to core 1
  xTaskCreatePinnedToCore(taskDataCollection, "TaskDocNhietDo", 10000, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(taskHandleButtons, "TaskHandleButtons", 10000, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(taskUpdateLCD, "TaskUpdateLCD", 10000, NULL, 1, NULL, 1);
}

void loop() {
  // The loop function can remain empty if all tasks are handled by FreeRTOS
}
