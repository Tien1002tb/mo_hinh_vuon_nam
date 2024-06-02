void setup() 
{
  Serial.begin(115200);
}
 
void loop() 
{
  int value = analogRead(14);    
  
  Serial.println(value);
 delay(1000);
}
