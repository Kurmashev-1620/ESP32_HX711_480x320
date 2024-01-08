//================================================================================================================================
void Display_level_PWM()
{
  Display_write_level_PWM_1(0);
  Display_write_level_PWM_2(0);
  Display_write_level_PWM_3(0);
  flag_first_start = false;
}
//================================================================================================================================
void Display_write_level_PWM_1(int val_PWM)                 // 
{
  tft.fillRect(val_PWM, 51, 255 - val_PWM, 8, TFT_BLACK);   // Очистить 
  tft.drawRect(0,50, 257, 10, TFT_WHITE);                   // Вывести квадрат
  tft.fillRect(1,51, val_PWM, 8, TFT_YELLOW);               // Вывести уровень PWM
}
//================================================================================================================================
void Display_write_level_PWM_2(int val_PWM)                 // 
{
  tft.fillRect(val_PWM, 61, 255 - val_PWM, 8, TFT_BLACK);   // Очистить 
  tft.drawRect(0, 60, 257, 10, TFT_WHITE);                  // Вывести квадрат
  tft.fillRect(1, 61, val_PWM, 8, TFT_YELLOW);              // Вывести уровень PWM
}
//================================================================================================================================
void Display_write_level_PWM_3(int val_PWM)                 // 
{
  tft.fillRect(val_PWM, 71, 255 - val_PWM, 8, TFT_BLACK);   // Очистить 
  tft.drawRect(0, 70, 257, 10, TFT_WHITE);                  // Вывести квадрат
  tft.fillRect(1, 71, val_PWM, 8, TFT_YELLOW);              // Вывести уровень PWM
}
//================================================================================================================================