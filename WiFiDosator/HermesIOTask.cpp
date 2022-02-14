#include "HermesIOTask.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "GlobalConfigs.h"
#include "Channel.h"

HermesIOTask::HermesIOTask(int channelId)
  : Task()
  , m_channelId(channelId)
{
    Channels[m_channelId].HermesIO.init(&m_client);
    Channels[m_channelId].HermesIO.setPollTimeout(1000);

    //m_client.setTimeout(2000);
}

void HermesIOTask::setup()
{
    setState(DeviceState::ConnectingToNetwork);
}

void HermesIOTask::loop()
{
    while(!m_client.connect(AQUABOX_IP, AQUABOX_PORT)) {
      long long end = millis() + 100;
      do {
        delay(100);
      } while(millis() < end && !m_client.connected());
    }

    Serial.printf("Channel %d handshaking...\n", m_channelId);
     
    if(!Channels[m_channelId].Stepper.handshake()) {
      m_client.flush();
      return;
    }

    Serial.printf("Channel %d operating...\n", m_channelId);

    while(m_client.connected()) {
      if (m_client.available() >= sizeof(aquabox::proto::Message)) {
        int32_t curr = Channels[m_channelId].TimesProperty.value;
        Channels[m_channelId].processNextMessage();
//        if (curr != Channels[m_channelId].TimesProperty.value) {
//          Channels[m_channelId].State = ChannelState::Idle;
//        }
        //Serial.printf("Processing incoming hermes message on channel %d\n", m_channelId);
      } else {
        yield();
      }
    }
    Serial.printf("Channel %d died!\n", m_channelId);
    m_client.flush();
}