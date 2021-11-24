#ifndef CALIBRATOIN_TASK_H
#define CALIBRATOIN_TASK_H

#include <Scheduler.h>

class CalibrationTask: public Task
{
public:
  inline void setChannel(uint8_t channel) { m_channel = channel; };
protected:
  virtual void loop();
private:
  uint8_t m_channel;
  uint8_t m_calibrationStarted;
};

#endif // CALIBRATOIN_TASK_H