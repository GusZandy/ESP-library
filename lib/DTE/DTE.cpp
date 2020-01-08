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
  Serial.println(timeout);
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

  // unsigned long startRead = millis();
  // while (millis() - startRead < timeout) {
  //   if(Serial1.available() > 0) {
  //     Serial.write(Serial1.read());
  //   }
  // }
  ATResponse(timeout);
  //
  Serial.println(F("Response: "));
  Serial.println(responseBuffer);

  return true;
}

bool DTE::ATCommand(const __FlashStringHelper *at, const char endResponse[], unsigned long timeout) {
  char buffer[strlen_P((const char *)at) + 1];
  strcpy_P(buffer, (const char *)at);
  return ATCommand(buffer, endResponse, timeout);
}

void DTE::init(void) {
  // hardwareSerial = &Serial1;
  hardwareSerial->begin(HardwareSerialBaudrate);
}

void DTE::main(void) {

}
