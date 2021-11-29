#include "Channel.h"
#include "GlobalConfigs.h"

Channel::Channel(ChannelSettings& channel, uint8_t pin)
        : Settings(channel)
        , TimesProperty(pin)
        , Stepper(TimesProperty, &HermesIO, channel.Token, Settings.Serial)
        , Pin(pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}


void Channel::processNextMessage()
{
    if (HermesIO.available() >= sizeof(aquabox::proto::Message)) {
      if(Stepper.processNextMessage()) {
        yield();
      }
    } else {
      HermesIO.wait(sizeof(aquabox::proto::Message));
      yield();
    }
}

uint32_t Channel::millilitersRemain() const
{
    return TimesProperty.CurrentValue;
}

Channel Channels[CHANNELS_COUNT] = { Channel(AllSettings.Channel1, PUMP_PIN_1), Channel(AllSettings.Channel2, PUMP_PIN_2) };