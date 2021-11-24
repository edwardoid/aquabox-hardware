#ifndef CHANNEL_H
#define CHANNEL_H

#include <AquaboxProto.h>
#include "HermesFeeder.h"
#include "TimesProperty.h"
#include "Settings.h"

#define CHANNELS_COUNT 2

enum class ChannelState
{
    FillRequested,
    Filling,
    Calibration
};

struct Channel
{
    Channel(ChannelSettings& channel);
    ChannelSettings& Settings;
    Times TimesProperty;
    aquabox::proto::ArduinoStreamIO HermesIO;
    HermesFeeder Feeder;
    uint8_t Pin;
    ChannelState State;
    void processNextMessage();
    uint32_t millilitersRemain() const;
};

extern Channel Channels[CHANNELS_COUNT];

#endif // CHANNEL_H