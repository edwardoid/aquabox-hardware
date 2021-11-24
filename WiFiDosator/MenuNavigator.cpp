#include "MenuNavigator.h"
#include "Menu.h"
#include "Routines.h"
#include "Button.h"
#include "Canvas.h"

MenuNavigation Navigation;

GestureHandler up(D6), down(D7);

uint8_t cmd = MENU_NOTHING;

void handler(uint8_t pin, uint8_t gesture)
{
    if (cmd != MENU_NOTHING) {
      return;
    }
    if (gesture == GESTURE_SINGLE) {
      if (pin == D6) cmd = MENU_DOWN;
      if (pin == D7) cmd = MENU_UP;
    } else if (gesture == GESTURE_DOUBLE) {
      if (pin == D6) cmd = MENU_ENTER;
      if (pin == D7) cmd = MENU_LEAVE;
    }
}


void MenuNavigation::begin()
{
  up.begin();
  up.setHandler(handler);
  down.begin();
  down.setHandler(handler);
}

void MenuNavigation::loop()
{
  up.loop();
  down.loop();

  if (cmd != MENU_NOTHING) {
    CurrentMenu->commandHandler(cmd);
    UI.markDirty();
  }
}