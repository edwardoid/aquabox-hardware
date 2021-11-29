#ifndef ROUTINES_H
#define ROUTINES_H

#include "GlobalConfigs.h"
#include "UIRoutine.h"
#include "TimesProperty.h"
#include "HermesStepper.h"
#include "HermesIOTask.h"
#include "DeviceRoutine.h"
#include "NetworkTask.h"
#include "Controls.h"

extern UIRoutine UI;
extern HermesIOTask IO0;
extern HermesIOTask IO1;
extern DeviceRoutine Routine0;
extern DeviceRoutine Routine1;
extern NetworkTask Networking;
extern ControlsMonitorTask Controls;


#endif // ROUTINES_H