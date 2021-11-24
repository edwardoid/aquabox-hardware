#include "FillMenu.h"

#include "MenuNavigator.h"
#include "WelcomeMenu.h"
#include "texts.h"
#include "Canvas.h"
#include "Routines.h"

#define FILLING_NOT_STARTED 0
#define FILLING_IN_PROGRESS 1

uint8_t fillingState = FILLING_NOT_STARTED;

void drawFillMenu(Adafruit_SSD1306& display)
{
    display.setTextSize(1);
    display.setCursor(0, 20);
    display.setTextWrap(true);
    display.setTextColor(WHITE);
    switch(fillingState)
    {
      case FILLING_NOT_STARTED: {
        display.println(textById(TXT_FILL_NOTIFY_ID));
        break;
      }
      case FILLING_IN_PROGRESS: {
        display.println(textById(TXT_FILL_IN_PROGRESS_ID));
        break;
      }
      default: {
        display.println(textById(TXT_ERROR_RESTART_ID));
      }
    }
}


void handleFillMenuCommand(uint8_t& cmd) {
  switch(cmd) {
    case MENU_UP: {
      break;
    }
    case MENU_DOWN: {
      switch(fillingState)
      {
        case FILLING_NOT_STARTED: {
          fillingState = FILLING_IN_PROGRESS;
          break;
        }
        case FILLING_IN_PROGRESS: {
          fillingState = FILLING_NOT_STARTED;
          break;
        }
      }
      UI.markDirty();
      break;
    }
    case MENU_LEAVE: {
      if (fillingState == FILLING_NOT_STARTED) {
        CurrentMenu = &welcome;
        CurrentMenu->selected = 0;
      }
      break;
    }
  }
  cmd = MENU_NOTHING;
}

Menu fill = {
  0, 0,
  drawFillMenu, handleFillMenuCommand,
  {}
};