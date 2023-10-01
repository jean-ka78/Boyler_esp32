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
bool heat; //флаг включения бойлера
bool boy_state;
bool heat_otop; //Флаг включения отопления
bool heat_state; 
bool valve_mode;
int per_on; //Период включения 
int per_off; //Период виключения
int time_valve;
} eeprom;