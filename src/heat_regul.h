bool logic(bool heat_on, float Temp_boy, float Temp_kol, float temp_u, float gis)
{
    bool nasos = false;
    float temp_on;
    if (Temp_kol<temp_u)
    {
        temp_on = Temp_kol;
    }
    else
    {
        temp_on = temp_u;
    }
        //  temp_on = temp_u;
    if (heat_on)
    {
        if (Temp_boy<(temp_on+gis))
        {
           nasos = true;
        //    led1.on();
    //    heat_otop = LOW;

        }
        if (Temp_boy > (temp_on-gis))
        {
            nasos = false;
            // heat_otop = HIGH;
            
            // led1.off();
        }
        
    }
    else
    {
        nasos = false;
        
        // heat_otop = HIGH;
      
        }
    return nasos;

}