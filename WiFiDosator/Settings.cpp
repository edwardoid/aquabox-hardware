#include "Settings.h"
#include "Routines.h"
#include <EEPROM.h>

SettingsKeys AllSettings;

SettingsImpl Settings;

aquabox::proto::byte_t* TOKEN[TOKEN_LEN]     = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
aquabox::proto::byte_t CH1_SERIAL[SERIAL_LEN] = { 0xD0, 0xE0, 0xA0, 0xD0, 0xB0, 0xE0, 0xE0, 0xF0 };
aquabox::proto::byte_t CH2_SERIAL[SERIAL_LEN] = { 0xD1, 0xE1, 0xA1, 0xD1, 0xB1, 0xE1, 0xE1, 0xF1 };

ChannelSettings::ChannelSettings()
{
  
}

void SettingsImpl::begin()
{
    EEPROM.begin(sizeof(AllSettings));
    read();
}

void SettingsImpl::read()
{
   AllSettings = EEPROM.get(0, AllSettings);
   memcpy(AllSettings.Channel1.Serial, CH1_SERIAL, SERIAL_LEN);
   memcpy(AllSettings.Channel1.Token, TOKEN, TOKEN_LEN);

   memcpy(AllSettings.Channel2.Serial, CH2_SERIAL, SERIAL_LEN);
   memcpy(AllSettings.Channel2.Token, TOKEN, TOKEN_LEN);
}

void SettingsImpl::write()
{
    UI.pushScreen(UIScreenId::SavingSettings);
    EEPROM.put(0, AllSettings);
    EEPROM.commit();
    UI.popScreen();
}