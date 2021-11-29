#include "SelectChannelMenu.h"
#include "texts.h"
#include "Canvas.h"
#include "Routines.h"

#define FILLING_NOT_STARTED 0
#define FILLING_IN_PROGRESS 1


void drawSelectChannelMenu(Adafruit_SSD1306& display)
{

}


void handleSelectChannelMenuCommand(uint8_t& cmd) {
  Controls.LastKeyPress = MENU_NOTHING;
}

Menu selectChannelMenu = {
  2, 0,
  drawSelectChannelMenu, handleSelectChannelMenuCommand,
  {
    TXT_CHANNEL_1_ID,
    TXT_CHANNEL_2_ID
  }
};