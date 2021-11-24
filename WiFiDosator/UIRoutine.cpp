#include "UIRoutine.h"
#include "Canvas.h"
#include "Channel.h"
#include "WelcomeMenu.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


UIRoutine::UIRoutine()
  : m_screenIdx(0)
{
    for(uint8_t i = 0; i < SCREENS_HISTORY; ++i) {
      m_screens[i] = UIScreenId::Default;
    }
}

void UIRoutine::setup()
{
  CurrentMenu = &welcome;
  Canvas.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}
void UIRoutine::loop()  {
  static unsigned long  fps = millis();
  if (m_render || millis() - fps > 200) {
    m_render = false; 
    Canvas.clearDisplay(); // Clear display buffer
    
    CurrentMenu->renderer(Canvas);

    drawStatusBar(Canvas);

    Canvas.display();
    fps = millis();
  } else {
    yield();
  }
}
