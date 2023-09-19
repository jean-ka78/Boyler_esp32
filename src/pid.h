// #include "flprogUtilites.h"
// #include "universalModbus.h"
// #include <OneWire.h>
#include <EEPROM.h>
#include "GyverTimer.h"
GTimer isTimer(MS);  
// byte _d18x2x1Addr[8]={0x28, 0xDB, 0x66, 0x77, 0x91, 0x7, 0x2, 0xD0};
// byte _d18x2x2Addr[8]={0x28, 0xE4, 0x84, 0x77, 0x91, 0x8, 0x2, 0x58};
// FLProgSoftwareUart flprogSerial100(2, 3);
bool table_0_1_D[5];
// int table_0_1_A[5] = {0, 1, 2, 3, 4};
// bool table_0_1_S[5] = {0, 0, 0, 0, 0};
// ModbusBoolTable table_0_1_T(0, table_0_1_D, table_0_1_A, table_0_1_S, 5);
// int table_4_1_D[26];
// int table_4_1_A[26] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
// bool table_4_1_S[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// ModbusWorldTable table_4_1_T(4, table_4_1_D, table_4_1_A, table_4_1_S, 26);
// ModbusMainData SlaveData_1;
// ModbusSlaveRTU Slave_1_0;
// OneWire  _ow6(6);
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
unsigned long _d18x2x1Tti = 0UL;
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
    // pinMode(4, OUTPUT);
    // digitalWrite(4, 0);
    // pinMode(5, OUTPUT);
    // digitalWrite(5, 0);
    isTimer.setInterval(50);
    // if(((readByteFromEEPROM(0, 0, 0x0))) != 186) 
    // {
    //     (updateByteToEEPROM(0, 0, 0x0, (186)));
    //     (updateBooleanToEEPROM(1, 0, 0x0, (0)));
    //     (updateFloatToEEPROM(2, 0, 0x0, (3.0)));
    //     (updateFloatToEEPROM(6, 0, 0x0, (60.0)));
    //     (updateFloatToEEPROM(10, 0, 0x0, (1)));
    //     (updateFloatToEEPROM(14, 0, 0x0, (30.0)));
    //     (updateFloatToEEPROM(18, 0, 0x0, (0.0)));
    //     (updateFloatToEEPROM(22, 0, 0x0, (1.0)));
    //     (updateFloatToEEPROM(26, 0, 0x0, (-28.0)));
    //     (updateFloatToEEPROM(30, 0, 0x0, (80.0)));
    //     (updateFloatToEEPROM(34, 0, 0x0, (8.0)));
    //     (updateFloatToEEPROM(38, 0, 0x0, (25.0)));
    // }
    // SlaveData_1.setDataTable(&table_0_1_T);
    // SlaveData_1.setDataTable(&table_4_1_T);
    // SlaveData_1.setLongOrder(1);
    // SlaveData_1.setFloatOrder(1);
    // SlaveData_1.setUnsignedlongOrder(1);
    // SlaveData_1.setIntOrder(1);
    // Slave_1_0.setData(&SlaveData_1);
    // Slave_1_0.setUart(&flprogSerial100);
    // Slave_1_0.setPortSpeed(5);
    // Slave_1_0.begin(1);
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
          if (isTimer.isReady()) 
        {
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
    //Плата:2
//Наименование:Работа с памятью
//     if(_BitChange_1_Out) 
//     {
//         _BitChange_1_Out = 0;
//     }
//     else
//     {
//         if(!(_BitChange_1_OldSt == (Slave_1_0.readBool(0, 0))))
//         {
//             _BitChange_1_OldSt = (Slave_1_0.readBool(0, 0));
//             _BitChange_1_Out= 1;
//         }
//     }
//     if(_BitChange_1_Out)
//     {
//          if(!_SEEPR1OSN)
//         {
//             (updateBooleanToEEPROM(1, 0, 0x0, ((Slave_1_0.readBool(0, 0)))));
//             _SEEPR1OSN=1;
//         }
//     }
//     else
//     {
//          if(_SEEPR1OSN)
//         {
//             _SEEPR1OSN=0;
//         }
//     }
//     if (((_gtv1) || (_BitChange_1_Out)))
//     {
//         _tempVariable_bool = (readBooleanFromEEPROM(1, 0, 0x0));
//         Slave_1_0.saveBool(_tempVariable_bool, 0, 0);
//     }
//     if (_changeNumber1_Out) 
//     {
//         _changeNumber1_Out = 0;
//     }
//      else 
//     {
//         _tempVariable_float = (Slave_1_0.readFloat(4, 0));
//         if (_tempVariable_float != _changeNumber1_OLV) 
//         {
//             _changeNumber1_OLV = _tempVariable_float;
//             _changeNumber1_Out = 1;
//         }
//     }
//     if(_changeNumber1_Out)
//     {
//          if(!_SEEPR2OSN)
//         {
//             (updateFloatToEEPROM(2, 0, 0x0, ((Slave_1_0.readFloat(4, 0)))));
//             _SEEPR2OSN=1;
//         }
//     }
//     else
//     {
//          if(_SEEPR2OSN)
//         {
//             _SEEPR2OSN=0;
//         }
//     }
//     if (((_gtv1) || (_changeNumber1_Out)))
//     {
//         _tempVariable_float = (readFloatFromEEPROM(2, 0, 0x0));
//         Slave_1_0.saveFloat(_tempVariable_float, 4, 0);
//     }
//     if (_changeNumber2_Out) 
//     {
//         _changeNumber2_Out = 0;
//     }
//      else 
//     {
//         _tempVariable_float = (Slave_1_0.readFloat(4, 2));
//         if (_tempVariable_float != _changeNumber2_OLV) 
//         {
//             _changeNumber2_OLV = _tempVariable_float;
//             _changeNumber2_Out = 1;
//         }
//     }
//     if(_changeNumber2_Out)
//     {
//          if(!_SEEPR3OSN)
//         {
//             (updateFloatToEEPROM(6, 0, 0x0, ((Slave_1_0.readFloat(4, 2)))));
//             _SEEPR3OSN=1;
//         }
//     }
//     else
//     {
//          if(_SEEPR3OSN)
//         {
//             _SEEPR3OSN=0;
//         }
//     }
//     if (((_gtv1) || (_changeNumber2_Out)))
//     {
//         _tempVariable_float = (readFloatFromEEPROM(6, 0, 0x0));
//         Slave_1_0.saveFloat(_tempVariable_float, 4, 2);
//     }
//     if (_changeNumber3_Out) 
//     {
//         _changeNumber3_Out = 0;
//     }
//      else 
//     {
//         _tempVariable_float = (Slave_1_0.readFloat(4, 4));
//         if (_tempVariable_float != _changeNumber3_OLV) 
//         {
//             _changeNumber3_OLV = _tempVariable_float;
//             _changeNumber3_Out = 1;
//         }
//     }
//     if(_changeNumber3_Out)
//     {
//          if(!_SEEPR4OSN)
//         {
//             (updateFloatToEEPROM(10, 0, 0x0, ((Slave_1_0.readFloat(4, 4)))));
//             _SEEPR4OSN=1;
//         }
//     }
//     else
//     {
//          if(_SEEPR4OSN)
//         {
//             _SEEPR4OSN=0;
//         }
//     }
//     if (((_gtv1) || (_changeNumber3_Out)))
//     {
//         _tempVariable_float = (readFloatFromEEPROM(10, 0, 0x0));
//         Slave_1_0.saveFloat(_tempVariable_float, 4, 4);
//     }
//     if (_changeNumber4_Out) 
//     {
//         _changeNumber4_Out = 0;
//     }
//      else 
//     {
//         _tempVariable_float = (Slave_1_0.readFloat(4, 6));
//         if (_tempVariable_float != _changeNumber4_OLV) 
//         {
//             _changeNumber4_OLV = _tempVariable_float;
//             _changeNumber4_Out = 1;
//         }
//     }
//     if(_changeNumber4_Out)
//     {
//          if(!_SEEPR5OSN)
//         {
//             (updateFloatToEEPROM(14, 0, 0x0, ((Slave_1_0.readFloat(4, 6)))));
//             _SEEPR5OSN=1;
//         }
//     }
//     else
//     {
//          if(_SEEPR5OSN)
//         {
//             _SEEPR5OSN=0;
//         }
//     }
//     if (((_gtv1) || (_changeNumber4_Out)))
//     {
//         _tempVariable_float = (readFloatFromEEPROM(14, 0, 0x0));
//         Slave_1_0.saveFloat(_tempVariable_float, 4, 6);
//     }
//     if (_changeNumber5_Out) 
//     {
//         _changeNumber5_Out = 0;
//     }
//      else 
//     {
//         _tempVariable_float = (Slave_1_0.readFloat(4, 8));
//         if (_tempVariable_float != _changeNumber5_OLV) 
//         {
//             _changeNumber5_OLV = _tempVariable_float;
//             _changeNumber5_Out = 1;
//         }
//     }
//     if(_changeNumber5_Out)
//     {
//          if(!_SEEPR6OSN)
//         {
//             (updateFloatToEEPROM(18, 0, 0x0, ((Slave_1_0.readFloat(4, 8)))));
//             _SEEPR6OSN=1;
//         }
//     }
//     else
//     {
//          if(_SEEPR6OSN)
//         {
//             _SEEPR6OSN=0;
//         }
//     }
//     if (((_gtv1) || (_changeNumber5_Out)))
//     {
//         _tempVariable_float = (readFloatFromEEPROM(18, 0, 0x0));
//         Slave_1_0.saveFloat(_tempVariable_float, 4, 8);
//     }
//     if (_changeNumber6_Out) 
//     {
//         _changeNumber6_Out = 0;
//     }
//      else 
//     {
//         _tempVariable_float = (Slave_1_0.readFloat(4, 10));
//         if (_tempVariable_float != _changeNumber6_OLV) 
//         {
//             _changeNumber6_OLV = _tempVariable_float;
//             _changeNumber6_Out = 1;
//         }
//     }
//     if(_changeNumber6_Out)
//     {
//          if(!_SEEPR7OSN)
//         {
//             (updateFloatToEEPROM(22, 0, 0x0, ((Slave_1_0.readFloat(4, 10)))));
//             _SEEPR7OSN=1;
//         }
//     }
//     else
//     {
//          if(_SEEPR7OSN)
//         {
//             _SEEPR7OSN=0;
//         }
//     }
//     if (((_gtv1) || (_changeNumber6_Out)))
//     {
//         _tempVariable_float = (readFloatFromEEPROM(22, 0, 0x0));
//         Slave_1_0.saveFloat(_tempVariable_float, 4, 10);
//     }
//     if (_changeNumber7_Out) 
//     {
//         _changeNumber7_Out = 0;
//     }
//      else 
//     {
//         _tempVariable_float = (Slave_1_0.readFloat(4, 18));
//         if (_tempVariable_float != _changeNumber7_OLV) 
//         {
//             _changeNumber7_OLV = _tempVariable_float;
//             _changeNumber7_Out = 1;
//         }
//     }
//     if(_changeNumber7_Out)
//     {
//          if(!_SEEPR8OSN)
//         {
//             (updateFloatToEEPROM(26, 0, 0x0, ((Slave_1_0.readFloat(4, 18)))));
//             _SEEPR8OSN=1;
//         }
//     }
//     else
//     {
//          if(_SEEPR8OSN)
//         {
//             _SEEPR8OSN=0;
//         }
//     }
//     if (((_gtv1) || (_changeNumber7_Out)))
//     {
//         _tempVariable_float = (readFloatFromEEPROM(26, 0, 0x0));
//         Slave_1_0.saveFloat(_tempVariable_float, 4, 18);
//     }
//     if (_changeNumber8_Out) 
//     {
//         _changeNumber8_Out = 0;
//     }
//      else 
//     {
//         _tempVariable_float = (Slave_1_0.readFloat(4, 20));
//         if (_tempVariable_float != _changeNumber8_OLV) 
//         {
//             _changeNumber8_OLV = _tempVariable_float;
//             _changeNumber8_Out = 1;
//         }
//     }
//     if(_changeNumber8_Out)
//     {
//          if(!_SEEPR9OSN)
//         {
//             (updateFloatToEEPROM(30, 0, 0x0, ((Slave_1_0.readFloat(4, 20)))));
//             _SEEPR9OSN=1;
//         }
//     }
//     else
//     {
//          if(_SEEPR9OSN)
//         {
//             _SEEPR9OSN=0;
//         }
//     }
//     if (((_gtv1) || (_changeNumber8_Out)))
//     {
//         _tempVariable_float = (readFloatFromEEPROM(30, 0, 0x0));
//         Slave_1_0.saveFloat(_tempVariable_float, 4, 20);
//     }
//     if (_changeNumber9_Out) 
//     {
//         _changeNumber9_Out = 0;
//     }
//      else 
//     {
//         _tempVariable_float = (Slave_1_0.readFloat(4, 22));
//         if (_tempVariable_float != _changeNumber9_OLV) 
//         {
//             _changeNumber9_OLV = _tempVariable_float;
//             _changeNumber9_Out = 1;
//         }
//     }
//     if(_changeNumber9_Out)
//     {
//          if(!_SEEPR10OSN)
//         {
//             (updateFloatToEEPROM(34, 0, 0x0, ((Slave_1_0.readFloat(4, 22)))));
//             _SEEPR10OSN=1;
//         }
//     }
//     else
//     {
//          if(_SEEPR10OSN)
//         {
//             _SEEPR10OSN=0;
//         }
//     }
//     if (((_gtv1) || (_changeNumber9_Out)))
//     {
//         _tempVariable_float = (readFloatFromEEPROM(34, 0, 0x0));
//         Slave_1_0.saveFloat(_tempVariable_float, 4, 22);
//     }
//     if (_changeNumber10_Out) 
//     {
//         _changeNumber10_Out = 0;
//     }
//      else 
//     {
//         _tempVariable_float = (Slave_1_0.readFloat(4, 24));
//         if (_tempVariable_float != _changeNumber10_OLV) 
//         {
//             _changeNumber10_OLV = _tempVariable_float;
//             _changeNumber10_Out = 1;
//         }
//     }
//     if(_changeNumber10_Out)
//     {
//          if(!_SEEPR11OSN)
//         {
//             (updateFloatToEEPROM(38, 0, 0x0, ((Slave_1_0.readFloat(4, 24)))));
//             _SEEPR11OSN=1;
//         }
//     }
//     else
//     {
//          if(_SEEPR11OSN)
//         {
//             _SEEPR11OSN=0;
//         }
//     }
//     if (((_gtv1) || (_changeNumber10_Out)))
//     {
//         _tempVariable_float = (readFloatFromEEPROM(38, 0, 0x0));
//         Slave_1_0.saveFloat(_tempVariable_float, 4, 24);
//     }
//     //Плата:3
// //Наименование:Опрос датчиков
//     if(flprog::isTimer(_d18x2x1Tti, 1000)) 
//     {
//         _d18x2x1Tti = millis();
//         _tempVariable_float =  _readDS18_ow6(_d18x2x1Addr, 0);
//         if (_tempVariable_float < 500) 
//         {
//             _d18x2x1O = _tempVariable_float;
//         }
//     }
//     _tempVariable_float = (_d18x2x1O);
//     Slave_1_0.saveFloat(_tempVariable_float, 4, 12);
//     if(flprog::isTimer(_d18x2x2Tti, 10000)) 
//     {
//         _d18x2x2Tti = millis();
//         _tempVariable_float =  _readDS18_ow6(_d18x2x2Addr, 0);
//         if (_tempVariable_float < 500) 
//         {
//             _d18x2x2O = _tempVariable_float;
//         }
//     }
//     _tempVariable_float = (_d18x2x2O);
//     Slave_1_0.saveFloat(_tempVariable_float, 4, 16);
    //Плата:4
//Наименование:Отопительный график
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
    // _tempVariable_bool = DOWN;
    // Slave_1_0.saveBool(_tempVariable_bool, 0, 4);

    #ifdef PID
    digitalWrite(PIN_LOW, DOWN);
    // _tempVariable_bool = UP;
    // Slave_1_0.saveBool(_tempVariable_bool, 0, 3);
    digitalWrite(PIN_HIGH, UP);
if (eeprom.heat_state)
{
    eeprom.heat_otop = true;
    /* code */
}else{eeprom.heat_otop = false;}



if (eeprom.heat_otop)
{
    if (T_koll>=eeprom.temp_off_otop)
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
// float _convertDS18x2xData(byte type_s, byte data[12])
// {
//     int16_t raw = (data[1] << 8) | data[0];
//     if (type_s)
//     {
//         raw = raw << 3;
//         if (data[7] == 0x10) 
//         {
//              raw = (raw & 0xFFF0) + 12 - data[6];
//         }
//     }
//     else
//     {
//         byte cfg = (data[4] & 0x60);
//         if (cfg == 0x00)raw = raw & ~7;
//         else if(cfg == 0x20)raw = raw & ~3;
//         else if(cfg == 0x40) raw = raw & ~1;
//     }
//     return  (float)raw / 16.0;
// }
// float _readDS18_ow6(byte addr[8], byte type_s)
// {
//     byte data[12];
//     byte i;
//     _ow6.reset();
//     _ow6.select(addr);
//     _ow6.write(0xBE);
//     for (i = 0; i < 9; i++) 
//     {
//          data[i] = _ow6.read();
//     }
//     _ow6.reset();
//     _ow6.select(addr);
//     _ow6.write(0x44);
//     if (_ow6.crc8(data, 8) != data[8])
//     {
//         return 501;
//     }
//     return _convertDS18x2xData(type_s, data);
// }
//  byte readByteFromEEPROM(int addres, byte bitAddres, byte chipAddres)
// {
//     return EEPROM.read(addres);
// }
// void updateByteToEEPROM(int addres, byte bitAddres, byte chipAddres, byte value)
// {
//     return EEPROM.update(addres, value);
// }
// bool readBooleanFromEEPROM(int addres, byte bitAddres, byte chipAddres)
// {
//     byte temp = readByteFromEEPROM(addres,  bitAddres,  chipAddres);
//     return  bitRead(temp, bitAddres);
// }
// void updateBooleanToEEPROM(int addres, byte bitAddres, byte chipAddres, bool value)
// {
//     byte temp = readByteFromEEPROM(addres,  bitAddres,  chipAddres);
//     bitWrite(temp, bitAddres, value);
//     updateByteToEEPROM(addres,  bitAddres,  chipAddres, temp);
// }
// float readFloatFromEEPROM(int addres, byte bitAddres, byte chipAddres)
// {
//     byte x[4];
//     for(byte i = 0; i < 4; i++) 
//     {
//          x[i] = readByteFromEEPROM((addres+i),  bitAddres,  chipAddres);
//     }
//     float *y = (float *)&x;
//     return y[0];
// }
// void updateFloatToEEPROM(int addres, byte bitAddres, byte chipAddres, float value)
// {
//     byte *x = (byte *)&value;
//     for(byte i = 0; i < 4; i++) 
//     {
//         updateByteToEEPROM((addres+i),  bitAddres,  chipAddres, x[i]);
//     }
// }