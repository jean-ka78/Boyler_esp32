#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include "link.h"
#include <EEPROM.h>
#include "GyverFilters.h"
#include "st_enum.h"
#include "NTC.h"
#include "NTC_LIB.h"
    
float T_boyler, T_koll, T_bat, T_out;
bool hand_up, hand_down;

bool isFirstConnection=true;

// put function declarations here:

int thermistorPin1 = 33;// Вход АЦП, выход делителя напряжения
int thermistorPin2 = 32;
int thermistorPin3 = 35;
int old_len = 0;

#define PID

const int relay = 21;
const int nasos_otop = 19;
int PIN_LOW = 22;
int PIN_HIGH = 23;
uint32_t tmr;
bool flag = HIGH;

long rssi;
unsigned long timer_1, old_time, old_time1, old_time2, old_time3, timer4;
NTC kollektor(thermistorPin1);
NTC boyler(thermistorPin2);
NTC bat(thermistorPin3);
#include "heat_regul.h"
#include "obogrev.h"
#include "pid.h"
#include "mqtt.h"
// Вибір алгоритму зчитування 
// #define NTC



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
  setup_ntc();
  // boolean ok2 = EEPROM.commit();
  // isFirstConnection = false;
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

  // if (millis() - timer_1>1000)
  //   {
  //     timer_1 = millis();
  //     ConnectWIFI();
  //   }
 unsigned long real_time = millis();
  // if (real_time - old_time>2000)
  //   {
  //     old_time = real_time;

     
  //   }
    if (real_time - old_time1>10000)
    {
      old_time1 = real_time;
     
      Safe_eeprom();
    }
    
    if (real_time - old_time2>1000)
    {
      old_time2 = real_time;
      reconnect();
    }

    if (real_time - old_time3 > 2000)
    {
      old_time3 = real_time;
      #ifdef NTC
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
    
    // if (run_mb)    {
    
    // if (real_time - timer4 > 10000)
    // {
    //   timer4 = real_time;
      
    
    //   EEPROM.begin(sizeof(st_Enum));
    //   EEPROM.put(0, eeprom);
    //   delay(50);
    //   EEPROM.commit();
      
    //   // Serial.println("eeprom write: " + String(eeprom.temp_u_b));
     
    // }
    // }


#ifdef PID
loop_pid();
#else
  regulator(T_koll, eeprom.temp_u_b, T_bat, eeprom.temp_off_otop);
#endif
loopMQtt();
    regul();
}


