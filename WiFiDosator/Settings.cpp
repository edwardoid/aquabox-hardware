#include "Settings.h"
#include "Routines.h"
#include <EEPROM.h>

SettingsImpl Settings;

SettingsKeys AllSettings;

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
}

void SettingsImpl::write()
{
    UI.pushScreen(UIScreenId::SavingSettings);
    EEPROM.put(0, AllSettings);
    EEPROM.commit();
    UI.popScreen();
}