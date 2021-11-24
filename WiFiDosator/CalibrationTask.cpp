#include "CalibrationTask.h"
#include "Channel.h"
#include "Routines.h"
#include "Settings.h"
#include "GlobalConfigs.h"

void CalibrationTask::loop()
{
  /*
    if (Channels[m_channel].State == ChannelState::FillRequested && Controls.upState() == ButtonState::LongPressed && Controls.downState() == ButtonState::LongPressed)
    {
      UI.pushScreen(UIScreenId::Filling);
      Channels[m_channel].State == ChannelState::Filling;
    }
    else if(Channels[m_channel].State == ChannelState::Filling)
    {
      if (Controls.upState() == ButtonState::LongPressed && Controls.downState() == ButtonState::LongPressed)
          digitalWrite(Channels[m_channel].Pin, HIGH);
      else {
          digitalWrite(Channels[m_channel].Pin, LOW);
          UI.popScreen();
      }
    }
    else if (Channels[m_channel].State == ChannelState::Calibration)
    {
      if (Controls.upState() == ButtonState::LongPressed && Controls.downState() == ButtonState::LongPressed) {
          if (m_calibrationStarted == 0) {
            UI.pushScreen(UIScreenId::Calibrating);
            m_calibrationStarted = millis();
            digitalWrite(Channels[m_channel].Pin, HIGH);
          }
      }
      else {
          Channels[m_channel].Settings.CalibrationDelay = max<unsigned long>((millis() - m_calibrationStarted) / CALIBRATION_PRECISION, 1UL);
          Settings.write();
          m_calibrationStarted = 0;
          digitalWrite(Channels[m_channel].Pin, LOW);
          UI.popScreen();
      }
    }
    */
}