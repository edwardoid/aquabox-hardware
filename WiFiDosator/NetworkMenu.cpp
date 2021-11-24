#include "NetworkMenu.h"
#include "WelcomeMenu.h"
#include "MenuNavigator.h"
#include "texts.h"
#include "Routines.h"
#include <ESP8266WiFi.h>

void drawNetworkMenu(Adafruit_SSD1306& display);

void scanCompleted(int networksFound);

void handleCommand(uint8_t& cmd) {
  switch(cmd) {
    case MENU_UP: {
      uint8_t entriesCount = 1 + (WiFi.scanComplete() < 0 ? 0 : WiFi.scanComplete());
      network.selected = network.selected == 0 ? entriesCount - 1 : --network.selected;
      break;
    }
    case MENU_DOWN: {
      uint8_t entriesCount = 1 + (WiFi.scanComplete() < 0 ? 0 : WiFi.scanComplete());
      network.selected = ++network.selected % entriesCount;
      break;
    }
    case MENU_LEAVE: {
      CurrentMenu = &welcome;
      CurrentMenu->selected = 0;
      break;
    }
    case MENU_ENTER: {
      if (network.selected == 0 && network.entries[0] == TXT_SCAN_ID) {
          WiFi.scanDelete();
          WiFi.mode(WIFI_STA);
          WiFi.disconnect();
          WiFi.scanNetworksAsync(scanCompleted);
          network.entries[0] == TXT_SCANNING_ID;
          UI.markDirty();
      }
    }
  }
  cmd = MENU_NOTHING;
}

Menu network = {
  1, 0,
  drawNetworkMenu, handleCommand,
  {
    TXT_SCAN_ID    
  }
};

void scanCompleted(int networksFound)
{
  network.entries[0] == TXT_SCAN_ID;
  network.selected = 0;
  UI.markDirty();
}

void drawNetworkMenu(Adafruit_SSD1306& display) {
  drawStatusBar(display);
  display.setTextWrap(false);
  
  if (WiFi.scanComplete() > 0) {

    uint8_t b = (network.selected / MAX_VISIBLE_MENU_ENTRIES) * MAX_VISIBLE_MENU_ENTRIES;
    uint8_t e = WiFi.scanComplete() + 1;
    if (b + MAX_VISIBLE_MENU_ENTRIES < e) {
      e = b + MAX_VISIBLE_MENU_ENTRIES;
    }
    
    for(uint8_t i = b; i < e; ++i) {
      if (i == 0) {
        if (network.selected == 0) {
          drawSelected(textById(TXT_SCAN_ID), display, 0);
        }
        else {
          drawNormal(textById(TXT_SCAN_ID), display, 0);
        }
      } else {
        if (network.selected == i) {
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