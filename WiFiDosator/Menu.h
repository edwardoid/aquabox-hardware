#ifndef MENU_H
#define MENU_H

#include <Adafruit_SSD1306.h>

struct Menu {
  uint8_t entriesCount;
  uint8_t selected;
  typedef void (*Renderer)(Adafruit_SSD1306&);
  typedef void (*CommandHanler)(uint8_t&);
  Renderer renderer;
  CommandHanler commandHandler;
  volatile uint8_t entries[];
};

#define MAX_VISIBLE_MENU_ENTRIES 4

extern void drawStatusBar(Adafruit_SSD1306& display);
extern void drawSimpleMenu(Adafruit_SSD1306& display, Menu* menu);

#ifndef drawSelected
#define drawSelected(text, display, line) { display . setCursor(6, 2 + 16 + (line) * 10); display . fillRoundRect(2, 16 + (line) * 10, display . width()- 4, 10, 4, WHITE); display . setTextColor(BLACK); display . println(text); }
#endif // drawSelected

#ifndef drawNormal
#define drawNormal(text, display, line) { display . setCursor(6, 2 + 16 + (line) * 10);  display . setTextColor(WHITE); display . println(text); }
#endif // drawNormal

extern Menu* CurrentMenu;

#endif // MENU_H