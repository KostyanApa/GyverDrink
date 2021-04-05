
//╞════════════════════════════════════════════════════════════════════════════════════╣ Настройки ⚒ ╠════════════════════════════════════════════════════════════════════════════════════╡

/*■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ Основные настройки ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/

/*  ======================== выбор дисплея ========================
   0  → OLED 128x64 на контроллере SSD1306 или SSD1309 по (I2C)
   1  → OLED 128x64 на контроллере SH1106 (I2C)
   2  → OLED 128x64 на контроллере SSD1306 или SSD1309 (SPI)
   3  → 4-х значный 7-ми сегментный дисплей на контроллере TM1637
   4  → стрелочный индикатор
*/
#define DISPLAY_TYPE   0

#define NUM_SHOTS      5     // количество рюмок (оно же кол-во светодиодов и кнопок!)
#define SWITCH_LEVEL   0     // кнопки: 1 → высокий сигнал при замыкании, 0 → низкий
#define ENCODER_TYPE   1     // тип энкодера. 0 или 1. Отличаются количеством делений на оборот
#define ENCODER_DIR    1     // направление вращения энкодера. 0 или 1
//#define STATUS_LED     30    // яркость статус-светодиода. 255 → максимум. Раскомментировать, если подключен
//#define BATTERY_PIN    A7    // + аккумулятора (максимум 5 вольт без делителя). Раскомментировать, если подключен
//#define CHARGER_PIN    A6    // IN+ с TP4056. Используется для детектирования зарядки

#define MOTOR_TYPE     0     // тип привода. Серво - 0, Шаговик - 1

// ======================== Настройка шагового мотора ========================

#define STEPS_PER_REVOLUTION     2038  // количество шагов на оборот двигателя
#define MICROSTEPS               2     // значение микрошага, выставленного на драйвере двигателя
#define STEPPER_ACCELERATION     500   // ускорение двигателя в угол/сек^2
#define STEPPER_HOMING_SPEED     20    // скорость вращения двигателя при движении к концевику (если он есть) в об/мин
//#define SMOOTH_ALGORITHM               // ещё больше плавности движения!

// ========================= Настройка Серводвигателя =========================

#define SERVO_MIN_US  544     // минимальная ширина импульса в мкс
#define SERVO_MAX_US  2400    // максимальная ширина импульса в мкс

/*■■■■■■■■■■■■■■■■■■■■■ Параметры, изменяемые в сервис режиме ■■■■■■■■■■■■■■■■■■■■■■*/

#define TIME_50ML      5000  // время заполнения 50 мл
#define MAX_VOLUME     50    // ограничение максимального объёма. Максимальное значение 255
#define MOTOR_REVERSE  0     // инвертировать направление вращения двигателя
#define PARKING_POS    0     // угол двигателя для парковочной позиции
#define BATTERY_CAL    1.0   // фактор для калибровки напряжения акб

// позиции серводвигателя над рюмками. От первой к последней
#define SHOT_POSITIONS       30, 60, 90, 120, 150, 180

/*■■■■■■■■■■■■■■■■■■■■■■■■■■ Дополнительные настройки ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/

// Онлайн конвертер цветов https://bit.ly/34WSaig Используем значение H из HSV.

#define LEDS_COLOR     270            // цвет подсветки светодиодов от 0 до 360
#define TIMEOUT_STBY   10             // таймаут входа в режим ожидания в секундах. В режиме ожидания сохраняется последний объём и приглушается яркость подсветки
#define TIMEOUT_OFF    5              // таймаут входа в енергосберегающий режим в минутах. В этом режиме отключается дисплей и все светодиоды. Если 0 → режим не активен
#define KEEP_POWER     0              // интервал поддержания питания от повербанка в секундах. Через этот интервал происходит скачёк потребления енергии светодиодами. 0 → функция отключена
#define MOTOR_SPEED    40             // скорость привода. Для серво максимум 100. Для шаговика значение в градус/сек
#define AUTO_PARKING   1              // парковка в авто режиме: 1 → вкл, 0 → выкл
#define MOTOR_AUTO_POWER 1            // авто отключение двигателя во время простоя
#define SAVE_MODE      0              // 1 → сохранение последнего активного режима в памяти, 0 → не сохраняется
#define STBY_LIGHT     20             // яркость подсветки в режиме ожидания. 255 → максимум, 0 → выкл
#define RAINBOW_FLOW   1              // 1 → динамическая подсветка налитых рюмок, 0 → статическая
#define MANUAL_MODE_STATUS_COLOR 200  // цвет статусного светодиода в ручном режиме
#define AUTO_MODE_STATUS_COLOR 100    // цвет статусного светодиода в авто режиме
#define DISPLAY_SESSION_VOLUME  1     // вывод общего объёма за сеанс на основную страницу. 1 → вкл, 0 → выкл

/*■■■■■■■■■■■■■■■■■■■■■■■■■■■ Настройки OLED дисплея ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/

#define INVERT_DISPLAY 0     // инверсия цветов OLED дисплея
#define OLED_CONTRAST  15    // яркость дисплея. Макс 255
#define MENU_SELECT    0     // 0 → выбор пункта меню инверсией, 1 → стрелкой
#define MENU_LANG      0     // язык меню. 0 → русский, 1 → english
#define NUM_FONT       0     // выбор шрифта для отображения объёма (0 или 1)
#define WIRE_SPEED     888   // частота передачи данных OLED дисплею в kHz (min 100, mid 400, max 900). Понизьте частоту, при проблемах с дисплеем.
#define BOOTSCREEN     "Der Наливатор"  // текст на OLED дисплее при старте устройства


//╞════════════════════════════════════════════════════════════════════════════════════╣ Соединения ╠════════════════════════════════════════════════════════════════════════════════════╡

#define PUMP_POWER  3        // управляющий сигнал драйвера помпы (обычно обозначен как IN на драйверах моторов, либо GATE/BASE, если используется транзистор)
#define SERVO_POWER 4        // управляющий сигнал драйвера для питания серводвигателя (обычно обозначен как IN на драйверах моторов, либо GATE/BASE, если используется транзистор)
#define SERVO_PIN   5        // сигнальный провод серводвигателя
#define LED_PIN     6        // сигнал DIO/DI первого светодиода (WS2812b)
#define BTN_PIN     7        // сигнал с основной кнопки для разлива и смены режимов
#define ENC_SW      8        // сигнал центральной кнопки на энкодере для прокачки и настройки различных обьёмов. Обозначен как SW или BTN
#define ENC_DT      9        // сигнал DT или А с энкодера
#define ENC_CLK     10       // сигнал CLK или B с энкодера

//#define STEPPER_ENDSTOP 1    // сигнал с концевика для двигателя. В активном состоянии должен замыкать на GND. Закоментировать, если концевик не используется
#define STEPPER_EN      2    // сигнал EN драйвера
#define STEPPER_DIR     4    // сигнал DIR драйвера
#define STEPPER_STEP    5    // сигнал STEP драйвера

/*■■■■■■■■■■■■■■■■■■■■■■■■■■■ Версия с дисплеем TM1639 ■■■■■■■■■■■■■■■■■■■■■■■■■■■*/
#if(DISPLAY_TYPE == 3)

#define DISP_DIO    11       // сигнал DIO на дисплее TM1637
#define DISP_CLK    12       // сигнал CLK на дисплее TM1637
#define SW_PINS     A0, A1, A2, A3, A4, A5    // сигналы с датчиков наличия рюмок на ТМ1637 версии: от первой к последней рюмке

/*■■■■■■■■■■■■■■■■■■■■■■■■■■■■ Версия с OLED дисплеем ■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/
#elif (DISPLAY_TYPE < 3)

// пины I2C
#define DISP_SDA    A4       // сигнал SDA OLED дисплея
#define DISP_SCK    A5       // сигнал SCK OLED дисплея
// пины SPI
#define DISP_DC     0        // сигнал DC OLED дисплея
#define DISP_MOSI   A4       // сигнал MOSI или SDA OLED дисплея
#define DISP_CLK    A5       // сигнал CLK или SCL OLED дисплея

#define SW_PINS     A0, A1, A2, A3, 11, 12  // сигналы с датчиков наличия рюмок на OLED версии: от первой к последней рюмке

/*■■■■■■■■■■■■■■■■■■■■■■■ Версия со стрелочным индикатором ■■■■■■■■■■■■■■■■■■■■■■■*/
#elif (DISPLAY_TYPE == 4)

#define ANALOG_METER_PIN 11  // + с индикатора
#define SW_PINS     A0, A1, A2, A3, A4, A5    // сигналы с датчиков наличия рюмок на ANALOG_METER версии: от первой к последней рюмке
#endif
