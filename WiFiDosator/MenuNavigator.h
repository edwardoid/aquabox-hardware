#ifndef MENU_NAVIGATION_H
#define MENU_NAVIGATION_H

#include <Arduino.h>

#define MENU_NOTHING 0
#define MENU_UP 1
#define MENU_DOWN 2
#define MENU_ENTER 3
#define MENU_LEAVE 4

class MenuNavigation
{
public:
  void begin();
  void loop();
};

extern MenuNavigation Navigation;

#endif // MENU_NAVIGATION_H