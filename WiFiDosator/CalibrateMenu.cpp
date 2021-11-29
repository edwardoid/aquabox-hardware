#include "CalibrateMenu.h"

#include "texts.h"
#include "Canvas.h"
#include "Routines.h"

#define CALIBRATE_NOT_STARTED 1
#define CHANNEL_SELECTED 2
#define CALIBRATE_IN_PROGRESS 3
#define CALIBRATE_SAVE 4

void drawCalibrateMenu(Adafruit_SSD1306& display);
void handleCalibrateMenuCommand(uint8_t& cmd);

Menu calibrateMenu = {
  2, 0,
  drawCalibrateMenu, handleCalibrateMenuCommand,
  {}
};

uint8_t calibrateState = CALIBRATE_NOT_STARTED;

void drawCalibrateMenu(Adafruit_SSD1306& display)
{
    display.setTextSize(1);
    display.setCursor(0, 30);
    display.setTextWrap(true);
    display.setTextColor(WHITE);
    switch(calibrateState)
    {
      case CALIBRATE_NOT_STARTED: {
        drawNormal(textById(TXT_SELECT_CHANNEL_ID), Canvas, 0);
        if (calibrateMenu.selected == 0) {
          drawSelected(textById(TXT_CHANNEL_1_ID), Canvas, 1);
        } else {
          drawNormal(textById(TXT_CHANNEL_1_ID), Canvas, 1);
        }

        if (calibrateMenu.selected == 1) {
          drawSelected(textById(TXT_CHANNEL_2_ID), Canvas, 2);
        } else {
          drawNormal(textById(TXT_CHANNEL_2_ID), Canvas, 2);
        }
        break;
      }
      case CHANNEL_SELECTED: {
        display.println(textById(TXT_CALIBRATE_NOTIFY_5ML_ID));
        break;
      }
      case CALIBRATE_IN_PROGRESS: {
        display.println(textById(TXT_CALIBRATE_IN_PROGRESS_ID));
        break;
      }
      case CALIBRATE_SAVE: {
        double currentValue = double(Channels[calibrateMenu.selected].Settings.CalibrationDelay) / (CALIBRATION_PRECISION * 1000.);
        double newValue = double(Channels[calibrateMenu.selected].isOnFor()) / (CALIBRATION_PRECISION * 1000.);
        display.setCursor(0, 17);
        display.printf(TXT_SAVE_CALIBRATION_RESULT_QUESTION_FMT, calibrateMenu.selected + 1, currentValue, newValue);
        break;
      }
      default: {
        display.println(textById(TXT_ERROR_RESTART_ID));
      }
    }
}


void handleCalibrateMenuCommand(uint8_t& cmd) {
  switch(calibrateState)
  {
    case CALIBRATE_NOT_STARTED: {
      if (cmd == MENU_UP || cmd == MENU_DOWN) {
        calibrateMenu.selected = ++ calibrateMenu.selected % 2;
      } else if (cmd == MENU_ENTER) {
        calibrateState = CHANNEL_SELECTED;
      } else if (cmd == MENU_LEAVE) {
        calibrateMenu.selected = 0;
        UI.popScreen();

        Channels[0].State = ChannelState::Idle;
        Channels[1].State = ChannelState::Idle;
      }
      UI.markDirty();
      break;
    }
    case CHANNEL_SELECTED: {
      if (cmd == MENU_DOWN) {
        calibrateState = CALIBRATE_IN_PROGRESS;
        Channels[calibrateMenu.selected].State = ChannelState::Calibration;
        Channels[calibrateMenu.selected].set(true);
      } else if (cmd == MENU_LEAVE) {
        calibrateState = CALIBRATE_NOT_STARTED;
        Channels[calibrateMenu.selected].set(false);
        Channels[calibrateMenu.selected].State = ChannelState::Idle;
      }
      UI.markDirty();
      break;
    }
    case CALIBRATE_IN_PROGRESS: {
      if (cmd == MENU_DOWN) {
        Channels[calibrateMenu.selected].set(false);
        calibrateState = CALIBRATE_SAVE;
        UI.markDirty();
      }
      break;
    }
    case CALIBRATE_SAVE: {
      if (cmd == MENU_DOWN) {
        Channels[calibrateMenu.selected].Settings.CalibrationDelay = Channels[calibrateMenu.selected].isOnFor();
        Settings.write();
        calibrateMenu.selected = 0;
        calibrateState = CALIBRATE_NOT_STARTED;
        Channels[calibrateMenu.selected].State = ChannelState::Idle;
        UI.popScreen();
      } else if (cmd == MENU_UP) {
        calibrateState = CHANNEL_SELECTED;
      } else if (cmd == MENU_LEAVE) {
        calibrateState = CALIBRATE_NOT_STARTED;
        calibrateMenu.selected = 0;
        UI.popScreen();
      }
    }
  }

  cmd = MENU_NOTHING;
}