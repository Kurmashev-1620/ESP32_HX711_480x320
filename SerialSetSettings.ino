void SerialSetSettings()                                    // 
{
  Serial.println("99," + String(serialPrintInterval) + ";");//
  delay(10);
  Serial.println("98," + String(calibrationValue) + ";");   // 
  delay(10);
}