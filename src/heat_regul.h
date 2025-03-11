// #include "pid.h"
 bool nasos = false;
bool logic(bool heat_on, float Temp_boy, float Temp_kol, float temp_u, float gis)
{
   
    float temp_on;
    
         temp_on = temp_u;
    if (heat_on)
    {
        if (Temp_boy<(temp_on+gis) && !nasos)
        {
           nasos = true;
       

        }
        else if (Temp_boy > temp_on && nasos)
        {
            nasos = false;
            
        }
        
    }
    else
    {
        nasos = false;
        
       
      
        }
    return nasos;

}

#include <Arduino.h>

// bool nasos = false;
unsigned long lastCheckTime = 0;
float lastTempBoy = 0;
bool waiting = false;
unsigned long waitingStartTime = 0;

bool logic_new(bool heat_on, float Temp_boy, float Temp_kol, float temp_u, float gis)
{
    float temp_on = temp_u;
    unsigned long currentTime = millis();
    
    if (heat_on)
    {
        if (!waiting)
        {
            if (Temp_boy < (temp_on + gis) && !nasos)
            {
                nasos = true;
                lastCheckTime = currentTime;
                lastTempBoy = Temp_boy;
            }
            else if (Temp_boy > temp_on && nasos)
            {
                nasos = false;
            }
            
            // Перевіряємо, чи температура не змінюється протягом 10 хвилин
            if (nasos && (currentTime - lastCheckTime >= 600000)) // 10 хвилин
            {
                if (Temp_boy <= lastTempBoy) // Температура не зросла
                {
                    nasos = false;
                    waiting = true;
                    waitingStartTime = currentTime; // Запам'ятовуємо час початку очікування
                }
                else
                {
                    lastCheckTime = currentTime;
                    lastTempBoy = Temp_boy;
                }
            }
        }
        else if (waiting)
        {
            // Чекаємо ще 10 хвилин перед повторною спробою
            if (currentTime - waitingStartTime >= 600000)
            {
                waiting = false;
            }
        }
    }
    else
    {
        nasos = false;
        waiting = false;
    }
    
    return nasos;
}
