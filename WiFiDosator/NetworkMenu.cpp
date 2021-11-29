#include "NetworkMenu.h"
#include "texts.h"
#include "Routines.h"
#include <ESP8266WiFi.h>

void drawNetworkMenu(Adafruit_SSD1306& display);
void handleNetworkMenuCommand(uint8_t& cmd);
void scanCompleted(int networksFound);



Menu networkMenu = {
  1, 0,
  drawNetworkMenu, handleNetworkMenuCommand,
  {
    TXT_SCAN_ID    
  }
};

void handleNetworkMenuCommand(uint8_t& cmd) {
  switch(cmd) {
    case MENU_UP: {
      uint8_t entriesCount = 1 + (WiFi.scanComplete() < 0 ? 0 : WiFi.scanComplete());
      networkMenu.selected = networkMenu.selected == 0 ? entriesCount - 1 : --networkMenu.selected;
      break;
    }
    case MENU_DOWN: {
      uint8_t entriesCount = 1 + (WiFi.scanComplete() < 0 ? 0 : WiFi.scanComplete());
      networkMenu.selected = ++networkMenu.selected % entriesCount;
      break;
    }
    case MENU_LEAVE: {
      UI.popScreen();
      break;
    }
    case MENU_ENTER: {
      if (networkMenu.selected == 0 && networkMenu.entries[0] == TXT_SCAN_ID) {
          WiFi.scanDelete();
          WiFi.mode(WIFI_STA);
          WiFi.disconnect();
          WiFi.scanNetworksAsync(scanCompleted);
          networkMenu.entries[0] == TXT_SCANNING_ID;
          UI.markDirty();
      }
    }
  }
  cmd = MENU_NOTHING;
}

void scanCompleted(int networksFound)
{
  networkMenu.entries[0] == TXT_SCAN_ID;
  networkMenu.selected = 0;
  UI.markDirty();
}

void drawNetworkMenu(Adafruit_SSD1306& display) {
  drawStatusBar(display);
  display.setTextWrap(false);
  
  if (WiFi.scanComplete() > 0) {

    uint8_t b = (networkMenu.selected / MAX_VISIBLE_MENU_ENTRIES) * MAX_VISIBLE_MENU_ENTRIES;
    uint8_t e = WiFi.scanComplete() + 1;
    if (b + MAX_VISIBLE_MENU_ENTRIES < e) {
      e = b + MAX_VISIBLE_MENU_ENTRIES;
    }
    
    for(uint8_t i = b; i < e; ++i) {
      if (i == 0) {
        if (networkMenu.selected == 0) {
          drawSelected(textById(TXT_SCAN_ID), display, 0);
        }
        else {
          drawNormal(textById(TXT_SCAN_ID), display, 0);
        }
      } else {
        if (networkMenu.selected == i) {
          drawSelected(WiFi.SSID(i - 1).c_str(), display, (i - b))
        }
        else {
          drawNormal(WiFi.SSID(i - 1).c_str(), display, (i - b))
        }
      }
    }
  } else {
    if (WiFi.scanComplete() == -1) {
      drawSelected(textById(TXT_SCANNING_ID), display, 0);
    }
    else {
      drawSelected(textById(TXT_SCAN_ID), display, 0);
    }
  }
}