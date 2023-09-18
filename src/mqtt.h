#include <PubSubClient.h>
// #include "json.h"
#include <ArduinoJson.h> 

const size_t capacity_post = JSON_ARRAY_SIZE(7) + JSON_OBJECT_SIZE(1) + 7*JSON_OBJECT_SIZE(2);
DynamicJsonDocument doc_post(capacity_post);
//MQTT Server
const char *mqtt_server = "greenhouse.net.ua"; // Имя сервера MQTT
const int mqtt_port = 1883; // Порт для подключения к серверу MQTT
const char *mqtt_user = "mqtt_boyler"; // Логин от сервер
const char *mqtt_pass = "qwerty"; // Пароль от сервера
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
char msg1[MSG_BUFFER_SIZE];
char msg3[MSG_BUFFER_SIZE];
int value = 0;



#define state_topic "home/boy_on/state" 
#define inTopic "home/#"
// 
// MQTT topics
const char* CURRENT_TEMP_GET_BOY = "home/boy_on/current-temperature/get";
const char* CURRENT_TEMP_SET_BOY = "home/boy_on/current-temperature/set";
const char* TEMP_SETPOINT_GET_BOY = "home/boy_on/setpoint-temperature/get";
const char* TEMP_SETPOINT_SET_BOY = "home/boy_on/setpoint-temperature/set";
const char* MODE_GET_TOPIC_BOY = "home/boy_on/mode/get";
const char* MODE_GET_NASOS_BOY = "home/boy_on/mode/nasos";
const char* MODE_SET_TOPIC_BOY = "home/boy_on/mode/set";
const char* TEMP_BOILER_GET_TOPIC = "home/boy_on/boiler-temperature/get";
const char* TEMP_BOILER_TARGET_GET_TOPIC = "home/boy_on/boiler-target-temperature/get";
const char* TEMP_BOILER_GIS = "home/boy_on/gis-temperature/get";

const char* CURRENT_TEMP_GET_HEAT = "home/heat_on/current-temperature/get";
const char* CURRENT_TEMP_SET_HEAT = "home/heat_on/current-temperature/set";
const char* CURRENT_TEMP_SET_PID = "home/heat_on/current-temperature/set_pid";
const char* TEMP_SETPOINT_GET_HEAT = "home/heat_on/setpoint-temperature/get";
const char* TEMP_SETPOINT_SET_HEAT = "home/heat_on/setpoint-temperature/set";
const char* MODE_GET_TOPIC_HEAT = "home/heat_on/mode/get";
const char* MODE_SET_TOPIC_HEAT = "home/heat_on/mode/set";
const char* MODE_GET_NASOS_HEAT = "home/heat_on/mode/nasos";
const char* TEMP_HEAT_GET_TOPIC = "home/heat_on/boiler-temperature/get";
const char* TEMP_HEAT_OFF_TOPIC = "home/heat_on/boiler-temperature/off";
const char* TEMP_HEAT_TARGET_GET_TOPIC = "home/heat_on/boiler-target-temperature/get";
const char* TIME_HEAT_CIKL = "home/heat_on/setpoint-time/cikl";
const char* TIME_HEAT_IMPULS = "home/heat_on/setpoint-time/impuls";
const char* TEMP_MIN_OUT = "home/heat_on/temp_min_out";
const char* TEMP_MAX_OUT = "home/heat_on/temp_max_out";
const char* TEMP_MAX_HEAT = "home/heat_on/temp_max_heat";
const char* KOF_P = "home/heat_on/kof_p";
const char* KOF_I = "home/heat_on/kof_i";
const char* KOF_D = "home/heat_on/kof_d";
const char* TEMP_DEAD_ZONE = "home/heat_on/dead_zone";
const char* VALVE_UP = "home/heat_on/valve/up";
const char* VALVE_DOWN = "home/heat_on/valve/down";
const char* VALVE_MODE = "home/heat_on/valve/mode";
const char* TEMP_OUT = "home/heat_on/temp_out";
const char* HAND_UP = "home/heat_on/hand_up";
const char* HAND_DOWN = "home/heat_on/hand_down";


float temp_boy,
      temp_heat,
      temp_koll;
const String modeSetTopic(MODE_SET_TOPIC_BOY);
float temp = 0.00;
float hum = 0.00;
float tempDiff = 0.2;
float humDiff = 1.0;
int sensorTakt = 2000; //alle 2 Sekunden wird der Sensor ausgelesen
// long lastMsg = 0;
// char msg[50];
// int value = 0;
unsigned long oldmillis;
WiFiClient espClient;
PubSubClient client(espClient);
// long lastMsg = 0;  
                                                    // вызывается когда приходят данные от брокера
void callback(char* topic, byte* payload, unsigned int length) {
  // Serial.print("Message arrived on topic: ");
  // Serial.print(topic);
  // Serial.println(". Message: ");

payload[length] = '\0';
String message = (char*)payload;

   if (strcmp(topic, MODE_SET_TOPIC_BOY) == 0){
     if (message == "heat"){
    eeprom.boy_state = true;
    // client.publish(MODE_GET_TOPIC_BOY, "heat");
    Serial.println("Heat: "+String(eeprom.boy_state));
   }else if (message == "off")
   {
    eeprom.boy_state = false;
   
    // client.publish(MODE_GET_TOPIC_BOY, "off");
    Serial.println("Heat: "+String(eeprom.boy_state));
    
   }
     
  }else if (strcmp(topic, TEMP_SETPOINT_SET_BOY) == 0){
    float temp_boy = message.toFloat();
    eeprom.temp_u = temp_boy;
    Serial.println("Ustavka Boyler: "+String(eeprom.temp_u));
  }
  // 

  if (strcmp(topic, MODE_SET_TOPIC_HEAT) == 0){
     if (message == "heat"){
    eeprom.heat_state = true;
    // client.publish(MODE_GET_TOPIC_HEAT, "heat");
    Serial.println("Heat_otop: "+String(eeprom.heat_state));
   }else if (message == "off")
   {
    eeprom.heat_state = false;
        // client.publish(MODE_GET_TOPIC_HEAT, "off");
    Serial.println("Heat: "+String(eeprom.heat_state));
 

   } }else if (strcmp(topic, TEMP_SETPOINT_SET_HEAT) == 0){
    float temp_heat = message.toFloat();
    eeprom.temp_u_b = temp_heat;
    Serial.println("Ustavka Otopl: "+String(eeprom.temp_u_b));

  }else if (strcmp(topic, TEMP_BOILER_GIS) == 0){
    float temp_gis = message.toFloat();
    eeprom.gis_boy = temp_gis;
    Serial.println("GIS Otopl: "+String(eeprom.gis_boy));

  }else if (strcmp(topic, TIME_HEAT_CIKL) == 0){
    int time_cikl = message.toInt();
    eeprom.per_off = time_cikl;
    High.OffTime = eeprom.per_off;
    Low.OffTime = eeprom.per_off;
    Serial.println("cikl Otopl: "+String(eeprom.per_off));

  }else if (strcmp(topic, TIME_HEAT_IMPULS) == 0){
    int time_imp = message.toInt();
    eeprom.per_on = time_imp;
    High.OnTime = eeprom.per_on;
    Low.OnTime = eeprom.per_on;
    Serial.println("impuls Otopl: "+String(eeprom.per_on));

  }else if (strcmp(topic, TEMP_HEAT_OFF_TOPIC) == 0){
    float temp_off = message.toFloat();
    eeprom.temp_off_otop = temp_off;
    Serial.println("temp_off Otopl: "+String(eeprom.temp_off_otop));
    
  }else if (strcmp(topic, TEMP_MIN_OUT) == 0){
    float temp_min_out = message.toFloat();
    eeprom.temp_min_out = temp_min_out;
    // Serial.println("temp_off Otopl: "+String(eeprom.temp_off_otop));
 
  }else if (strcmp(topic, TEMP_MAX_OUT) == 0){
    float temp_max_out = message.toFloat();
    eeprom.temp_max_out = temp_max_out;
    // Serial.println("temp_off Otopl: "+String(eeprom.temp_off_otop));
  
  }else if (strcmp(topic, TEMP_MAX_HEAT) == 0){
    float temp_max_heat = message.toFloat();
    eeprom.temp_max_heat = temp_max_heat;
    // Serial.println("temp_off Otopl: "+String(eeprom.temp_off_otop));
  
  }else if (strcmp(topic, KOF_P) == 0){
    float kof_p = message.toFloat();
    eeprom.kof_p = kof_p;

  }else if (strcmp(topic, KOF_I) == 0){
    float kof_i = message.toFloat();
    eeprom.kof_i = kof_i;
  
  }else if (strcmp(topic, KOF_D) == 0){
    float kof_d = message.toFloat();
    eeprom.kof_d = kof_d;
  
  }else if (strcmp(topic, TEMP_DEAD_ZONE) == 0){
    float dead_zone = message.toFloat();
    eeprom.dead_zone = dead_zone;
 
  }else if (strcmp(topic, TEMP_OUT) == 0){
    float temp_out = message.toFloat();
    T_out = temp_out;
 
  }else if (strcmp(topic, VALVE_MODE) == 0){
    if (message == "on"){
    eeprom.valve_mode = true;}
    else if (message == "off")
    {eeprom.valve_mode = false;}
    
  }else if (strcmp(topic, HAND_UP) == 0){
    if (message == "on"){
    hand_up = true;}
    else if (message == "off") {hand_up = false;}
    
  }else if (strcmp(topic, HAND_DOWN) == 0){
    if (message == "on"){
    hand_down = true;}
    else if (message == "off") {hand_down = false;}
    
  }



EEPROM.put(0, eeprom);
}



void setupMqtt() {  
  
  client.setServer(mqtt_server, mqtt_port); 
  client.subscribe(inTopic);          // указываем адрес брокера и порт
  client.setCallback(callback); 
  // указываем функцию которая вызывается когда приходят данные от брокера
}

void reconnect() {                                                      

 if (WiFi.status() != WL_CONNECTED){

   ConnectWIFI();
  }
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    client.setServer(mqtt_server, 1883);
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe(inTopic);
      client.setCallback(callback); 
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
    //   delay(5000);
    }
  
}

// 

}

void getValues() {

 dtostrf(T_boyler,2,2,msg);
    client.publish(CURRENT_TEMP_GET_BOY, msg);
dtostrf(T_bat,2,2,msg);
    client.publish(CURRENT_TEMP_GET_HEAT, msg);
    
JsonArray tags = doc_post.createNestedArray("tags");
JsonObject tags_0 = tags.createNestedObject();

tags_0["koll"] = T_koll;
tags_0["RSS"] = rssi;
JsonObject tags_1 = tags.createNestedObject();
tags_1["boy"] = T_boyler;
JsonObject tags_2 = tags.createNestedObject();
tags_2["bat"] = T_bat;


char output[256];
size_t n = serializeJson(doc_post, output);
client.publish("home/temp_json", output,n);
doc_post.clear();

// 
// snprintf (msg, MSG_BUFFER_SIZE, "%ld", rssi);
    // client.publish("outTopic/rssi",msg);
// snprintf (msg, MSG_BUFFER_SIZE, "%ld", String(eeprom.temp_u_b).c_str());

}

void SendData(){


dtostrf(eeprom.temp_u,2,2,msg);
    client.publish(TEMP_SETPOINT_GET_BOY, msg);
dtostrf(eeprom.temp_u_b,2,2,msg);
    client.publish(TEMP_SETPOINT_GET_HEAT, msg);
dtostrf(eeprom.temp_off_otop,2,2,msg);    
     client.publish(TEMP_HEAT_OFF_TOPIC, msg);
dtostrf(eeprom.gis_boy,2,2,msg);    
     client.publish(TEMP_BOILER_GIS, msg);

snprintf (msg, MSG_BUFFER_SIZE, "%ld", eeprom.per_on);
// dtostrf(eeprom.per_on,2,2,msg);    
     client.publish(TIME_HEAT_IMPULS, msg);
snprintf (msg, MSG_BUFFER_SIZE, "%ld", eeprom.per_off);
// dtostrf(eeprom.per_on,2,2,msg);    
     client.publish(TIME_HEAT_CIKL, msg);
dtostrf(T_SET_67293872_1,2,2,msg);
    client.publish(CURRENT_TEMP_SET_PID, msg);



if (eeprom.boy_state)
{
  client.publish(MODE_GET_TOPIC_BOY, "heat");
  /* code */
} else {
client.publish(MODE_GET_TOPIC_BOY, "off");
}

if (eeprom.heat_state)
{
  client.publish(MODE_GET_TOPIC_HEAT, "heat");
  /* code */
}
else{
  client.publish(MODE_GET_TOPIC_HEAT, "off");
}

if (eeprom.heat_otop)
{
  client.publish(MODE_GET_NASOS_HEAT, "on");
}else {client.publish(MODE_GET_NASOS_HEAT, "off");}

if (eeprom.heat)
{
  client.publish(MODE_GET_NASOS_BOY, "on");
  
}else {client.publish(MODE_GET_NASOS_BOY, "off");}


if (eeprom.valve_mode)
{
  /* code */


if (DOWN_147944907_1)
{
  client.publish(VALVE_DOWN, "on");
}else {client.publish(VALVE_DOWN, "off");}

if (UP_147944907_1)
{
  client.publish(VALVE_UP, "on");
}else {client.publish(VALVE_UP, "off");}

}


}


void loopMQtt() {

   
  if (!client.connected()) {                             // проверяем подключение к брокеру
    reconnect();                                            // еще бы проверить подкючение к wifi...
  }
  client.loop();
     
}