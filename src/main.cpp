#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include "link.h"
#include <EEPROM.h>
#include "GyverFilters.h"
#include "st_enum.h"
#include "NTC.h"

// put function declarations here:

int thermistorPin1 = 33;// Вход АЦП, выход делителя напряжения
int thermistorPin2 = 32;
int thermistorPin3 = 35;
const int relay = 21;
const int nasos_otop = 19;
int PIN_LOW = 22;
int PIN_HIGH = 23;
uint32_t tmr;
bool flag = HIGH;
float T_boyler, T_koll, T_bat;
long rssi;
unsigned long timer_1;
NTC kollektor(thermistorPin1);
NTC boyler(thermistorPin2);
NTC bat(thermistorPin3);
#include "heat_regul.h"
#include "obogrev.h"
#include "mqtt.h"



void regul()
{
bool relle;
relle = logic(eeprom.heat,T_boyler,T_koll,eeprom.temp_u, eeprom.gis_boy);
digitalWrite(relay,relle);
}

void setup() {
  Serial.begin(115200);
 setupMqtt();

 pinMode(relay, OUTPUT);
  pinMode(PIN_LOW, OUTPUT);
  pinMode(PIN_HIGH, OUTPUT);
  pinMode(nasos_otop, OUTPUT);
  EEPROM.begin(sizeof(st_Enum));
  EEPROM.put(0, eeprom);
// --------------------------------------
// Заводские настройки 
  eeprom.temp_u = 50;
  eeprom.temp_u_b = 50;
  eeprom.temp_off_otop = 35;
  eeprom.gis_boy = -5;
  eeprom.heat = true;
  eeprom.heat_otop = true;
  eeprom.per_on = 10;
  eeprom.per_off = 60;
  EEPROM.put(0, eeprom);
  // ---------------------------------------

   boolean ok2 = EEPROM.commit();
  ConnectWIFI();

  ArduinoOTA.setHostname("ESP32"); // Задаем имя сетевого порта
  ArduinoOTA.begin(); 
  digitalWrite(PIN_LOW,HIGH);
  digitalWrite(PIN_HIGH,HIGH);
  digitalWrite(relay,LOW);
  digitalWrite(nasos_otop, LOW);

}

void loop() {
  ArduinoOTA.handle(); // Всегда готовы к прошивке
if (isFirstConnection)
  {
  EEPROM.get(0, eeprom);
  // Blynk.syncAll(); 
  // if (Blynk.connected()){ 

  // }
  }
  if (millis() - timer_1>1000)
    {
      timer_1 = millis();
      ConnectWIFI();

    }
}


