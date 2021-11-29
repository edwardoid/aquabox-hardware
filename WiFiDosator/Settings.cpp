#include "Settings.h"
#include "Routines.h"
#include <EEPROM.h>

SettingsKeys AllSettings;

SettingsImpl Settings;

aquabox::proto::byte_t* TOKEN = (aquabox::proto::byte_t*)("allow me");
aquabox::proto::byte_t CH1_SERIAL[] = { 'd', 'o', 's', 'e', 'r', 'c', 'h', '1' };
aquabox::proto::byte_t CH2_SERIAL[] = { 'd', 'o', 's', 'e', 'r', 'c', 'h', '1' };

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