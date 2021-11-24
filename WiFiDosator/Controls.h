#ifndef CONTROLS_H
#define CONTROLS_H

#include <Scheduler.h>
#include <Button2.h>

enum class ButtonState
{
    Idle = 0,
    Pressed,
    LongPressed
};

class ControlsMonitorTask: public Task
{
protected:
    virtual void setup() override;
    inline virtual void loop() override;
private:
};

#endif // CONTROLS_H