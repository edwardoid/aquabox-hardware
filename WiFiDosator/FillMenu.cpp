#include "FillMenu.h"

#include "texts.h"
#include "Canvas.h"
#include "Routines.h"

#define FILLING_NOT_STARTED 1
#define CHANNEL_SELECTED 2
#define FILLING_IN_PROGRESS 3

void drawFillMenu(Adafruit_SSD1306& display);
void handleFillMenuCommand(uint8_t& cmd);

Menu fillMenu = {
  2, 0,
  drawFillMenu, handleFillMenuCommand,
  {}
};

uint8_t fillingState = FILLING_NOT_STARTED;

void drawFillMenu(Adafruit_SSD1306& display)
{
    display.setTextSize(1);
    display.setCursor(0, 30);
    display.setTextWrap(true);
    display.setTextColor(WHITE);
    switch(fillingState)
    {
      case FILLING_NOT_STARTED: {
        drawNormal(textById(TXT_SELECT_CHANNEL_ID), Canvas, 0);
        if (fillMenu.selected == 0) {
          drawSelected(textById(TXT_CHANNEL_1_ID), Canvas, 1);
        } else {
          drawNormal(textById(TXT_CHANNEL_1_ID), Canvas, 1);
        }

        if (fillMenu.selected == 1) {
          drawSelected(textById(TXT_CHANNEL_2_ID), Canvas, 2);
        } else {
          drawNormal(textById(TXT_CHANNEL_2_ID), Canvas, 2);
        }
        break;
      }
      case CHANNEL_SELECTED: {
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
  switch(fillingState)
  {
    case FILLING_NOT_STARTED: {
      if (cmd == MENU_UP || cmd == MENU_DOWN) {
        fillMenu.selected = ++ fillMenu.selected % 2;  
      } else if (cmd == MENU_ENTER) {
        fillingState = CHANNEL_SELECTED;
      } else if (cmd == MENU_LEAVE) {
        UI.popScreen();
        fillMenu.selected = 0;
        Channels[0].State = ChannelState::Idle;
        Channels[1].State = ChannelState::Idle;
      }
      UI.markDirty();
      break;
    }
    case CHANNEL_SELECTED: {
      if (cmd == MENU_DOWN) {
        fillingState = FILLING_IN_PROGRESS;
      } else if (cmd == MENU_LEAVE) {
        fillingState = FILLING_NOT_STARTED;
      }
      Channels[fillMenu.selected].State = (fillingState == FILLING_IN_PROGRESS ) ? ChannelState::Filling : ChannelState::FillRequested;
      Channels[fillMenu.selected].set(fillingState == FILLING_IN_PROGRESS);
      
      UI.markDirty();
      break;
    }
    case FILLING_IN_PROGRESS: {
      if (cmd == MENU_DOWN) {
        fillingState = CHANNEL_SELECTED;
        Channels[fillMenu.selected].State = ChannelState::FillRequested;
        Channels[fillMenu.selected].set(false);
        UI.markDirty();
      }
      break;
    }
  }

  cmd = MENU_NOTHING;
}