#ifndef TCP_h
#define TCP_h

#include <Arduino.h>
#include <IPAddress.h>
#include "Config.h"

#include "DTE.h"


class TCP {
private:
  DTE *dte;
  IPAddress *ip;
  // SoftwareSerial *softwareSerial;

  bool debug;
  char response[203];
  char responseBuffer[203];

protected:
  void debugPrint(const char message[], bool returnChar = false);
  void debugPrint(const __FlashStringHelper *message, bool returnChar = false);

public:
  TCP(DTE &dte);

  bool begin(const char* type, const char *address, int port);
  bool send(const char* data);
  bool send(const __FlashStringHelper *data);
  bool close(void);

  void setDebug(bool debug);

  void init(void);
  void main(void);
};

#endif
