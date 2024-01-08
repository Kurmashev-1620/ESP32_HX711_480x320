//================================================================================================================================
void Init_DS18B20()                                         // 
{
  sensors.begin();                                          // Инициализируем DS18B20
  //------------------------------------------------------------------------------------------------------------------------------
  tft.setTextColor(TFT_WHITE, TFT_BLACK);					          // Установить цвет текста
  //------------------------------------------------------------------------------------------------------------------------------
  if (sensors.getAddress(insideThermometer, 0))             // Запросить адрес первого датчика
  {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);					        // Установить цвет текста
    tft.print("Address for DS18B20_0: [");                  // 
    printAddress(insideThermometer);                        // Вывести полученный адрес
    tft.println(']');                                       // 
    flag_DS18B20_0 = true;                                  // 
  }
  else
  {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);					        // Установить цвет текста
    tft.print("DS18B20_0:");                                // 
    tft.setTextColor(TFT_YELLOW, TFT_RED);					        // Установить цвет текста
    tft.println("Error_!!!");                               //
    flag_DS18B20_0 = false;                                 // 
  }
  //------------------------------------------------------------------------------------------------------------------------------
  if (sensors.getAddress(outsideThermometer, 1))            // Запросить адрес второго датчика
  {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);					        // Установить цвет текста
    tft.print("Address for DS18B20_1: [");                  // 
    printAddress(outsideThermometer);                       // Вывести полученный адрес
    tft.println(']');                                       // 
    flag_DS18B20_1 = true;                                  // 
  }
  else
  {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);					        // Установить цвет текста
    tft.print("DS18B20_1:");                                // 
    tft.setTextColor(TFT_YELLOW, TFT_RED);					        // Установить цвет текста
    tft.println("Error_!!!");                               //
    flag_DS18B20_1 = false;                                 // 
  }
  //------------------------------------------------------------------------------------------------------------------------------
  sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);  
  // Записать адрес первого датчика
  sensors.setResolution(outsideThermometer, TEMPERATURE_PRECISION); 
  // Записать адрес второго датчика
}
//================================================================================================================================
void Print_ds18b20()                                        // 
{
  sensors.requestTemperatures();                            // 
  //------------------------------------------------------------------------------------------------------------------------------
  if (flag_DS18B20_0)                                       //
  {
    printTemperature(insideThermometer, 0, 310, 1, 2);      // 
  }
  //------------------------------------------------------------------------------------------------------------------------------
  if (flag_DS18B20_1)                                       // 
  {
    printTemperature(outsideThermometer, 0, 300, 1, 3);     // 
  }
}
//================================================================================================================================
void printAddress(DeviceAddress deviceAddress)              // 
{
  for (uint8_t i = 0; i < 8; i++)                           // 
  {
    if (deviceAddress[i] < 16)                              // 
    {
      tft.print("0");                                       // 
    }
    tft.print(deviceAddress[i], HEX);                       // 
  }
}
//================================================================================================================================
void printTemperature(DeviceAddress deviceAddress, uint16_t x, uint16_t y, uint8_t size, uint8_t inDex)
{
  tft.setTextColor(TFT_WHITE, TFT_BLACK);					          // Установить цвет текста
  tft.setTextSize(size);										                // Установить размер символов
  tft.setCursor(x, y);										                  // Установить координату
  //------------------------------------------------------------------------------------------------------------------------------
  float tempC = sensors.getTempC(deviceAddress);            // 
  if (tempC == DEVICE_DISCONNECTED_C)                       // 
  {
    tft.setTextColor(TFT_YELLOW, TFT_RED);					        // Установить цвет текста
    tft.print(" _Error_!!!_");                              //
    array_data_send[inDex] = 99.99;                         // 
    return;                                                 // 
  }
  tft.print("Temp ");                                       // 
  tft.print(tempC);                                         // 
  tft.print(" C");                                          // 

  array_data_send[inDex] = tempC;                           // 
}
//================================================================================================================================
void printResolution(DeviceAddress deviceAddress)           // 
{
  tft.print("Resolution: ");                                // 
  tft.print(sensors.getResolution(deviceAddress));          // 
  tft.println();                                            // 
}
//================================================================================================================================