// #include "pid.h"
 bool nasos = false;
bool logic(bool heat_on, float Temp_boy, float Temp_kol, float temp_u, float gis)
{
   
    float temp_on;
    // if (Temp_kol<temp_u)
    // {
    //     temp_on = Temp_kol;
    // }
    // else
    // {
    //     temp_on = temp_u;
    // }
         temp_on = temp_u;
    if (heat_on)
    {
        if (Temp_boy<(temp_on+gis) && !nasos)
        {
           nasos = true;
        //    led1.on();
    //    eeprom.heat_otop = LOW;
        turnNasosOff();

        }
        else if (Temp_boy > temp_on && nasos)
        {
            nasos = false;
            // eeprom.heat_otop = HIGH;
            turnNasosOn();
            
            // led1.off();
        }
        
    }
    else
    {
        nasos = false;
        
        // eeprom.heat_otop = HIGH;
        turnNasosOn();
      
        }
    return nasos;

}