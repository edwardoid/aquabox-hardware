#include "Controls.h"
#include "GlobalConfigs.h"
#include "MenuNavigator.h"


void ControlsMonitorTask::setup()
{
  
  Navigation.begin();
}


void ControlsMonitorTask::loop()
{
    
  Navigation.loop();
}