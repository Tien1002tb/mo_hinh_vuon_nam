#define AOUT_PIN 36 // ESP32 pin GPIO36 (ADC0) that connects to AOUT pin of moisture sensor

// Giá trị đo được khi cảm biến ở trong không khí
const int AirValue = 3000;   
// Giá trị đo được khi cảm biến ở trong nước
const int WaterValue = 1000;  

void setup() {
  Serial.begin(9600); // Mở cổng serial với tốc độ 9600 bps
}

void loop() {
  int value = analogRead(AOUT_PIN); // Đọc giá trị analog từ cảm biến

  Serial.print("Moisture value: ");
  Serial.println(value);

  // Chuyển đổi giá trị sang phần trăm độ ẩm
  int percentage = map(value, WaterValue, AirValue, 100, 0);
  if (percentage < 0) percentage = 0;
  if (percentage > 100) percentage = 100;

  Serial.print("Soil Moisture (%): ");
  Serial.println(percentage);

  delay(500); // Dừng chương trình trong 500 milliseconds trước khi lặp lại
}
