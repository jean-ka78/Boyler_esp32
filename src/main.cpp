#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include "link.h"
// put function declarations here:

unsigned long timer_1;
int myFunction(int, int);

void setup() {
  Serial.begin(115200);
  ArduinoOTA.setHostname("ESP32"); // Задаем имя сетевого порта
  ArduinoOTA.begin(); 
  

}

void loop() {
  ArduinoOTA.handle(); // Всегда готовы к прошивке

  if (millis() - timer_1>1000)
    {
      timer_1 = millis();
      ConnectWIFI();

    }
}


