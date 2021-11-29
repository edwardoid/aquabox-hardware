#ifndef CONTROLS_H
#define CONTROLS_H

#include <Scheduler.h>

#define MENU_NOTHING 0
#define MENU_UP 1
#define MENU_DOWN 2
#define MENU_ENTER 3
#define MENU_LEAVE 4

enum class ButtonState
{
    Idle = 0,
    Pressed,
    LongPressed
};

class ControlsMonitorTask: public Task
{
public:
    uint8_t LastKeyPress = MENU_NOTHING;
protected:
    virtual void setup() override;
    inline virtual void loop() override;
private:
};

#endif // CONTROLS_H