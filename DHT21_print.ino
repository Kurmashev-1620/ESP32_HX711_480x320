//================================================================================================================================
void Init_DHT()                                             // Функция инициализации датчика DHT
{
  float h = dht.readHumidity();                             // Чтение уровня влажности с DHT и сохранение в переменную h

  if (!isnan(h))                                            // Проверка, является ли полученное значение допустимым
  {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);                 // Установка цвета текста на белый и фона на чёрный
    tft.print("DHT_Humidity: ");                            // Вывод текста "DHT_Humidity: "
    tft.setTextColor(TFT_BLACK, TFT_GREEN);                 // Установка цвета текста на чёрный и фона на зелёный
    tft.println("ON");                                      // Вывод текста "ON" на экран, датчик влажности работает
  }
  else
  {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);                 // Установка цвета текста на белый и фона на чёрный
    tft.print("DHT_Humidity: ");                            // Вывод текста "DHT_Humidity: "
    tft.setTextColor(TFT_YELLOW, TFT_RED);                  // Установка цвета текста на жёлтый и фона на красный
    tft.println("OFF");                                     // Вывод текста "OFF" на экран, датчик влажности не работает
  }

  float t = dht.readTemperature();                          // Чтение температуры с датчика DHT и сохранение в переменную t

  if (!isnan(t))                                            // Проверка, является ли полученное значение допустимым
  {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);                 // Установка цвета текста на белый и фона на чёрный
    tft.print("DHT_Temperature: ");                         // Вывод текста "DHT_Temperature: "
    tft.setTextColor(TFT_BLACK, TFT_GREEN);                 // Установка цвета текста на чёрный и фона на зелёный
    tft.println("ON");                                      // Вывод текста "ON" на экран, датчик температуры работает
  }
  else
  {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);                 // Установка цвета текста на белый и фона на чёрный
    tft.print("DHT_Temperature: ");                         // Вывод текста "DHT_Temperature: "
    tft.setTextColor(TFT_YELLOW, TFT_RED);                  // Установка цвета текста на жёлтый и фона на красный
    tft.println("OFF");                                     // Вывод текста "OFF" на экран, датчик температуры не работает
  }
}
//================================================================================================================================
void printHumi(int x, int y, uint8_t size)                  //
{
  float h = dht.readHumidity();                             // 
  
  if (!isnan(h))                                            //
  {
    tft.setCursor(x, y);                                    // 
    tft.setTextSize(size);                                  // 
    tft.setTextColor(TFT_WHITE, TFT_BLACK);                 // 
    tft.print("Humidity: ");                                // 
    tft.print(h);                                           // 
    tft.println(" %");                                      // 

    array_data_send[0] = h;                                 // 
  }
  else
  {
    tft.setCursor(x, y);                                    // 
    tft.setTextSize(size);                                  // 
    tft.setTextColor(TFT_YELLOW, TFT_RED);                  // 
    tft.print("Humidity: ");                                // 
    tft.print("ERROR");                                     // 
    tft.println(" %");                                      // 

    array_data_send[0] = 99.99;                             // 
  }
}
//================================================================================================================================
void printTemp(int x, int y, uint8_t size)                  //
{
  float t = dht.readTemperature();                          // 

  if (!isnan(t))                                            //
  {
    tft.setCursor(x, y);                                    // 
    tft.setTextSize(size);                                  // 
    tft.setTextColor(TFT_WHITE, TFT_BLACK);                 // 
    tft.print("Temperature: ");                             // 
    tft.print(t);                                           // 
    tft.println(" C");                                      // 

    array_data_send[1] = t;                                 // 
  }
  else
  {
    tft.setCursor(x, y);                                    // 
    tft.setTextSize(size);                                  // 
    tft.setTextColor(TFT_YELLOW, TFT_RED);                  // 
    tft.print("Temperature: ");                             // 
    tft.print("ERROR");                                     // 
    tft.println(" C");                                      // 

    array_data_send[1] = 99.99;                             // 
  }
}
//================================================================================================================================