void parsing() {
  while (Serial.available() > 0) {
    char incomingByte = Serial.read();      // обязательно ЧИТАЕМ входящий символ
    if (incomingByte == '$') {              // если это $
      getStarted = true;                    // поднимаем флаг, что можно парсить
    } else if (incomingByte != ';' && getStarted) { // пока это не ;
      // в общем происходит всякая магия, парсинг осуществляется функцией strtok_r
      inputData[index_parse] = incomingByte;
      index_parse++;
      inputData[index_parse] = NULL;
    } else {
      if (getStarted) {
        char *p = inputData;
        char *str;
        index_parse = 0;
        String value = "";
        while ((str = strtok_r(p, " ", & p)) != NULL) {
          string_convert = str;
          intData[index_parse] = string_convert.toInt();
          index_parse++;
        }
        index_parse = 0;
      }
    }
    if (incomingByte == ';') {        // если таки приняли ; - конец парсинга
      getStarted = false;
      recievedFlag = true;
    }
  }
}
