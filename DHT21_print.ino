void Init_DHT()                                             // 
{
  float h = dht.readHumidity();                             // 

  if (!isnan(h))                                            // 
  {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);                 // 
    tft.print("DHT_Humidity: ");                            // 

    tft.setTextColor(TFT_BLACK, TFT_GREEN);					        // Установить цвет текста
    tft.println("ON");                                      // 
  }
  else
  {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);                 // 
    tft.print("DHT_Humidity: ");                            // 

    tft.setTextColor(TFT_YELLOW, TFT_RED);					        // Установить цвет текста
    tft.println("OFF");                                     // 
  }

  float t = dht.readTemperature();                          // 

  if (!isnan(t))
  {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);                 // 
    tft.print("DHT_Temperature: ");                         // 

    tft.setTextColor(TFT_BLACK, TFT_GREEN);					        // Установить цвет текста
    tft.println("ON");                                      // 
  }
  else
  {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);                 // 
    tft.print("DHT_Temperature: ");                         // 

    tft.setTextColor(TFT_YELLOW, TFT_RED);					        // Установить цвет текста
    tft.println("OFF");                                     // 
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
  }
  else
  {
    tft.setCursor(x, y);                                    // 
    tft.setTextSize(size);                                  // 
    tft.setTextColor(TFT_YELLOW, TFT_RED);                  // 
    tft.print("Humidity: ");                                // 
    tft.print("ERROR");                                     // 
    tft.println(" %");                                      // 
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
  }
  else
  {
    tft.setCursor(x, y);                                    // 
    tft.setTextSize(size);                                  // 
    tft.setTextColor(TFT_YELLOW, TFT_RED);                  // 
    tft.print("Temperature: ");                             // 
    tft.print("ERROR");                                     // 
    tft.println(" C");                                      // 
  }
}
//================================================================================================================================