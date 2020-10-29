void serviceRoutine(serviceStates mode);

#ifdef TM1637
GyverTM1637 disp(DISP_CLK, DISP_DIO);
enum { ml = 1, deg };
void printNum(uint16_t num, int8_t mode = 0);

//==================================================================================================

#elif defined ANALOG_METER
byte err_vector[256] = {
  0,  1,  1,  2,  2,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,  5,
  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  8,  8,  8,  9,
  9,  9,  10, 10, 10, 11, 11, 12, 12, 12, 13, 13, 14, 14, 14, 14,
  14, 15, 15, 15, 15, 16, 16, 16, 17, 17, 18, 18, 18, 19, 19, 19,
  20, 20, 21, 21, 21, 22, 22, 23, 23, 24, 24, 25, 26, 26, 26, 27,
  27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 31, 31, 31, 32, 32, 32,
  33, 33, 34, 34, 34, 35, 35, 35, 36, 36, 36, 37, 37, 38, 38, 38,
  39, 39, 40, 40, 40, 40, 40, 41, 41, 41, 41, 42, 42, 43, 43, 44,
  44, 44, 44, 44, 45, 45, 45, 45, 45, 46, 46, 46, 46, 46, 47, 47,
  47, 47, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 49,
  49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
  49, 49, 49, 48, 48, 48, 48, 48, 48, 48, 48, 47, 47, 47, 47, 46,
  46, 46, 45, 45, 44, 44, 44, 43, 43, 43, 43, 42, 42, 42, 41, 41,
  40, 40, 39, 39, 38, 38, 37, 37, 36, 36, 35, 34, 33, 33, 32, 31,
  31, 30, 29, 28, 28, 27, 26, 25, 24, 23, 22, 22, 21, 20, 19, 19,
  18, 17, 16, 15, 14, 13, 12, 11, 10, 9,  7,  5,  4,  3,  1,  0,
};

void printNum(uint16_t num, int8_t mode = 0) {
  static byte lastVal = 255;
  byte value = round(num * 255.0 / parameterList[max_volume]);
  Serial.println(num);

  if ( (value == 0) && (lastVal > 0) ) {
    for (byte i = lastVal; i > 0; i--) {
      analogWrite(ANALOG_METER_PIN, i - err_vector[i]);
      delay(2);
    }
    lastVal = value;
  }

  if ( (lastVal == 0) && (value > 0)) {
    for (byte i = 0; i < value; i++) {
      analogWrite(ANALOG_METER_PIN, i - err_vector[i]);
      delay(3);
    }
    lastVal = value;
  }
  if ( (lastVal == 255) && (num == thisVolume) ) {
    for (byte i = lastVal; i > value; i--) {
      analogWrite(ANALOG_METER_PIN, i - err_vector[i]);
      delay(3);
    }
    lastVal = value;
  }

  if (value > lastVal)
    for (byte i = lastVal; i < value; i++) analogWrite(ANALOG_METER_PIN, i - err_vector[i]);
  else if (value < lastVal)
    for (byte i = lastVal; i > value; i--) analogWrite(ANALOG_METER_PIN, i - err_vector[i]);

  lastVal = value;
}

/* для совместимости */
struct disp {
  void clear() {}
} disp;
enum { ml = 1, deg };


//==================================================================================================

#elif defined OLED

#if (OLED == 3)
SSD1306AsciiSoftSpi disp;
#else
SSD1306AsciiWire disp;
#endif

#if (NUM_FONT == 0)
#define BIG_NUM_FONT FixedNum30x40
#elif (NUM_FONT == 1)
#define BIG_NUM_FONT FixedNum30x40_2
#endif

#if (MENU_LANG == 1)
#define MAIN_FONT Vicler8x16
#else
#define MAIN_FONT ZevvPeep8x16
#endif

enum MenuPageName { // типы страниц меню
  NO_MENU = -1,
  MAIN_MENU_PAGE,
  SETTINGS_PAGE,
  STATISTICS_PAGE,
  SERVICE_PAGE,
  SERVO_CALIBRATION_PAGE
};

MenuPageName menuPage = MAIN_MENU_PAGE; // актуальная страница
byte lastMenuPage = NO_MENU; // последняя отображаемая страница
bool itemSelected = 0;

uint8_t menuItemsNum[] = {3, 8, 2, 4, 4}; // количество строк на каждой странице без заголовка

#if(MENU_LANG == 1)
const char *MenuPages[][9] = {
  { "#####  Меню  #####",
    "",
    " Настройки",
    " Статистика",
  },

  { "###  Настройки  ###",
    "таймаут выкл.",
    "режим ожидания",
    "яркость лед",
    "цвет лед",
    "динам. подсветка",
    "инверсия дисп.",
    "яркость дисп.",
    "макс. объeм"
  },

  { "### Статистика  ###",
    " Кол-во рюмок",
    " Объ@м",
    ""
  },

  { "##### Сервис #####",
    " Серво",
    " Объ@м",
#ifdef BATTERY_PIN
    " Аккумулятор",
#else
    " Поддерж. питания",
#endif
    " Сброс"
  },

  {
    "#####  Серво  #####",
    " Калибровка",
    " Инверсия",
    " Скорость",
    " Авто парковка"
  }
};

#else
const char *MenuPages[][9] = {
  { "Menu",
    "",
    " Settings",
    " Statistics"
  },

  { "Settings",
    "timeout off",
    "stby time",
    "stby light",
    "led color",
    "rainbow flow",
    "invert display",
    "disp contrast",
    "max volume",
  },

  { "Statistics",
    " Shots",
    " Volume",
    ""
  },

  { "Service",
    " Servo",
    " Volume",
#ifdef BATTERY_PIN
    " Battery",
#else
    " Keep power",
#endif
    " Reset"
  },

  {
    " Servo ",
    " Calibration",
    " Inverse",
    " Speed",
    " Auto parking"
  }
};
#endif

byte strWidth(const char str[]) {
  byte _width = 0;
  while (*str) {
#if(MENU_LANG == 1)
    _width += disp.charWidth(*str++);
#else
    _width += disp.charSpacing(*str++);
#endif
  }
  return _width;
}

enum text_position {
  Append = -4,
  Left,
  Center,
  Right
};

void clearToEOL(const char ch = ' ') {
  byte i = 1 + (disp.displayWidth() - disp.col()) / disp.charWidth(ch);
  while (i--) disp.write(ch);
}

void printStr(const char str[], int8_t x = Append, int8_t y = Append) {
  if (x == Left)    disp.setCol(0);
  if (x == Center)  disp.setCol( (disp.displayWidth() - strWidth(str)) / 2);
  if (x == Right)   disp.setCol(disp.displayWidth() - strWidth(str));
  if (x != Append)  disp.setCol(x);

  if (y != Append)  disp.setRow(y);

  while (*str) disp.write(*str++);
}

void printInt(uint16_t num, int8_t x = Append, int8_t y = Append) {
  char cstr[5];
  itoa(num, cstr, 10);
  printStr(cstr, x, y);
}

void ftoa(float floatVal, char* floatStr, byte dec) { // float to char array
  byte index = 0;

  float rounding = 0.5;
  for (uint8_t i = 0; i < dec; ++i) rounding /= 10.0;
  floatVal += rounding;

  uint16_t int_part = (uint16_t)floatVal;
  float remainder = floatVal - (float)int_part;
  floatStr[index++] = int_part + '0';             // warning! prints only one decimal before comma

  if (dec > 0) floatStr[index++] = '.';

  while (dec-- > 0)
  {
    remainder *= 10.0;
    uint16_t toPrint = (uint16_t)remainder;
    floatStr[index++] = toPrint + '0';
    remainder -= toPrint;
  }
  floatStr[index++] = '\0';
}

void printFloat(float num, uint8_t decimals, int8_t x = Append, int8_t y = Append) {
  char cstr[5];
  ftoa(num, cstr, decimals);
  printStr(cstr, x, y);
}

enum { ml = 1, deg };

void printNum(uint16_t volume, int8_t postfix = 0) {
  static uint16_t lastVol = 0;

  byte shiftY = 0;
  disp.setFont(BIG_NUM_FONT);

  if (postfix == 1) shiftY = 1;

  if (volume <= 999 && lastVol >= 1000) printStr("    ", Center, 3 - shiftY); // "/" = space
  if (volume <= 99 && lastVol >= 100) {
    printStr(" ", Left, 3 - shiftY);
    printStr(" ", Right, 3 - shiftY);
  }
  if ( (volume <= 9 && lastVol >= 10) || !timeoutState ) {
    printStr("  ", Left, 3 - shiftY);
    //printStr("  ", Right, 3 - shiftY);
  }
  lastVol = volume;

  if (postfix == 1) { // отображение мл
    if (volume > 99) printInt(volume, Left, 3 - shiftY);
    else if (volume > 9) printInt(volume, (disp.displayWidth() - strWidth("00%")) / 2, 3 - shiftY);
    else printInt(volume, (disp.displayWidth() - strWidth("0%")) / 2 + 16, 3 - shiftY);
    printStr("%"); // "ml"
  }
  else if (postfix == 2) { // отображение угла
    if (volume > 99) printInt(volume, (disp.displayWidth() - strWidth("000*")) / 2, 3 - shiftY);
    else if (volume > 9) printInt(volume, (disp.displayWidth() - strWidth("00*")) / 2, 3 - shiftY);
    else printInt(volume, (disp.displayWidth() - strWidth("0*")) / 2 + 16, 3 - shiftY);
    if (postfix == 2)  printStr("*"); // "°"
  }
  else printInt(volume, Center, 3 - shiftY);

  disp.setFont(MAIN_FONT);
#if(MENU_LANG == 1)
  disp.setLetterSpacing(0);
#endif
}

void progressBar(int16_t value, uint16_t maximum = 50) {
  disp.setFont(ProgBar);
  disp.setLetterSpacing(0);
  static int16_t currX = 0, targetX = 0;

  if (value == -1) {
    disp.setCursor(0, 7);
    for (int i = 0; i < disp.displayWidth(); i++) {
      if (i % 2 == 0) disp.write('.');
      else disp.write(' ');
    }
    currX = 0;
    return;
  }

  targetX = value * (128.0 / maximum);

  if (targetX > currX) {
    do
    {
      disp.setCursor(currX, 7);
      disp.write('-');
      if (value == thisVolume && systemState != PUMPING) delay(2);
    }
    while (targetX > ++currX);
  }
  else if (targetX < currX) {
    do {
      disp.setCursor(min(currX, disp.displayWidth() - 1), 7);
      if (currX % 2 == 0) {
        disp.write('.');
        if (value == thisVolume) delay(5);
        else if (value == 0) delay(2);
      }
      else disp.write(' ');
    } while (targetX <= --currX);
    currX = targetX;
  }
}

void displayMode(workModes mode);
void displayMode(workModes mode) {
  disp.setFont(Mode12x26);
  printInt(mode, 1, 0); // выводим иконку режима

#ifdef BATTERY_PIN // выводим иконку батареи
  disp.setFont(Battery12x22);
  printInt(get_battery_percent(), Right, 0);
#endif
}

void displayVolume() {
  disp.setFont(BIG_NUM_FONT);
  printNum(thisVolume, ml);
  progressBar(thisVolume, parameterList[max_volume]);
}

void displayMenu() {
  static uint8_t firstItem = 1, selectedRow = 0;

#if(MENU_LANG == 1)
  disp.setFont(MAIN_FONT);
  disp.setLetterSpacing(0);
#else
  disp.setFont(MAIN_FONT);
#endif

  if (itemSelected) {
    if (menuPage == MAIN_MENU_PAGE) { // выбор елемента на главной странице Меню
      if (menuItem == 1) { // нажали на режим
        workMode = (workModes)!workMode;
        timeoutReset();
        itemSelected = 0;
        showMenu = false;
        disp.clear();
        lastMenuPage = NO_MENU;
        progressBar(-1);
        displayMode(workMode);
        displayVolume();
#if (SAVE_MODE == 1)
        EEPROM.update(eeAddress._workMode, workMode);
#endif
        return;
      }
      else {
        menuPage = (MenuPageName)(menuItem - 1);
        menuItem = 1;
        //disp.clear();
      }
    }
    else if (menuPage == SETTINGS_PAGE) {
      editParameter(menuItem - 1, selectedRow);
      if (!timeoutState) { // произошёл вход в режим ожидания
        itemSelected = 0;
        return;
      }
    }
    else if (menuPage == SERVICE_PAGE)  {
      if (menuItem == menuItemsNum[menuPage]) { // сброс настроек
        resetEEPROM();
        readEEPROM();
      }
      else if (menuItem == 1) menuPage = SERVO_CALIBRATION_PAGE;
      else {
        serviceRoutine((serviceStates)(menuItem - 1));
        lastMenuPage = NO_MENU;
      }
    }
    else if (menuPage == STATISTICS_PAGE) {
      if (menuItem == 1) shots_overall = 0;
      else if (menuItem == 2) volume_overall = 0;
    }
    else if (menuPage == SERVO_CALIBRATION_PAGE) {
      if (menuItem == 1) {
        serviceRoutine(SERVO);
        lastMenuPage = NO_MENU;
      }
      else editParameter(menuItem - 2 + 8, selectedRow);
    }
    itemSelected = 0;
  }

  menuItem = constrain(menuItem, 1, menuItemsNum[menuPage]);

  if (menuPage != lastMenuPage) {
    disp.setInvertMode(0);
    printStr(MenuPages[menuPage][0], Center, 0);
    disp.write('\n');
    lastMenuPage = menuPage;
    firstItem = 1;
  }
  else disp.setCursor(0, 2);


  if (menuItem > firstItem + 2) firstItem = menuItem - 2; // прокрутка елементов меню
  else if (menuItem < firstItem)  firstItem = menuItem;

  for (byte currItem = firstItem; currItem < (firstItem + 3); currItem++) {// отображаем три строки из страницы меню, начиная с firstitem
    if (currItem == menuItem) { // инвертируем текущую строку
#if(MENU_SELECT == 1)
      disp.setInvertMode(1);
#else
      disp.setInvertMode(0);
      disp.write('>');
#endif
      selectedRow = disp.row();
    }
    else  disp.setInvertMode(0);

    if (menuPage == MAIN_MENU_PAGE && currItem == 1)  {
#if(MENU_LANG == 1)
      if (workMode == ManualMode) MenuPages[menuPage][currItem] = " Авто режим";
      else  MenuPages[menuPage][currItem] = " Ручной режим";
#else
      if (workMode == ManualMode) MenuPages[menuPage][currItem] = " Auto mode";
      else  MenuPages[menuPage][currItem] = " Manual mode";
#endif
    }

    if (menuPage == SETTINGS_PAGE)  {
      printStr(MenuPages[menuPage][currItem]);
      clearToEOL();
      byte parameter = currItem - 1;
#if(MENU_LANG == 1)
      if ( (parameter == rainbow_flow) || (parameter == invert_display) ) {
        if (parameterList[parameter] == 0) printStr("(", Right);
        else printStr(")", Right);
      }
      else printInt(parameterList[parameter], Right);
#else
      printInt(parameterList[parameter], Right);
#endif
      disp.write('\n');
    }
    else if (menuPage == STATISTICS_PAGE) {
      printStr(MenuPages[menuPage][currItem]);
      clearToEOL();
      if (currItem == 1)  printInt(shots_overall, Right);
      if (currItem == 2)  {
#if(MENU_LANG == 1)
        if (volume_overall < 100.0) {
          if (volume_overall < 10) printInt(volume_overall, disp.displayWidth() - strWidth("0мл") - 1);
          else printInt(volume_overall, disp.displayWidth() - strWidth("00мл") - 1);
          printStr("мл");
        }
        else {
          printFloat(volume_overall / 1000.0, 2, disp.displayWidth() - strWidth("0.00л") - 1);
          printStr("л");
        }
#else
        if (volume_overall < 100.0) {
          if (volume_overall < 10) printInt(volume_overall, disp.displayWidth() - strWidth("0ml") - 1);
          else printInt(volume_overall, disp.displayWidth() - strWidth("00ml") - 1);
          printStr("ml");
        }
        else {
          printFloat(volume_overall / 1000.0, 2, disp.displayWidth() - strWidth("0.00l"));
          printStr("l");
        }
#endif
      }
      disp.write('\n');
    }
    else if (menuPage == SERVO_CALIBRATION_PAGE) {
      printStr(MenuPages[menuPage][currItem]);
      clearToEOL();
      byte parameter = currItem - 2 + 8;
#if(MENU_LANG == 1)
      if ( (parameter == inverse_servo) || (parameter == auto_parking) ) {
        if (parameterList[parameter] == 0) printStr("(", Right);
        else printStr(")", Right);
      }
      if ( (parameter == servo_speed) || (parameter == keep_power) )
        printInt(parameterList[parameter], Right);
#else
      if (currItem > 1) printInt(parameterList[parameter], Right);
#endif
      disp.write('\n');
    }
    else  {
      printStr(MenuPages[menuPage][currItem]);
      clearToEOL(' ');
      disp.write('\n');
    }
  }
  disp.setInvertMode(0);
}

#endif /* OLED */
