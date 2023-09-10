
#define WIFI_SSID               "aonline3g"  //Имя точки доступа WIFI VVK   AndroidAP
#define WIFI_PASS               "1qaz2wsx3edc" //пароль точки доступа WIFI vtb24admin 1234567890
bool isFirstConnection=true;

void ConnectWIFI()
{
  //*******************************************************
  // Запускаем WiFi
    if (WiFi.status() != WL_CONNECTED)// Если нет WiFi, то коннектимся
    {
      
     Serial.println();
     Serial.println();
     Serial.print("Connecting to ");
     Serial.println(WIFI_SSID);
      
      WiFi.begin(WIFI_SSID, WIFI_PASS);

      int8_t count=0;
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        Serial.print(WiFi.status());
        isFirstConnection = false;
         
        count++;
        if (count >= 5){

          Serial.println("WiFi not connected"); break;}
      }

    }
  /*  Дисконект - для справки 
    WiFi.disconnect(); // отключаемся от сети
    
  */
 Serial.println(WiFi.localIP());

}

