
//╞══════════════════════════════╣ НАСТРОЙКИ ⚒ ╠══════════════════════════════════╡

#define NUM_SHOTS     5     // количество рюмок (оно же кол-во светодиодов и кнопок!)
#define TIMEOUT_OFF   5     // таймаут на выключение (перестаёт дёргать привод), минут
#define SWITCH_LEVEL  0     // кнопки 1 - высокий сигнал при замыкании, 0 - низкий
#define PARKING_POS   0     // положение парковочной позиции в градусах
#define TIME_50ML     5000  // время заполнения 50 мл
#define STBY_LIGHT    20    // яркость подсветки в режиме ожидания. 255 -> максимум, 0 -> выкл
#define RAINBOW_FLOW  1     // 1 -> динамическая подсветка налитых рюмок, 0 -> статическая
#define STATUS_LED    0     // яркость статус-светодиода. 255 -> максимум, 0 -> не подключен.

#define STEPS_PER_REVOLUTION     2037.88642  // количество шагов на оборот двигателя
#define MICROSTEPS               2           // значение микрошага, выставленного на драйвере двигателя
#define INVERT_STEPPER           0           // инвертировать направление вращения шагового двигателя
#define STEPPER_ENDSTOP_INVERT   0           // 1 - высокий сигнал при замыкании, 0 - низкий
#define STEPPER_POWERSAFE        1           // энергосберегающий режим шагового двигателя. 1 -> вкл ,0 -> выкл
#define STEPER_BACKLASH          3           // компенсация люфта двигателя в градусах. 0 выключает эту функцию
#define STEPPER_SPEED            15          // скорость двигателя в об/мин
#define STEPPER_HOMING_SPEED     5           // скорость вращения двигателя при движении к концевику (если он есть) в об/мин

#define DEBUG_UART 0                         // отладка

//╞═════════════════════╡Положения серво над центрами рюмок╞══════════════════════╡

// номер рюмки                1   2   3   4    5    6
//                            ^   ^   ^   ^    ^    ^
#define SHOT_POSITIONS       30, 60, 90, 120, 150, 180

//╞═════════════════════════════╡ПИНЫ Arduino Nano╞═══════════════════════════════╡

#if defined(ARDUINO_AVR_NANO)
#define PUMP_POWER      3   // управляющий сигнал драйвера помпы (обычно обозначен как IN на драйверах моторов, либо GATE/BASE, если используется транзистор)
#define STEPPER_STEP    5   // сигнал STEP драйвера
#define STEPPER_DIR     4   // сигнал DIR драйвера
#define STEPPER_EN      2   // сигнал EN драйвера
#define STEPPER_ENDSTOP A7  // сигнал с концевика для двигателя. Закоментировать, если концевик не используется
#define LED_PIN         6   // сигнал DIO/DI первого светодиода (для первой рюмки)
#define BTN_PIN         7   // сигнал с основной кнопки для разлива и смены режимов
#define ENC_SW          8   // сигнал центральной кнопки на энкодере для прокачки и настройки различных обьёмов. Обозначен как SW или BTN
#define ENC_DT          9   // сигнал DT или А с энкодера
#define ENC_CLK         10  // сигнал CLK или B с энкодера
#define DISP_DIO        11  // сигнал DIO на дисплее TM1637
#define DISP_CLK        12  // сигнал CLK на дисплее TM1637
#define SW_PINS         A0, A1, A2, A3, A4, A5  // сигналы с датчиков наличия рюмок: от первой к последней рюмке

//╞══════════════════════════════╡ПИНЫ Arduino Micro╞═════════════════════════════╡

#elif defined(ARDUINO_AVR_MICRO)
#define PUMP_POWER      0   // управляющий сигнал драйвера помпы (обычно обозначен как IN на драйверах моторов, либо GATE/BASE, если используется транзистор)
#define VALVE_PIN       1   // не используется
#define DISP_DIO        2   // сигнал DIO на дисплее TM1637
#define DISP_CLK        3   // сигнал CLK на дисплее TM1637
#define BTN_PIN         4   // сигнал с основной кнопки для разлива и смены режимов
#define LED_PIN         5   // сигнал DIO/DI первого светодиода (для первой рюмки)
#define STEPPER_STEP    6   // сигнал STEP драйвера
#define STEPPER_DIR     7   // сигнал DIR драйвера
#define STEPPER_EN      8   // сигнал EN драйвера
#define STEPPER_ENDSTOP 9   // сигнал с концевика для двигателя. Закоментировать, если концевик не используется
#define ENC_SW          10  // сигнал центральной кнопки на энкодере для прокачки и настройки различных обьёмов. Обозначен как SW или BTN
#define ENC_DT          14  // сигнал DT или А с энкодера
#define ENC_CLK         16  // сигнал CLK или B с энкодера
#define SW_PINS         14, 15, 18, 19, 20  // сигналы с датчиков наличия рюмок: от первой к последней рюмке
#endif
