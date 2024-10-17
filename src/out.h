int PIN_LOW = 22;
int PIN_HIGH = 23;
const int nasos_Boy = 21;
const int nasos_otop = 19;
class ControlSystem {
  private:
    const int pinLow;
    const int pinHigh;
    const int nasosBoy;
    const int nasosOtop;
    bool nasosOtopOn;  // Стан насосу опалення
    bool nasosBoyOn;   // Стан насосу бойлера
    bool nasosOn;
    bool boyOn;

  public:
    // Конструктор класу
    ControlSystem(int pinLow, int pinHigh, int nasosBoy, int nasosOtop) 
      : pinLow(pinLow), pinHigh(pinHigh), nasosBoy(nasosBoy), nasosOtop(nasosOtop), nasosOn(false), boyOn(false) {
        // Ініціалізація пінів під час створення об'єкта
        pinMode(pinLow, OUTPUT);
        pinMode(pinHigh, OUTPUT);
        pinMode(nasosBoy, OUTPUT);
        pinMode(nasosOtop, OUTPUT);

        // Зчитуємо початковий стан сигналів
        // checkAndTurnNasosOn();
        // checkAndTurnNasosBoyOn();
    }

    // Метод для встановлення сигналу на насос опалення
    void nasosOtop_start(bool _nasosOtopOn){
        nasosOtopOn = _nasosOtopOn;
    }

    // Метод для встановлення сигналу на насос бойлера
    void nasosBoy_start(bool _nasosBoyOn){
        nasosBoyOn = _nasosBoyOn;
    }

    // Перевірка стану насосів і керування ними
    void updateSystem() {
        // Якщо насос бойлера має сигнал для увімкнення
        if (nasosBoyOn) {
            turnNasosBoyOn();  // Увімкнути насос бойлера
            
            turnNasosOff();    // Вимкнути насос опалення
        } else {
            turnNasosBoyOff(); // Вимкнути насос бойлера
            // Якщо немає сигналу для увімкнення бойлера, перевіряємо насос опалення
            if (nasosOtopOn) {
                turnNasosOn(); // Увімкнути насос опалення
            } else {
                turnNasosOff(); // Вимкнути насос опалення
            }
        }
    }

    // Увімкнути насос опалення (Otop)
    void turnNasosOn() {
        digitalWrite(nasosOtop, HIGH);
        nasosOn = true;
        eeprom.nasos_on = true;
    }

    // Вимкнути насос опалення (Otop)
    void turnNasosOff() {
        digitalWrite(nasosOtop, LOW);
        nasosOn = false;
        eeprom.nasos_on = false;
    }

    // Увімкнути насос бойлера (Boy)
    void turnNasosBoyOn() {
        digitalWrite(nasosBoy, HIGH);
        boyOn = true;
        
    }

    // Вимкнути насос бойлера (Boy)
    void turnNasosBoyOff() {
        digitalWrite(nasosBoy, LOW);
        boyOn = false;
    }

    // Підняти клапан
    void valveUp() {
        digitalWrite(pinHigh, LOW);
        digitalWrite(pinLow, HIGH);
    }

    // Зупинити підйом клапана
    void valveUpStop() {
        digitalWrite(pinHigh, HIGH);
    }

    // Опустити клапан
    void valveDown() {
        digitalWrite(pinLow, LOW);
        digitalWrite(pinHigh, HIGH);
    }

    // Зупинити опускання клапана
    void valveDownStop() {
        digitalWrite(pinLow, HIGH);
    }

    // Перевірити стан насосу опалення (Otop)
    bool isNasosOn() const {
        return nasosOn;
    }

    // Перевірити стан насосу бойлера (Boy)
    bool isNasosBoyOn() const {
        return boyOn;
    }
};

// Приклад використання
ControlSystem control(PIN_LOW, PIN_HIGH, nasos_Boy, nasos_otop);  // пін-коди передаються через конструктор

void setup_out() {
    // Налаштування пінів виконується в конструкторі, тому setup() пустий
}

void loop_out() {
    // Оновлюємо стан насосів, перевіряючи сигнали
    control.updateSystem();
}
