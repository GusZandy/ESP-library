#include <Arduino.h>
#include "Config.h"
#include "DTE.h"

DTE dte(Serial1, ESP_SERIAL_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dte.init();
  delay(1000);

  dte.ATCommand(F("AT\r\n"), "OK", 5000, 10);
  delay(1000);
  dte.ATCommand(F("AT+RST\r\n"), "OK", 5000, 10);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
}
