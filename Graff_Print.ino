//================================================================================================================================
void Graff_Print(float y_os)                                //
{
  if (graff_time == WIDTH_DISPLAY) graff_time = 0;          // 
  tft.drawPixel(graff_time, y_os + 200, TFT_GREEN);         // 
  graff_time++;                                             // Инерементировать
}
//================================================================================================================================