#include "Controls.h"
#include "GlobalConfigs.h"
#include "Button.h"
#include "Routines.h"

GestureHandler up(UP_BUTTON_PIN), middle(MIDDLE_BUTTON_MIN), down(DOWN_BUTTON_PIN);

void buttonHandler(uint8_t pin, uint8_t gesture)
{
  Serial.println("Gesture detected");
    if (Controls.LastKeyPress != MENU_NOTHING) {
      return;
    }
    if (gesture == GESTURE_SINGLE) {
      if (pin == DOWN_BUTTON_PIN) Controls.LastKeyPress = MENU_DOWN;
      if (pin == UP_BUTTON_PIN) Controls.LastKeyPress = MENU_UP;
    } else if (gesture == GESTURE_DOUBLE) {
      if (pin == DOWN_BUTTON_PIN) Controls.LastKeyPress = MENU_ENTER;
      if (pin == UP_BUTTON_PIN) Controls.LastKeyPress = MENU_LEAVE;
    }
}


void ControlsMonitorTask::setup()
{
  up.begin();
  up.setHandler(buttonHandler);
  down.begin();
  down.setHandler(buttonHandler);
  middle.begin();
  middle.setHandler(buttonHandler);
}


void ControlsMonitorTask::loop()
{
  //Serial.println(__FILE__);
  up.loop();
  middle.loop();
  down.loop();

  if (LastKeyPress != MENU_NOTHING) {
    UI.handleCommand(LastKeyPress);
    UI.markDirty();
  }
}