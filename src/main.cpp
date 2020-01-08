#include <Arduino.h>
#include "Config.h"
#include "DTE.h"

DTE dte(Serial1, ESP_SERIAL_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dte.init();
  delay(3000);

  dte.ATCommand(F("AT+RST\r\n"), "ready");

  dte.ATCommand(F("AT\r\n"), "OK");
  // delay(500);
  // dte.ATCommand(F("AT+RST\r\n"), "OK");
  // delay(1000);
  dte.ATCommand(F("AT+CWLAP\r\n"), "OK", 3000);
  delay(1000);
}

void loop() {
  // if(Serial1.available() > 0) {
  //   Serial.write(Serial1.read());
  // }
  // put your main code here, to run repeatedly
  // while (Serial1.available()) {
  //   Serial.write(Serial1.read());
  //   delay(10);
  // }
}
