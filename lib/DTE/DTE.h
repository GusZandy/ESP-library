#ifndef DTE_h
#define DTE_h

#include <Arduino.h>

class DTE{
private:
  HardwareSerial *hardwareSerial;
  // SoftwareSerial *softwareSerial;

  bool debug;
  char response[203];
  char responseBuffer[203];
  bool echo;
  bool sleep;
  long baudrate;

protected:
  void debugPrint(const char message[], bool returnChar = false);
  void debugPrint(const __FlashStringHelper *message, bool returnChar = false);

public:
    DTE(HardwareSerial &hardwareSerial, bool debug = false);
    bool ATResponse(char buffer[], size_t bufferSize,
                    unsigned long timeout = 5000);
    bool ATResponse(unsigned long timeout = 5000);

    bool isResponseContain(const char expected[]);
    bool isResponseContain(const __FlashStringHelper *expected);
    bool isResponseEqual(const char expected[]);
    bool isResponseEqual(const __FlashStringHelper *expected);
    bool isResponseOk(void);
    char *getResponse(void) { return response; }

    int available(void);
    bool isListening(void);
    bool listen(void);
    void flush(void);
    size_t write(const char c);
    size_t write(const char str[]);
    size_t write(const __FlashStringHelper *str);
    size_t readBytes(char buffer[], size_t length);
    size_t read(void);

    void clearReceivedBuffer(void);
    bool ATCommand(const char at[], const char endResponse[], unsigned long timeout = 1000);
    bool ATCommand(const __FlashStringHelper *at, const char endResponse[], unsigned long timeout = 1000);

    bool AT(void);
    bool atRestartModule(void);
    bool atMode(unsigned char mode);
    bool atConnectAp(const char *ssid, const char *password);
    bool atConnectAp(const __FlashStringHelper *ssid, const __FlashStringHelper *password);

    void setDebug(bool debug);

    void init(void);
    void main(void);
};

#endif
