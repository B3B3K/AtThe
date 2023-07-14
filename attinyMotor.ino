#include "DHT.h"
#include <TinyWireM.h>
#include <Tiny4kOLED.h>

const unsigned char  img_thermometer[] PROGMEM = {
  0x00, 0xfe, 0x03, 0xfe, 0x50,
  0x00, 0xff, 0x00, 0xff, 0x55,
  0x60, 0x9f, 0x80, 0x9f, 0x65,
};
#define DHTTYPE DHT11
DHT dht(PB3, DHTTYPE);

float getTemperature() {
  return dht.readTemperature();
}
float getHumidity() {
  return dht.readHumidity();
}
void setup() {
  dht.begin();
  pinMode(PB1, OUTPUT);
  oled.begin(128, 64, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);
  oled.setFont(FONT8X16);
  oled.clear();
  oled.on();
  delay(3000);

}

void loop() {

  float temperature = getTemperature();
  float humidity = getHumidity();
  
  if (temperature > 20 and temperature < 25) {
    digitalWrite(PB1, HIGH);

  }
  if (temperature > 25 and temperature < 50) {
    digitalWrite(PB1, HIGH);
  }
  if (temperature < 20) {
    digitalWrite(PB1, LOW);
    
  }
  oled.setCursor(15, 4);
  oled.print("Temp: ");
  oled.print(" °C  ");
  oled.print(temperature, 1);
  oled.setCursor(15, 6);
  oled.print("Humi: ");
  oled.print(humidity, 1);
  oled.print(" %  ");
  oled.bitmap(2, 5, 7, 8, img_thermometer);
  oled.on();
  delay(1000);
  oled.clear();

}
