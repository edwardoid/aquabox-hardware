#include "UIRoutine.h"
#include "Canvas.h"
#include "Channel.h"
#include "WelcomeMenu.h"
#include "NetworkMenu.h"
#include "FillMenu.h"
#include "CalibrateMenu.h"

UIRoutine::UIRoutine()
  : m_screenIdx(0)
{
    for(uint8_t i = 0; i < SCREENS_HISTORY; ++i) {
      m_screens[i] = UIScreenId::Default;
    }
}

void UIRoutine::setup()
{
  Canvas.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Canvas.display();
}

Menu& UIRoutine::currentMenu()
{
  switch(m_screens[m_screenIdx])
  {
    case UIScreenId::FillInstructions:
    case UIScreenId::Filling:
    {
      return fillMenu;
    }
    case UIScreenId::NetworkSetup:
    {
      return networkMenu;
    }
    case UIScreenId::Calibrate:
    {
      return calibrateMenu;
    }
    case UIScreenId::Default:
    default: {
    }
  }
  return welcomeMenu;
}

void UIRoutine::loop()  {
  Serial.println(__FILE__);
  Canvas.clearDisplay(); // Clear display buffer

  currentMenu().renderer(Canvas);

  drawStatusBar(Canvas);

  Canvas.display();
  
  m_render = false;

  delay(UI_RENDER_WAIT_MS);
}
