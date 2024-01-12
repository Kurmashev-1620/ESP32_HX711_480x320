//================================================================================================================================
void SerialDebug()											                    // Дебаг
{
  int key = intData[0];									                    // Символ
  int val = intData[1];								                      // Число
  //------------------------------------------------------------------------------------------------------------------------------
  tft.setTextSize(1);                                       // Установить размер текста
  tft.setTextColor(TFT_WHITE, TFT_BLACK);					          // Установить цвет текста
  //------------------------------------------------------------------------------------------------------------------------------
  switch (key)												                      // 
  {
    //----------------------------------------------------------------------------------------------------------------------------
    case 1:												                          // 
		  if (val >= 0 && val < 256)                            // 
      {
        analogWrite(auger_motor, val);					            // 
        Display_write_level_PWM_1(val);                     // 

        val = map(val, 0, 255, 0, 100);                     //

        tft.setCursor(260, 50);                             // 
        tft.print("auger_motor: ");                         // 
        tft.print(val);                                     // 
        tft.print(" %");                                    // 
        tft.println("  ");                                  // 

        String val_str = "1," + String(val) + ";";          // 
        Serial.println(val_str);                            //
      }
		  break;												                        // 
    //----------------------------------------------------------------------------------------------------------------------------
    case 2:                                                 // 
      if (val >= 0 && val < 256)                            // 
      {
        analogWrite(vibration_motor_1, val);					      // 
        Display_write_level_PWM_2(val);                     // 

        val = map(val, 0, 255, 0, 100);                     //

        tft.setCursor(260, 60);                             // 
        tft.print("vibration_motor_1: ");                   // 
        tft.print(val);                                     // 
        tft.print(" %");                                    // 
        tft.println("  ");                                  // 

        String val_str = "2," + String(val) + ";";          // 
        Serial.println(val_str);                            //
      }
      break;												                        // 
    //----------------------------------------------------------------------------------------------------------------------------
    case 3:                                                 // 
      if (val >= 0 && val < 256)                            // 
      {
        analogWrite(vibration_motor_2, val);					      // 
        Display_write_level_PWM_3(val);                     // 

        val = map(val, 0, 255, 0, 100);                     //

        tft.setCursor(260, 70);                             // 
        tft.print("vibration_motor_2: ");                   // 
        tft.print(val);                                     // 
        tft.print(" %");                                    // 
        tft.println("  ");                                  // 

        String val_str = "3," + String(val) + ";";          // 
        Serial.println(val_str);                            //
      }
      break;                                                // 
    //----------------------------------------------------------------------------------------------------------------------------
    case 0:                                                 // 
      LoadCell.tareNoDelay();                               // 
      while (LoadCell.getTareStatus()){}                    // 
      tft.setCursor(0, 10);                                 // 
      tft.print("Tare: ");                                  // 
      tft.println("Complite");                              //
      flag_tare_res = true;                                 // 
      break;											                          // 
    //----------------------------------------------------------------------------------------------------------------------------
    case 4:                                                 //  
      float caliValue;
      caliValue = (float)val / 100.0;                       // Преобразование val в float и деление на 100
      calibrationValue = caliValue;												  // 
      
      if (flag_hx711)                                       // 
      {
        LoadCell.setCalFactor(calibrationValue);            // Если датчи HX711 определен то задать коллибровочные значение
      }
      
      tft.setCursor(0, 0);                                  // 
      tft.print("calibrationValue: ");                      // 
      tft.println(calibrationValue);                        // 
      break;                                                //
    //----------------------------------------------------------------------------------------------------------------------------
    case 5:                                                 // 
      serialPrintInterval = val;												    // 
      tft.setCursor(0, 40);                                 // 
      tft.print("serialPrintInterval: ");                   // 
      tft.println(serialPrintInterval);                     // 
      break;                                                // 
    //----------------------------------------------------------------------------------------------------------------------------
    case 6:                                                 // 
      tft.drawRect(x_readPrr,y_readPrr, xs_readPrr, ys_readPrr, TFT_BLACK);        // Вывести квадрат
      x_readPrr = val;												              // 
      tft.setCursor(0, 0);                                  // 
      tft.print("x_readPrr: ");                             // 
      tft.println(x_readPrr);                               // 
      tft.drawRect(x_readPrr,y_readPrr, xs_readPrr, ys_readPrr, TFT_WHITE);        // Вывести квадрат
      break;                                                // 
    //----------------------------------------------------------------------------------------------------------------------------
    case 7:                                                 // 
      tft.drawRect(x_readPrr,y_readPrr, xs_readPrr, ys_readPrr, TFT_BLACK);        // Вывести квадрат
      y_readPrr = val;												              // 
      tft.setCursor(0, 10);                                 // 
      tft.print("y_readPrr: ");                             // 
      tft.println(x_readPrr);                               // 
      tft.drawRect(x_readPrr,y_readPrr, xs_readPrr, ys_readPrr, TFT_WHITE);        // Вывести квадрат
      break;                                                // 
    //----------------------------------------------------------------------------------------------------------------------------
    case 8:                                                 // 
      tft.drawRect(x_readPrr,y_readPrr, xs_readPrr, ys_readPrr, TFT_BLACK);        // Вывести квадрат
      xs_readPrr = val;												              // 
      tft.setCursor(0, 10);                                 // 
      tft.print("xs_readPrr: ");                            // 
      tft.println(x_readPrr);                               // 
      tft.drawRect(x_readPrr,y_readPrr, xs_readPrr, ys_readPrr, TFT_WHITE);        // Вывести квадрат
      break;                                                // 
    //----------------------------------------------------------------------------------------------------------------------------
    case 9:                                                 // 
      tft.drawRect(x_readPrr,y_readPrr, xs_readPrr, ys_readPrr, TFT_BLACK);        // Вывести квадрат
      ys_readPrr = val;												              // 
      tft.setCursor(0, 10);                                 // 
      tft.print("ys_readPrr: ");                            // 
      tft.println(x_readPrr);                               // 
      tft.drawRect(x_readPrr,y_readPrr, xs_readPrr, ys_readPrr, TFT_WHITE);        // Вывести квадрат
      break;                                                // 
    //----------------------------------------------------------------------------------------------------------------------------
    case 10:                                                // 
      LoadMaxReal = val;												            // 
      tft.setCursor(0, 10);                                 // 
      tft.print("LoadMaxReal: ");                           // 
      tft.println(LoadMaxReal);                             // 
      break;                                                // 
    //----------------------------------------------------------------------------------------------------------------------------
    case 99:                                                // 
      if (val == 753)                                       //
      {
        flag_first_start = true;                            // 
      }
      break;                                                // 
    //----------------------------------------------------------------------------------------------------------------------------
  }
}
//================================================================================================================================