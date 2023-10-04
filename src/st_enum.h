struct st_Enum
{
float  temp_u;     //Уставка бойлера
float  temp_u_b;   //Уставка баттарей
float temp_off_otop; //уставка отключения отопления
float gis_boy;  //gisterezis boyler
float temp_min_out;
float temp_max_out;
float temp_max_heat;
float dead_zone;
float kof_p;
float kof_i;
float kof_d;
bool init;
bool heat; //флаг включения бойлера
bool boy_state;
bool heat_otop; //Флаг включения отопления
bool heat_state; 
bool valve_mode;
int per_on; //Период включения 
int per_off; //Период виключения
int time_valve;
} eeprom;

#define INIT_ADDR 1  // номер резервной ячейки
#define INIT_KEY 1     // ключ первого запуска. 0-254, на выбор
void first_start()
{
    EEPROM.begin(sizeof(st_Enum));
    EEPROM.get(0, eeprom);
    // Serial.println("first start read adress: "+String(eeprom.init));
    if (eeprom.init != INIT_KEY) { // первый запуск
    eeprom.init = INIT_KEY;    // записали ключ

  // EEPROM.get(0, eeprom);
// --------------------------------------
// Заводские настройки 
  eeprom.temp_u = 50;
  eeprom.temp_u_b = 50;
  eeprom.temp_off_otop = 30;
  eeprom.gis_boy = -1.5;
  eeprom.heat = true;
  eeprom.boy_state = true;
  eeprom.heat_otop = true;
  eeprom.heat_state = true;
  eeprom.valve_mode = true;
  eeprom.per_on = 10;
  eeprom.per_off = 120;
  eeprom.kof_p = 0.5;
  eeprom.kof_i = 30;
  eeprom.kof_d = 1;
  eeprom.temp_max_out = 18;
  eeprom.temp_min_out = -8;
  eeprom.temp_max_heat = 80;
  eeprom.dead_zone = 1;


  EEPROM.begin(sizeof(st_Enum));
  EEPROM.put(0, eeprom);
  delay(50);
  EEPROM.commit();


}
}

void Safe_eeprom()
{

      EEPROM.begin(sizeof(st_Enum));
      EEPROM.put(0, eeprom);
      delay(50);
      EEPROM.commit();

}