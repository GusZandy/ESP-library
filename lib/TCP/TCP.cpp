#include "TCP.h"

TCP::TCP(DTE &dte) {
  this->dte = &dte;
  this->debug = true;
}

void TCP::debugPrint(const char message[], bool returnChar) {
  if (debug) {
    Serial.print(message);
    if (returnChar)
      Serial.println();
  }
}

void TCP::debugPrint(const __FlashStringHelper *message, bool returnChar) {
  char buffer[strlen_P((const char *)message) + 1];
  strcpy_P(buffer, (const char *)message);
  debugPrint(buffer, returnChar);
}

bool TCP::begin(const char* type, const char *address, int port) {
  const __FlashStringHelper *command = F("AT+CIPSTART=\"%s\",\"%s\",%d\r\n");
  const char* response = "OK\r\n";
  char buffer[50];

  sprintf_P(buffer, (const char *) command, type, address, port);

  if (!dte->ATCommand(buffer, response, 6000)) return false;
  delay(100);
  // if (!dte->isResponseContain("OK")) return false;
  // if (!dte->isResponseContain("CONNECT")) return false;
  return true;
}

bool TCP::send(const char *data) {
  const __FlashStringHelper *command = F("AT+CIPSEND=%d\r\n");
  const char* response = "OK\r\n";
  char commandBuffer[20];

  sprintf_P(commandBuffer, (const char *) command, strlen(data));

  if (!dte->ATCommand(commandBuffer, response, 1000)) return false;
  if (!dte->ATCommand(data, response, 1000)) return false;

  return true;
}

bool TCP::close(void) {
  const __FlashStringHelper *command = F("AT+CIPCLOSE\r\n");
  const char* response = "OK\r\n";

  if (!dte->ATCommand((const char*) command, response, 1000)) return false;

  return true;
}
