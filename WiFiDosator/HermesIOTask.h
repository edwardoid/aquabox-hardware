#ifndef HERMES_IO_TASK_H
#define HERMES_IO_TASK_H

#include <Scheduler.h>

class HermesIOTask : public Task {
public:
    HermesIOTask(int channelId);
protected:
    virtual void setup() override;
    virtual void loop() override;
private:
    int m_channelId;
};

#endif // HERMES_IO_TASK_H
