
#include <EEPROM.h>
#include "GyverTimer.h"
GTimer isTimer(MS);  

bool table_0_1_D[5];
float T_OUT;
float T_X1;
float T_Y1;
float T_X2;
float T_Y2;
float T_SET;
bool ON_OFF;
bool AUTO_HAND;
bool HAND_UP;
bool HAND_DOWN;
float SET_VALUE;
float PRESENT_VALUE;
bool PULSE_100MS;
float CYCLE;
float VALVE;
float K_P;
float K_I;
float K_D;
float DEAD_ZONE;
bool UP;
bool DOWN;
float TIMER_PID; // Внутренний таймер ПИД
float E_1; // Текущее рассогласование
float E_2; // Рассогласование на -1 шаг
float E_3; // Рассогласование на -2 шага
float D_T; // Время воздействия на текущем шагу регулирования
float SUM_D_T; // Накопленное время воздействия
float TIMER_PID_UP; // Накопленное время открытия
float TIMER_PID_DOWN; // Накопленное время закрытия
boolean PID_PULSE; // Шаг выполнения 1 цикла
bool _gtv1; //Импульс при старте программы
bool _gtv2; //Импульст 100 мс
bool _trgrt1 = 0;
bool _trgrt1I = 0;
bool _changeNumber5_Out = 0;
float _changeNumber5_OLV;
bool _SEEPR10OSN = 0;
bool _changeNumber4_Out = 0;
float _changeNumber4_OLV;
bool _SEEPR9OSN = 0;
bool _changeNumber3_Out = 0;
float _changeNumber3_OLV;
bool _SEEPR8OSN = 0;
bool _SEEPR1OSN = 0;
bool _gen1I = 0;
bool _gen1O = 0;
unsigned long _gen1P = 0UL;
bool _changeNumber2_Out = 0;
float _changeNumber2_OLV;
bool _SEEPR7OSN = 0;
bool _changeNumber1_Out = 0;
float _changeNumber1_OLV;
bool _SEEPR6OSN = 0;
bool _SEEPR5OSN = 0;
unsigned long _d18x2x2Tti = 0UL;
float _d18x2x2O = 0.00;
bool _SEEPR4OSN = 0;
bool _BitChange_1_OldSt = 0;
bool _BitChange_1_Out = 0;
bool _changeNumber10_Out = 0;
float _changeNumber10_OLV;
bool _changeNumber9_Out = 0;
float _changeNumber9_OLV;
bool _SEEPR3OSN = 0;
bool _SEEPR2OSN = 0;
unsigned long _d18x2x1Tti = 0UL, timer;
float _d18x2x1O = 0.00;
bool _trgrt2 = 0;
bool _trgrt2I = 0;
bool _changeNumber8_Out = 0;
float _changeNumber8_OLV;
bool _changeNumber7_Out = 0;
float _changeNumber7_OLV;
bool _changeNumber6_Out = 0;
float _changeNumber6_OLV;
bool _SEEPR11OSN = 0;
bool _tempVariable_bool;
float _tempVariable_float;
void setup_pid()
{
 
    isTimer.setInterval(50);

}
void loop_pid()
{
    // Slave_1_0.pool();
    //Плата:1
//Наименование:Импульсы времени
    if (1) 
    {
         if (_trgrt1I) 
        {
             _trgrt1 = 0;
        }
         else 
        {
            _trgrt1 = 1;
            _trgrt1I = 1;
        }
    }
     else 
    {
        _trgrt1 = 0;
        _trgrt1I = 0;
    }
    ;
    _gtv1 = _trgrt1;
    if (1) 
    {
         if (! _gen1I) 
        {
            _gen1I = 1;
            _gen1O = 1;
            _gen1P = millis();
        }
    }
     else 
    {
        _gen1I = 0 ;
        _gen1O= 0;
    }
    if (_gen1I) 
    {
           if (millis() - timer>50)
    
      
        {
              timer = millis();
             _gen1P = millis();
            _gen1O = ! _gen1O;
        }
    }
    if (_gen1O) 
    {
         if (_trgrt2I) 
        {
             _trgrt2 = 0;
        }
         else 
        {
            _trgrt2 = 1;
            _trgrt2I = 1;
        }
    }
     else 
    {
        _trgrt2 = 0;
        _trgrt2I = 0;
    }
    ;
    _gtv2 = _trgrt2;

    T_OUT = T_out;
    T_X1 = eeprom.temp_min_out;
    T_Y1 = eeprom.temp_max_heat;
    T_X2 = eeprom.temp_max_out;
    T_Y2 = eeprom.temp_off_otop;
    // График отопления
    if (T_OUT <= T_X1)  // Верхняя срезка
    {
        T_SET = T_Y1;
    }
    if (T_OUT > T_X1 & T_OUT < T_X2)  // График между верхней и нижней срезкой
    {
        if (T_X1 == T_X2)  // Деление на 0
        {
            T_X1 = T_X1 + 0.1;
        }
        T_SET = (T_OUT - T_X1) * (T_Y1 - T_Y2) / (T_X1 - T_X2) + T_Y1;
    }
    if (T_OUT >= T_X2)  // Нижняя срезка
    {
        T_SET = T_Y2;
    }
    _tempVariable_float = T_SET;
    
    // Slave_1_0.saveFloat(_tempVariable_float, 4, 14);
    //Плата:5
//Наименование:Регулирование
    ON_OFF = eeprom.heat_otop;
    AUTO_HAND = eeprom.valve_mode;
    HAND_UP = hand_up;
    HAND_DOWN = hand_down;
    SET_VALUE = _tempVariable_float;
    PRESENT_VALUE = T_bat;
    PULSE_100MS = _gtv2;
    CYCLE = eeprom.per_on;
    VALVE = eeprom.per_off;
    K_P = eeprom.kof_p;
    K_I = eeprom.kof_i;
    K_D = eeprom.kof_d;
    DEAD_ZONE = eeprom.dead_zone;
    E_1 =  SET_VALUE -  PRESENT_VALUE; // Текущее рассогласование температуры
    if  (K_I == 0.0)  // Деление на 0
    {
        K_I = 9999.0;
    }
    if  (CYCLE == 0.0)  // Деление на 0
    {
        CYCLE = 1.0;
    }
    // Ограничения
    K_P = constrain(K_P, (-99.0), (99.0)); // Кр -99.0...99.0 %/С, знак + для нагревателя, знак - для холодильника
    K_I = constrain(K_I, (1.0), (9999.0)); // Ти 1...9999.0 сек
    K_D = constrain(K_D, (0.0), (9999.0)); // Тд 0...9999.0 сек
    CYCLE = constrain(CYCLE, (1.0), (25.0)); // Цикл 1...25.0 сек
    VALVE = constrain(VALVE, (15.0), (250.0)); // Время привода 15...250.0 сек
// Расчет управляющего воздействия
    if  (PULSE_100MS & TIMER_PID == 0.0 & !  PID_PULSE)
    {
        PID_PULSE = 1; // Присвоить шаг
            D_T = K_P * (E_1 - E_2 + CYCLE * E_2 / K_I +  K_D * (E_1 - 2 * E_2 +  E_3) / CYCLE) * VALVE / 100.0; // Время воздействия на текущем шагу регулирования       
            E_3 = E_2; // Запись рассогласования -2 шага назад
            E_2 = E_1; // Запись рассогласования -1 шаг назад
            SUM_D_T = SUM_D_T + D_T; // Накопленное время воздействия
            if (SUM_D_T >= 0.5)  // Сброс накопленного времени закрытия
        {
            TIMER_PID_DOWN = 0.0;
        }
        if (SUM_D_T <= -0.5)  // Сброс накопленного времени открытия
        {
            TIMER_PID_UP = 0.0;
        }
        if (E_1 < DEAD_ZONE & E_1 > - DEAD_ZONE)  // Зона нечувствительности
        {
            D_T = 0.0;
            SUM_D_T = 0.0;
        }
    }
    if (PULSE_100MS)
    {
        TIMER_PID = TIMER_PID + 0.1; // Внутренний таймер ПИД
    }
    if  (ON_OFF &  AUTO_HAND)
    {
        if (TIMER_PID >= CYCLE)  // Сброс таймера при окончание цикла регулирования
        {
            PID_PULSE = 0; // Сбросить шаг       
                   TIMER_PID = 0.0;
            if (SUM_D_T>=0.5 || SUM_D_T<=-0.5)  // Сброа накопленного времени воздействия
            {
                SUM_D_T = 0.0;
            }
        }
    }
    else
    {
        PID_PULSE = 0;
        D_T = 0.0;
        SUM_D_T = 0.0;
        TIMER_PID = 0.0;
        E_3 = E_1;
        E_2 = E_1;
        TIMER_PID_UP = 0.0;
        TIMER_PID_DOWN = 0.0;
    }
    // Управление
    UP = ((((SUM_D_T >= TIMER_PID & SUM_D_T >= 0.5) || D_T >= CYCLE - 0.5 || TIMER_PID_UP >= VALVE) & AUTO_HAND) || (HAND_UP & ! AUTO_HAND)) & ON_OFF & ! DOWN; // Открытие клапана 
    if (PULSE_100MS &  UP & TIMER_PID_UP <  VALVE)  // Накопленное время открытия
    {
        TIMER_PID_UP = TIMER_PID_UP + 0.1;
    }
    DOWN  = ((((SUM_D_T <= - TIMER_PID & SUM_D_T <= - 0.5) || D_T <= - CYCLE + 0.5 ||  TIMER_PID_DOWN  >= VALVE) & AUTO_HAND) || (HAND_DOWN  & ! AUTO_HAND)) & ON_OFF & !  UP; // Закрытие клапана
    if (PULSE_100MS &  DOWN & TIMER_PID_DOWN <  VALVE)  // Накопленное время закрытия
    {
        TIMER_PID_DOWN = TIMER_PID_DOWN + 0.1;
    }
    _tempVariable_bool = DOWN;
    // Slave_1_0.saveBool(_tempVariable_bool, 0, 4);

#ifdef PID
    digitalWrite(PIN_LOW, !DOWN);
    // _tempVariable_bool = UP;
    // Slave_1_0.saveBool(_tempVariable_bool, 0, 3);
    digitalWrite(PIN_HIGH, !UP);

if (eeprom.heat_state)
{
    eeprom.heat_otop = true;
    /* code */
}else{eeprom.heat_otop = false;}



if (eeprom.heat_otop)
{
    if (T_bat>eeprom.temp_off_otop-eeprom.dead_zone)
   // if (T_koll< eeprom.dead_zone & T_koll> - eeprom.dead_zone)
{


    digitalWrite(nasos_otop, eeprom.heat_otop);
}else
{
eeprom.heat_otop = LOW;
digitalWrite(nasos_otop, eeprom.heat_otop);
// led5.off();
}
}




    #endif
}