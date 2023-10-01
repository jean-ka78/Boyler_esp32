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
uint32_t per_on; //Период включения 
uint32_t per_off; //Период виключения
uint32_t time_valve;
uint32_t INIT_ADDR;
uint32_t INIT_KEY;


} eeprom;