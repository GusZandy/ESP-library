#include <Arduino.h>
#include "Config.h"
#include "DTE.h"
#include "TCP.h"

DTE dte(Serial1, ESP_SERIAL_PIN);
TCP tcp(dte);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dte.init();
  delay(3000);

  // dte.ATCommand(F("AT+RST\r\n"), "ready");

  dte.atRestartModule();
  dte.AT();
  dte.atMode(1);
  dte.atConnectAp(F("mbah dul"), F("12mbahDul345"));
  dte.AT();
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
  tcp.begin("TCP", "www.postman-echo.com", 80);
  tcp.send("GET /get?name=Zandy HTTP/1.1\r\nHost: www.postman-echo.com\r\n\r\n");
  tcp.close();
  delay(1000);
}
