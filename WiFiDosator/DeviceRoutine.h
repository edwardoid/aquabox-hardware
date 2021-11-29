#ifndef DEVICE_ROUTINE_H
#define DEVICE_ROUTINE_H

#include <Scheduler.h>
#include "Channel.h"

class DeviceRoutine : public Task
{
  public:
    DeviceRoutine(uint8_t channel);
  protected:
    virtual void loop() override;
    inline virtual bool shouldRun() override { return Channels[m_channel].State == ChannelState::Idle && Task::shouldRun(); }
    inline Channel& channel() { return Channels[m_channel]; }
  private:
      uint8_t m_channel;
};


#endif // DEVICE_ROUTINE_H
