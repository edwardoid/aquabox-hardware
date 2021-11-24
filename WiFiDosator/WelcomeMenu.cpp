#include "WelcomeMenu.h"
#include "NetworkMenu.h"
#include "MenuNavigator.h"
#include "FillMenu.h"
#include "texts.h"

void drawWelcomeMenu(Adafruit_SSD1306& display);

namespace {
void handleCommand(uint8_t& cmd)
{
  switch(cmd)
  {
    case MENU_UP: {
      CurrentMenu->selected = CurrentMenu->selected == 0 ? CurrentMenu->entriesCount - 1 : --CurrentMenu->selected;
      break;
    }
    case MENU_DOWN: {
      CurrentMenu->selected = ++CurrentMenu->selected % CurrentMenu->entriesCount;
      break;
    }
    case MENU_ENTER: {
      if (CurrentMenu->selected == 1) {
        CurrentMenu = &network;
        CurrentMenu->selected = 0;
      } else if(CurrentMenu->selected == 2) {
        CurrentMenu = &fill;
      }
      break;
    }
    case MENU_LEAVE: {
      if (CurrentMenu->selected == 1) {
        CurrentMenu = &welcome;
        CurrentMenu->selected = 0;
      }
      break;
    }
    default: {
    }
  }

  cmd = MENU_NOTHING;
}
}

Menu welcome = {
  5, 0,
  drawWelcomeMenu, handleCommand,
  {
    TXT_DISPLAY_ID,
    TXT_NETWORK_ID,
    TXT_FILL_ID,
    TXT_CALIBRATE_ID,
    TXT_RESET_ID
  }
};

void drawWelcomeMenu(Adafruit_SSD1306& display) {
  drawSimpleMenu(display, &welcome);
}