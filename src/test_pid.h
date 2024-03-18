class PIDController {
private:
    double kp, ki, kd;
    double setpoint;
    double lastInput;
    double output;
    double integral;
    double derivative;
    double hysteresis;

public:
    PIDController(double _kp, double _ki, double _kd, double _setpoint, double _hysteresis) :
        kp(_kp),
        ki(_ki),
        kd(_kd),
        setpoint(_setpoint),
        lastInput(0),
        output(0),
        integral(0),
        derivative(0),
        hysteresis(_hysteresis) {}

    double compute(double input) {
        double error = setpoint - input;
        integral += (ki * error);
        derivative = kd * (input - lastInput);

        output = kp * error + integral + derivative;

        // Anti-windup
        if (output > 255) {
            output = 255;
            integral -= ki * error;
        } else if (output < 0) {
            output = 0;
            integral -= ki * error;
        }

        // Гістерезіс
        double upperThreshold = setpoint + hysteresis;
        double lowerThreshold = setpoint - hysteresis;

        if (output > 0 && input > upperThreshold) {
            output = 0;  // Вимкнути обігрівач, якщо температура перевищує верхню межу
        } else if (output < 255 && input < lowerThreshold) {
            output = 255; // Вимкнути охолоджувач, якщо температура падає нижче нижньої межі
        }

        lastInput = input;
        return output;
    }

    void setSetpoint(double _setpoint) {
        setpoint = _setpoint;
    }

    void setHysteresis(double _hysteresis){
        hysteresis = _hysteresis;
    }

    void reset() {
        integral = 0;
        derivative = 0;
        lastInput = 0;
    }
};

// const int temperaturePin = A0; // Пін для зчитування температури
// const int heaterPin = 3;      // Пін для керування обігрівачем
// const int coolerPin = 5;      // Пін для керування охолоджувачем

double set_temp_graf(){
    double SET;
    double OUT = T_out;
    double X1 = eeprom.temp_min_out;
    double Y1 = eeprom.temp_max_heat;
    double X2 = eeprom.temp_max_out;
    double Y2 = eeprom.temp_off_otop;
    // График отопления
    if (OUT <= X1)  // Верхняя срезка
    {
        SET = Y1;
    }
    if (OUT > X1 & OUT < X2)  // График между верхней и нижней срезкой
    {
        if (X1 == X2)  // Деление на 0
        {
            X1 = X1 + 0.1;
        }
        SET = (OUT - X1) * (Y1 - Y2) / (X1 - X2) + Y1;
    }
    if (OUT >= X2)  // Нижняя срезка
    {
        SET = Y2;
    }
    // _tempVariable_float = T_SET;
    return SET;
}



const double Kp = eeprom.kof_p;        // Коефіцієнт пропорційності
const double Ki = eeprom.kof_i;        // Коефіцієнт інтегралу
const double Kd = eeprom.kof_d;        // Коефіцієнт диференціалу
double setpoint;                 // Бажане значення температури
const double hysteresis = eeprom.dead_zone;// Гістерезіс

PIDController pid(Kp, Ki, Kd, setpoint, hysteresis);

void adjustHeaterCooler(double output) {
    if (output > 0) {
        digitalWrite(PIN_HIGH, LOW);
        digitalWrite(PIN_LOW, HIGH);
    } else {
        digitalWrite(PIN_HIGH, HIGH);
        digitalWrite(PIN_LOW, LOW);
    }
}

double readTemperature() {

    double present = T_bat;
    return present;
    // Зчитування температури з датчика
}


// void setup_test_pid() {
//     pinMode(heaterPin, OUTPUT);
//     pinMode(coolerPin, OUTPUT);
// }

void loop_test_pid() {
    setpoint = set_temp_graf();
    pid.setSetpoint(setpoint);
    pid.setHysteresis(eeprom.dead_zone);
    double temperature = readTemperature();
    double output = pid.compute(temperature);
  
    adjustHeaterCooler(output);
    if (eeprom.heat_state)
        {
        eeprom.heat_otop = true;
        /* code */
            }
        else{
            eeprom.heat_otop = false;}


    if (T_SET==eeprom.temp_off_otop){
    eeprom.heat_otop = LOW;
    }
    if (eeprom.heat_otop)
    {
        turnNasosOn();
    }
    else
    {
      turnNasosOff();  
    }
}


