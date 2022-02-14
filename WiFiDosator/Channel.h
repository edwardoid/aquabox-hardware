#ifndef CHANNEL_H
#define CHANNEL_H

#include <AquaboxProto.h>
#include "HermesStepper.h"
#include "TimesProperty.h"
#include "Settings.h"
#include "GlobalConfigs.h"


enum class ChannelState
{
    Idle,
    FillRequested,
    Filling,
    Calibration
};

struct Channel
{
    Channel(ChannelSettings& channel, uint8_t pin);
    ChannelSettings& Settings;
    Times TimesProperty;
    aquabox::proto::ArduinoStreamIO HermesIO;
    HermesStepper Stepper;
    uint8_t Pin;
    ChannelState State;
    inline void set(bool on) { digitalWrite(Pin, on ? HIGH : LOW); if (on) { channelStartedOn = millis(); } else { channelStoppedOn = millis();} }
    inline unsigned long isOnFor() {  return channelStoppedOn - channelStartedOn; }
    unsigned long channelStartedOn = 0;
    unsigned long channelStoppedOn = 0;
    void processNextMessage();
    uint32_t millilitersRemain() const;
};

extern Channel Channels[CHANNELS_COUNT];

#endif // CHANNEL_H