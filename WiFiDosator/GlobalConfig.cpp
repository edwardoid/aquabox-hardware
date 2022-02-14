#include "GlobalConfigs.h"

volatile DeviceState CurrentState = DeviceState::Starting;

void setState(const DeviceState& state)
{
    if (state == CurrentState) {
        return;
    }
    Serial.printf("Changing state to %d from %d\n", (int)state, (int)CurrentState );
    CurrentState = state;
}