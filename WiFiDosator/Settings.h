#ifndef SETTINGS_H
#define SETTINGS_H

#include <AquaboxProto.h>

struct ChannelSettings
{
    ChannelSettings();
    aquabox::proto::byte_t Serial[SERIAL_LEN];
    aquabox::proto::byte_t Token[TOKEN_LEN];
    unsigned long CalibrationDelay;
};

struct SettingsKeys
{
    char SSID[32];
    char PASSWD[32];;
    char MasterIp[16];
    int  MasterPort;
    uint8_t Brightness;
    uint8_t Delay;
    ChannelSettings Channel1;  
    ChannelSettings Channel2;
};

extern SettingsKeys AllSettings;

class SettingsImpl
{
public:
  void begin();
  void read();
  void write();
};

extern SettingsImpl Settings;


#endif // SETTINGS_H