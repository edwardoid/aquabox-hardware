#include "DeviceRoutine.h"
#include <HardwareSerial.h>
#include "GlobalConfigs.h"


DeviceRoutine::DeviceRoutine(uint8_t channel)
  : Task()
  , m_channel(channel)
{}

void DeviceRoutine::loop()  {

  if ((int) channel().TimesProperty.CurrentValue > 0)
  {
      DeviceState last = CurrentState;
      CurrentState = DeviceState::Working;
      double currentValue = double(channel().Settings.CalibrationDelay) / (CALIBRATION_PRECISION * 1000.);
      uint32_t EndAt = millis() + currentValue * channel().TimesProperty.CurrentValue;
      while(channel().TimesProperty.CurrentValue-- > 0)
      {
          digitalWrite(channel().Pin, HIGH);
          delay(channel().Settings.CalibrationDelay);
          channel().TimesProperty.update();
          yield();
          Serial.print(" -> ");
          Serial.println((int) channel().TimesProperty.CurrentValue);
      }
      channel().TimesProperty.CurrentValue = 0;
      digitalWrite(channel().Pin, LOW);
      channel().TimesProperty.update();
      CurrentState = last;
  }
}