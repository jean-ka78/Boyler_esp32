#include <Thermistor.h>
#include <NTC_Thermistor.h>
#include <AverageThermistor.h>

int PIN1 = 33;
int PIN2 = 32;
int PIN3 = 35;
#define SENSOR_PIN1             PIN1
#define SENSOR_PIN2             PIN2
#define SENSOR_PIN3             PIN3
#define REFERENCE_RESISTANCE   11350
#define NOMINAL_RESISTANCE     10000
#define NOMINAL_TEMPERATURE    25
#define B_VALUE                3970
#define STM32_ANALOG_RESOLUTION 4095
#define READINGS_NUMBER 10
#define DELAY_TIME 5




Thermistor* t_kollektor;
Thermistor* t_boyler;
Thermistor* t_otop;


void setup_ntc() {
  t_kollektor =  new NTC_Thermistor(
    SENSOR_PIN1,
    REFERENCE_RESISTANCE,
    NOMINAL_RESISTANCE,
    NOMINAL_TEMPERATURE,
    B_VALUE,
   
    STM32_ANALOG_RESOLUTION // <- for a thermistor calibration
  );
  t_boyler =  new NTC_Thermistor(
    SENSOR_PIN2,
    REFERENCE_RESISTANCE,
    NOMINAL_RESISTANCE,
    NOMINAL_TEMPERATURE,
    B_VALUE,
   
    STM32_ANALOG_RESOLUTION // <- for a thermistor calibration
  );
    t_otop =  new NTC_Thermistor(
    SENSOR_PIN3,
    REFERENCE_RESISTANCE,
    NOMINAL_RESISTANCE,
    NOMINAL_TEMPERATURE,
    B_VALUE,
   
    STM32_ANALOG_RESOLUTION // <- for a thermistor calibration
  );


}

void loop_ntc() {
  // Reads temperature
//   const double celsius = thermistor->readCelsius();
}