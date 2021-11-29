#ifndef UI_ROUTINE_H
#define UI_ROUTINE_H

#include "GlobalConfigs.h"
#include "Canvas.h"
#include "Menu.h"
#include <Adafruit_SSD1306.h>
#include <Scheduler.h>
#include <ESP8266WiFi.h>

enum class UIScreenId: uint8_t
{
    Default,
    NetworkSetup,
    FillInstructions,
    Filling,
    Calibrate,
    SavingSettings
};

class UIRoutine : public Task
{
public:
    UIRoutine();

    inline UIScreenId screenId() { return m_screens[m_screenIdx]; }
    inline void pushScreen(UIScreenId id) { m_screens[++m_screenIdx % SCREENS_HISTORY] = id; m_render = true; }
    inline void popScreen()
    {
        m_screens[m_screenIdx] == UIScreenId::Default;
        if(m_screenIdx == 0)
        {
          m_screenIdx = SCREENS_HISTORY;
        }
        --m_screenIdx;
        m_render = true;
    }
    inline void markDirty() { m_render = true; }
    inline bool shouldRun() { return Task::shouldRun() || m_render;  }
    void handleCommand(uint8_t& command) { currentMenu().commandHandler(command); }    
protected:
    Menu& currentMenu();
    inline virtual void setup() override;
    inline virtual void loop() override;
private:
    UIScreenId m_screens[SCREENS_HISTORY];
    bool m_render = true;
    uint8_t m_screenIdx = 0;
    DeviceState LastState = DeviceState::NotReady;
};

#endif // UI_ROUTINE
