#ifndef ROUTINES_H
#define ROUTINES_H

#include "GlobalConfigs.h"
#include "UIRoutine.h"
#include "TimesProperty.h"
#include "HermesFeeder.h"
#include "HermesIOTask.h"
#include "DeviceRoutine.h"
#include "NetworkTask.h"
#include "Controls.h"
#include "CalibrationTask.h"

extern UIRoutine UI;
extern HermesIOTask IO0;
extern HermesIOTask IO1;
extern DeviceRoutine Routine0;
extern DeviceRoutine Routine1;
extern NetworkTask Networking;
extern ControlsMonitorTask Controls;
extern CalibrationTask Calibration;


#endif // ROUTINES_H