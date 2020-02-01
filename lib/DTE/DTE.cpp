#include "Config.h"
#include "DTE.h"

void DTE::debugPrint(const char message[], bool returnChar) {
  if (debug) {
    Serial.print(message);
    if (returnChar)
      Serial.println();
  }
}

void DTE::debugPrint(const __FlashStringHelper *message, bool returnChar) {
  char buffer[strlen_P((const char *)message) + 1];
  strcpy_P(buffer, (const char *)message);
  debugPrint(buffer, returnChar);
}

void DTE::setDebug(bool debug) { this->debug = debug; }

DTE::DTE(HardwareSerial &hardwareSerial, bool debug) {
  this->hardwareSerial = &hardwareSerial;
  // this->softwareSerial = NULL;
  this->debug = debug;
  this->response[0] = '\0';
  this->responseBuffer[0] = '\0';
  this->echo = true;
  this->baudrate = -1;
}

int DTE::available(void) {
  if (hardwareSerial)
    return hardwareSerial->available();
  // if (softwareSerial)
  //   return softwareSerial->available();
  return -1;
}

bool DTE::isListening(void) {
  // if (softwareSerial)
  //   return softwareSerial->isListening();
  return false;
}

bool DTE::listen(void) {
  // if (softwareSerial)
  //   return softwareSerial->listen();
  return false;
}

void DTE::flush(void) {
  if (hardwareSerial)
    hardwareSerial->flush();
  // if (softwareSerial)
  //   softwareSerial->flush();
}

size_t DTE::write(const char c) {
  if (hardwareSerial)
    return hardwareSerial->write(c);
  // if (softwareSerial)
  //   return softwareSerial->write(c);
  return 0;
}

size_t DTE::write(const char str[]) {
  if (hardwareSerial)
    return hardwareSerial->write(str);
  // if (softwareSerial)
  //   return softwareSerial->write(str);
  return 0;
}

size_t DTE::write(const __FlashStringHelper *str) {
  char buffer[strlen_P((const char *)str) + 1];
  strcpy_P(buffer, (const char *)str);
  return write(buffer);
}

size_t DTE::readBytes(char buffer[], size_t length) {
  if (hardwareSerial)
    return hardwareSerial->readBytes(buffer, length);
  // if (softwareSerial)
  //   return softwareSerial->readBytes(buffer, length);
  return 0;
}

size_t DTE::read(void) {
  if (hardwareSerial)
    return hardwareSerial->read();
  // if (softwareSerial)
  //   return softwareSerial->readBytes(buffer, length);
  return 0;
}

bool DTE::ATResponse(char buffer[], size_t bufferSize, unsigned long timeout) {
  flush();
  unsigned long startRead = millis();
  unsigned int i = 0;
  while (millis() - startRead < timeout) {
    if(Serial1.available() > 0) {
      buffer[i%200] = Serial1.read();
      i++;
    }
  }

  buffer[i%200] = '\0';

  return true;
}

bool DTE::ATResponse(unsigned long timeout) {
  return ATResponse(responseBuffer, strlen(responseBuffer), timeout);
}

bool DTE::ATCommand(const char at[], const char *endResponse, unsigned long timeout) {
  // clearReceivedBuffer();
  debugPrint("command: ", false);
  debugPrint(at, true);
  hardwareSerial->write(at);

  ATResponse(timeout);

  strcpy(response, "");
  strcpy(response, responseBuffer);

  debugPrint("response: ", true);
  debugPrint(response, true);

  return true;
}

bool DTE::ATCommand(const __FlashStringHelper *at, const char endResponse[], unsigned long timeout) {
  char buffer[strlen_P((const char *)at) + 1];
  strcpy_P(buffer, (const char *)at);
  return ATCommand(buffer, endResponse, timeout);
}

bool DTE::isResponseContain(const char expected[]) {
  if (strstr(responseBuffer, expected) == NULL)
    return false;
  return true;
}

bool DTE::isResponseContain(const __FlashStringHelper *expected) {
  char buffer[strlen_P((const char *)expected) + 1];
  strcpy_P(buffer, (const char *)expected);
  return isResponseContain(buffer);
}

bool DTE::isResponseEqual(const char expected[]) {
  if (strcmp(responseBuffer, expected) == 0)
    return false;
  return true;
}

bool DTE::isResponseEqual(const __FlashStringHelper *expected) {
  char buffer[strlen_P((const char *)expected) + 1];
  strcpy_P(buffer, (const char *)expected);
  return isResponseEqual(buffer);
}

bool DTE::isResponseOk(void) {
  if (strcmp(responseBuffer, "OK\r\n"))
    return false;
  return true;
}

bool DTE::AT(void) {
  const char* command = "AT\r\n";
  const char* response = "OK\r\n";
  if(!ATCommand(command, response)) return false;
  delay(100);
  // if (!isResponseOk()) return false;
  return true;
}

bool DTE::atRestartModule(void) {
  const char* command = "AT+RST\r\n";
  const char* response = "OK\r\n";
  if(!ATCommand(command, response, 5000)) return false;
  delay(100);
  // if (!isResponseOk()) return false;
  return true;
}

bool DTE::atMode(unsigned char mode) {
  const __FlashStringHelper* command = F("AT+CWMODE=%d\r\n");
  const char* response = "OK\r\n";
  char buffer[14]; // AT+CWMODE=1

  sprintf_P(buffer, (const char *) command, mode);

  if(!ATCommand(buffer, response)) return false;
  delay(100);
  // if (!isResponseOk()) return false;
  return true;
}

bool DTE::atConnectAp(const char *ssid, const char *password) {
  const __FlashStringHelper* command = F("AT+CWJAP=\"%s\",\"%s\"\r\n");
  const char* response = "OK\r\n";
  char buffer[50];

  sprintf_P(buffer, (const char *) command, ssid, password);

  if(!ATCommand(buffer, response, 6000)) return false;
  delay(100);
  // if (!isResponseOk()) return false;
  return true;
}

bool DTE::atConnectAp(const __FlashStringHelper *ssid, const __FlashStringHelper *password) {
  char bufferSsid[strlen_P((const char *)ssid) + 1];
  char bufferPassword[strlen_P((const char *)password) + 1];

  strcpy_P(bufferSsid, (const char *) ssid);
  strcpy_P(bufferPassword, (const char *) password);
  return atConnectAp(bufferSsid, bufferPassword);
}

void DTE::init(void) {
  // hardwareSerial = &Serial1;
  hardwareSerial->begin(HardwareSerialBaudrate);
}

void DTE::main(void) {

}
