#ifndef MENU_H
#define MENU_H

#include "GlobalConfigs.h"
#include <Adafruit_SSD1306.h>

void handleCommandDoNothing(uint8_t&);

struct Menu {
  uint8_t entriesCount = 0;
  uint8_t selected = 0;
  typedef void (*Renderer)(Adafruit_SSD1306&);
  typedef void (*CommandHanler)(uint8_t&);
  Renderer renderer = NULL;
  CommandHanler commandHandler = NULL;
  volatile uint8_t entries[];
};

extern void drawStatusBar(Adafruit_SSD1306& display);
extern void drawSimpleMenu(Adafruit_SSD1306& display, Menu* menu);

#ifndef drawSelected
#define drawSelected(text, display, line) { display . setCursor(6, 2 + 16 + (line) * 10); display . fillRoundRect(2, 16 + (line) * 10, display . width()- 4, 10, 4, WHITE); display . setTextColor(BLACK); display . println(text); }
#endif // drawSelected

#ifndef drawNormal
#define drawNormal(text, display, line) { display . setCursor(6, 2 + 16 + (line) * 10);  display . setTextColor(WHITE); display . println(text); }
#endif // drawNormal

#endif // MENU_H