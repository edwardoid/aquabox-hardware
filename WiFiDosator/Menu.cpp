#include "Menu.h"
#include "texts.h"
#include <ESP8266WiFi.h>

Menu* CurrentMenu = NULL;

const char* States[] = {  "Idle", "Single", "Double",  "Triple", "Long" };

void drawStatusBar(Adafruit_SSD1306& display) {
  display.setTextColor(WHITE);
  display.setCursor(1, 1);
  display.setTextWrap(false);
  if (WiFi.status() == WL_CONNECTED) {
    if ((millis() / 1000) % 2)
      display.print(WiFi.localIP());
    else
      display.print(WiFi.SSID());
  }
  else
    display.print(textById(TXT_NO_WIFI_CONNECTION));
}

void drawSimpleMenu(Adafruit_SSD1306& display, Menu* menu) {
  uint8_t b = MAX_VISIBLE_MENU_ENTRIES * (menu->selected / MAX_VISIBLE_MENU_ENTRIES);
  uint8_t e = b + MAX_VISIBLE_MENU_ENTRIES > menu->entriesCount ? menu->entriesCount : (b + MAX_VISIBLE_MENU_ENTRIES);
  for(uint8_t i = b; i < e; ++i)
    {
        if (i == menu->selected)
        {
          drawSelected(textById(menu->entries[i]), display, (i - b));
        } else {
          drawNormal(textById(menu->entries[i]), display, (i - b));
        }
    }
}