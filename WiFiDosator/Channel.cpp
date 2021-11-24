#include "Channel.h"
#include "GlobalConfigs.h"

Channel::Channel(ChannelSettings& channel)
        : Feeder(TimesProperty, &HermesIO, channel.Token, Settings.Serial)
        , Settings(channel)
        , Pin(MOTOR_PIN)
    {}


void Channel::processNextMessage()
{
    if (HermesIO.available() >= sizeof(aquabox::proto::Message)) {
      if(Feeder.processNextMessage()) {
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

Channel Channels[CHANNELS_COUNT] = { Channel(AllSettings.Channel1), Channel(AllSettings.Channel2) };