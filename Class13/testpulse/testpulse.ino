/*
  AnalogReadSerial
 Reads an analog input on pin 0, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */
void setup() {
  Serial.begin(115200);
}
 
void loop() {
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  delay_x(5);
}
 
void delay_x(uint32_t millis_delay)
{
  uint16_t micros_now = (uint16_t)micros();
 
  while (millis_delay > 0) {
    if (((uint16_t)micros() - micros_now) >= 1000) {
      millis_delay--;
      micros_now += 1000;
    }
  }  
}
