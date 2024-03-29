/*
__________________________________________________________________________________
| Датчик без адресации (один на линии) | Датчик с адресацией (несколько на линии) |
|______________________________________|__________________________________________|
| .setResolution(...) ~ 3591.125 мкс   | .setResolution(...) ~ 8276.0625 мкс 	    |
| .requestTemp() ~ 1839.9375 мкс	     | .requestTemp() ~ 6522.1875 мкс 		      |
|______________________________________|__________________________________________|
|							                С использованием CRC8								                |
|_________________________________________________________________________________|
| .readAddress(...) ~ 6467.3125 мкс	   | float .getTemp() ~ 12250.25 мкс	 	      | 
| float .getTemp() ~ 7620.25 мкс	     | int .getTemp() ~ 12250.2500 мкс 		      |	
| int .getTemp() ~ 7574.0625 мкс	     | 									                        |
|______________________________________|__________________________________________|
|							               Без использования CRC8								                |
|_________________________________________________________________________________|
| .readAddress(...) ~ 6394.3125 мкс    | float .getTemp() ~ 7809.1250 мкс	 	      |
| float .getTemp() ~ 3132.9375 мкс	   | int .getTemp() ~ 7809.1250 мкс	 		      |
| int .getTemp() ~ 3132.9375 мкс	     | 								  		                    |
|______________________________________|__________________________________________|

*/
//================================================================================================================================
#include <TFT_eSPI.h>										                    // Библиотека для дисплея TFT 3.5 480x320
#include <HX711_ADC.h>										                  // Библиотека для модуля HX711 (Датчик веса)
#include <DHT.h>                                            // Библиотека для памяти датчика температуры/влажность
#include <OneWire.h>                                        // Библиотека для подключения по одному проводу
#include <DallasTemperature.h>                              // Библиотека для подключения значений с DS18B20
#include <Beastdevices_INA3221.h>                           // Библиотека для подключения датчика INA3221
#include "Bitmap.h"                                         // Bitmaps
//================================================================================================================================
#define PRINT_DEC_POINTS  3                                 // Колличество нулей после зяпятой INA3221
#define TEMPERATURE_PRECISION 9                             // Колличество усреднений занчения DS18B20
//--------------------------------------------------------------------------------------------------------------------------------
#define PARSE_AMOUNT 5                                      // число значений в массиве, который хотим получить
#define INPUT_AMOUNT 80                                     // максимальное количество символов в пакете, который идёт в сериал
//--------------------------------------------------------------------------------------------------------------------------------
#define HEIGHT_DISPLAY 320                                  // Высота дисплея
#define WIDTH_DISPLAY 480                                   // Длина дисплея
//================================================================================================================================
const int ONE_WIRE_BUS          =  0;                       // Пин для подключения DS18B20
//--------------------------------------------------------------------------------------------------------------------------------
const int DHTPIN                = 13;  							        // Пин для подключения лини данных для DHT 21 (AM2301)
//--------------------------------------------------------------------------------------------------------------------------------
const int HX711_dout            = 27;  							        // Пин для подключения лини данных для модуля HX711
const int HX711_sck             = 26;   						        // Пин для подключения лини синхронизации для модуля HX711
//--------------------------------------------------------------------------------------------------------------------------------
const int auger_motor           = 25;							          // Пин для подключения мотора "Шнек"
const int vibration_motor_1     = 33;							          // Пин для подключения первого мотора "Вибро"
const int vibration_motor_2     = 32;							          // Пин для подключения второго мотора "Вибро"
//================================================================================================================================
const int calVal_eepromAdress = 0;							            // Адрес EEPROM для коллибровочного значения
//--------------------------------------------------------------------------------------------------------------------------------
unsigned long t = 0;										                    // Таймер времени для датчика HX711
unsigned long timeINA = 0;										              // Таймер времени для датчика INA3221
unsigned long timeSerial_Send = 0;										      // Таймер времени для отправки данных в программу
unsigned long timeSerial_graff = 0;										      // Таймер времени для отображения графика
//--------------------------------------------------------------------------------------------------------------------------------
float calibrationValue = 223.0;							                // Задаём коллибровочные значения
int serialPrintInterval = 100;						                  // Интервал времени запроса веса
int old_LoadCell = 0;                                       // Старое значение веса
float array_data_send[4];                                   // Массив передачи данных
byte inD = 6;                                               // Индекс 
//--------------------------------------------------------------------------------------------------------------------------------
uint16_t x_readPrr = 0;                                     // 
uint16_t y_readPrr = 0;                                     //
uint16_t xs_readPrr = 0;                                    // 
uint16_t ys_readPrr = 0;                                    //  
//--------------------------------------------------------------------------------------------------------------------------------
bool flag_hx711         = false;									          // По умолчанию выключаем датчик HX711
bool flag_DS18B20_0     = false;                            // Флаг датчика DS18B20 по первому адресу
bool flag_DS18B20_1     = false;                            // Флаг датчика DS18B20 по второму адресу
bool flag_bitMap_hx711  = true;                             // Флаг отрисовки bimPam_hx711
bool flag_tare_res      = false;                            // Флаг сброса Тарирования
bool flag_first_start   = false;                            // Флаг первго включения
//--------------------------------------------------------------------------------------------------------------------------------
int graff_time = 0;
//--------------------------------------------------------------------------------------------------------------------------------
char inputData[INPUT_AMOUNT];                               // Массив входных значений (СИМВОЛЫ)
int intData[PARSE_AMOUNT];                                  // Массив численных значений после парсинга
bool recievedFlag;                                          // 
bool getStarted;                                            // 
byte index_parse;                                           // 
String string_convert;                                      // 
//--------------------------------------------------------------------------------------------------------------------------------
uint16_t LoadMaxReal = 0;                                   // Нагрузка на весы реальная 
//================================================================================================================================
TFT_eSPI tft = TFT_eSPI();									                // Объявляем объект для работы с дисплеем
//--------------------------------------------------------------------------------------------------------------------------------
DHT dht(DHTPIN, DHT21);                                     // Объявляем объект для работы с AM2301
//--------------------------------------------------------------------------------------------------------------------------------
HX711_ADC LoadCell(HX711_dout, HX711_sck);					        // Объявляем объект для работы с модулем HX711
//--------------------------------------------------------------------------------------------------------------------------------
OneWire oneWire(ONE_WIRE_BUS);                              // Объявляем объект для работы с одной линией
DallasTemperature sensors(&oneWire);                        // Объявляем объект для работы с DS18B20
DeviceAddress insideThermometer, outsideThermometer;        // Создаём переменные для хранения адресов DS18B20
//--------------------------------------------------------------------------------------------------------------------------------
Beastdevices_INA3221 ina3221(INA3221_ADDR41_VCC);           // Объявляем объект для работы с INA3221
//================================================================================================================================
void setup()												                        // 
{
  Serial.begin(115200);										                  // Настраиваем Serial
  Serial.setTimeout(10);                                    // Настроить время ожижания Serial
  //------------------------------------------------------------------------------------------------------------------------------
  tft.init();												                        // Инициализируем дисплей
  tft.setRotation(3);										                    // Устанавливаем Rotation для дисплея
  tft.fillScreen(TFT_BLACK);								                // Очищаем дисплей
  tft.setTextColor(TFT_WHITE, TFT_BLACK);					          // Установить цвет текста
  tft.setTextSize(1);									                      // Установить размер символов
  tft.setCursor(0, 0);								                      // Установить координату
  //------------------------------------------------------------------------------------------------------------------------------
  dht.begin();                                              // Инициализируем DHT
  //------------------------------------------------------------------------------------------------------------------------------
  pinMode(auger_motor, OUTPUT);									            // Настраиваем пин как выход
  pinMode(vibration_motor_1, OUTPUT);									      // Настраиваем пин как выход
  pinMode(vibration_motor_2, OUTPUT);									      // Настраиваем пин как выход
  //------------------------------------------------------------------------------------------------------------------------------
  Init_HX711();                                             // Инициализируем весовой датчик HX711
  Init_DS18B20();                                           // Инициализируем датчики температуры DS18B20
  Init_DHT();                                               // Инициализируем датчик DHT21
  Init_INA3221();                                           // Инициализируем датчика INA3221
  //------------------------------------------------------------------------------------------------------------------------------
  delay(2000);                                              // Задержка инициализации
  //------------------------------------------------------------------------------------------------------------------------------
  tft.fillScreen(TFT_BLACK);								                // Очищаем дисплей
}
//================================================================================================================================
void loop()													                        // Гавный ЦиК-л
{
  if (flag_first_start)                                     // 
  {
    Display_level_PWM();                                    // Отобразить уровни 
    SerialSetSettings();                                    // Отобразить калибровочные значения
  }
  //------------------------------------------------------------------------------------------------------------------------------
  printHumi(378, 300, 1);                                   // Вывести на дисплей Влажность
  printTemp(360, 310, 1);                                   // Вывести на дисплей Температуру
  Print_ds18b20();                                          // Вывести на дисплей Температуру (DS18B20)
  PrintLoad(220, 285);                                      // Вывести на дисплей вес
  Print_INA3221(0, 270);                                    // Вывести на дисплей значение тока и напряжения
  //------------------------------------------------------------------------------------------------------------------------------
  parsing();                                                // Функция парсинга
  //------------------------------------------------------------------------------------------------------------------------------
  if (recievedFlag)                                         // Если получены данные
  {
    recievedFlag = false;                                   // Сбросить флаг принятых данных
    SerialDebug();                                          // 
  }
  //------------------------------------------------------------------------------------------------------------------------------
  if (millis() > timeSerial_Send + 50)                      // 
  {
    if (inD == 11) inD = 6;                                 //  
    String val_str = String(inD) + "," + \
    String(array_data_send[inD - 6]) + ";";                 // 
    Serial.println(val_str);                                //
    inD++;                                                  // 
    //----------------------------------------------------------------------------------------------------------------------------
    timeSerial_Send = millis();                             // 
  }
  //------------------------------------------------------------------------------------------------------------------------------
  if (millis() > timeSerial_graff + 500)                    // 
  {
    Graff_Print(array_data_send[3]);                        // Отобразить граффик
    //----------------------------------------------------------------------------------------------------------------------------
    timeSerial_graff = millis();                            // 
  }
}
//================================================================================================================================