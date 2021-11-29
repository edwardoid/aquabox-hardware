#include "WelcomeMenu.h"
#include "Routines.h"
#include "texts.h"

void drawWelcomeMenu(Adafruit_SSD1306& display);
void handleWelcomeeMenuCommand(uint8_t& cmd);


Menu welcomeMenu = {
  5, 0,
  drawWelcomeMenu, handleWelcomeeMenuCommand,
  {
    TXT_DISPLAY_ID,
    TXT_NETWORK_ID,
    TXT_FILL_ID,
    TXT_CALIBRATE_ID,
    TXT_RESET_ID
  }
};

void handleWelcomeeMenuCommand(uint8_t& cmd)
{
  switch(cmd)
  {
    case MENU_UP: {
      welcomeMenu.selected = welcomeMenu.selected == 0 ? welcomeMenu.entriesCount - 1 : --welcomeMenu.selected;
      break;
    }
    case MENU_DOWN: {
      welcomeMenu.selected = ++welcomeMenu.selected % welcomeMenu.entriesCount;
      break;
    }
    case MENU_ENTER: {
      if (welcomeMenu.selected == 1) {
        UI.pushScreen(UIScreenId::NetworkSetup);
      } else if (welcomeMenu.selected == 2) {
        UI.pushScreen(UIScreenId::FillInstructions);
      } else if (welcomeMenu.selected == 3) {
        UI.pushScreen(UIScreenId::Calibrate);
      }
      break;
    }
    case MENU_LEAVE: {
      if (welcomeMenu.selected == 1) {
        welcomeMenu.selected = 0;
      }
      break;
    }
    default: {
    }
  }

  cmd = MENU_NOTHING;
}

void drawWelcomeMenu(Adafruit_SSD1306& display) {
  drawSimpleMenu(display, &welcomeMenu);
}