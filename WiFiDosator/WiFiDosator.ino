
#include <Arduino.h>
#include <HardwareSerial.h>
#include "GlobalConfigs.h"
#include "Routines.h"
#include <Scheduler.h>
#include <AquaboxProto.h>
#include "Settings.h"
//#include <GDBStub.h>

void setup()
{
    CurrentState = DeviceState::Starting;
    Serial.begin(115200);
    //gdbstub_init();
    
    Settings.begin();
    Scheduler.start(&Routine0);
    Scheduler.start(&Routine1);
    Scheduler.start(&Networking);
    Scheduler.start(&IO0);
    Scheduler.start(&IO1);
    Scheduler.start(&Controls);
    Scheduler.start(&Calibration);
    Scheduler.start(&UI);
    
    Scheduler.begin();
}

// the loop function runs over and over again forever
void loop() {}
