void MotorAvtoMove(uint16_t load)
{
  uint16_t val = LoadMaxReal - load;

  val = map(i, 0, i, 0, 255);

  if (load < LoadMaxReal)
  {
    analogWrite(vibration_motor_2, val);
  }
}