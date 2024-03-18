#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include "link.h"
#include <EEPROM.h>
#include "GyverFilters.h"
#include "st_enum.h"
#include "NTC.h"
#include "NTC_LIB.h"
#include "heat_regul.h"
#include "obogrev.h"
#define PID
#include "pid.h"
#include "test_pid.h"
#include "mqtt.h"

    



bool isFirstConnection=true;

// put function declarations here:

int thermistorPin1 = 33;// Вход АЦП, выход делителя напряжения
int thermistorPin2 = 32;
int thermistorPin3 = 35;
int old_len = 0;



// #define LIB_NTC // Вибір алгоритму зчитування 

   
  NTC kollektor(thermistorPin1);
  NTC boyler(thermistorPin2);
  NTC bat(thermistorPin3);

uint32_t tmr;
bool flag = HIGH;


unsigned long timer_1, old_time, old_time1, old_time2, old_time3, timer4, timer5;





void regul()
{
bool relle;
relle = logic(eeprom.boy_state,T_boyler,T_koll,eeprom.temp_u, eeprom.gis_boy);
eeprom.heat = relle;

digitalWrite(relay,eeprom.heat);

}

void setup() {
  Serial.begin(115200);
  setupMqtt();
  setup_pid();
  pinMode(relay, OUTPUT);
  pinMode(PIN_LOW, OUTPUT);
  pinMode(PIN_HIGH, OUTPUT);
  pinMode(nasos_otop, OUTPUT);
  first_start();
  // ---------------------------------------
 #ifdef LIB_NTC
 
  setup_ntc();
#else
setup_mtc();
 
  #endif
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
  rssi =  map(WiFi.RSSI(), -115, -35, 0, 100);

  if (millis() - timer_1>2000)
    {
      timer_1 = millis();
      #ifdef LIB_NTC
      T_koll = t_kollektor->readCelsius();
      T_bat = t_otop->readCelsius();
      T_boyler = t_boyler->readCelsius();
      #else
      T_bat = bat.Update_f();
      T_boyler =  boyler.Update_f();
      T_koll = kollektor.Update_f();
      #endif
      SendData();
      getValues(); 

     }

    
    if (millis() - old_time2>1000)
    {
      old_time2 = millis();
      reconnect();
    }

    // if (millis() - old_time3 > 2000)
    // {
    //   old_time3 = millis();
      
    //   SendData();
    //   getValues();      
    // }
    


#ifdef PID
loop_pid();
#else
  // regulator(T_koll, eeprom.temp_u_b, T_bat, eeprom.temp_off_otop);
  loop_test_pid();
#endif
loopMQtt();
    regul();



    if (millis() - old_time1>10000)
    {
      old_time1 = millis();
     
      Safe_eeprom();
    }
}


