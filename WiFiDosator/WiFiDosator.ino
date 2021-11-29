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
    Serial.begin(115200);
    Settings.begin();
    Channels[0].Stepper.setSerial(AllSettings.Channel1.Serial);
    Channels[0].Stepper.setSerial(AllSettings.Channel1.Token);

    Channels[1].Stepper.setSerial(AllSettings.Channel2.Serial);
    Channels[1].Stepper.setSerial(AllSettings.Channel2.Token);
    CurrentState = DeviceState::Starting;
    //gdbstub_init();
    
    Settings.begin();
    Scheduler.start(&Routine0);
    Scheduler.start(&Routine1);
    Scheduler.start(&Networking);
    Scheduler.start(&IO0);
    Scheduler.start(&IO1);
    Scheduler.start(&Controls);
    Scheduler.start(&UI);
    
    Scheduler.begin();
}

// the loop function runs over and over again forever
void loop() {}
