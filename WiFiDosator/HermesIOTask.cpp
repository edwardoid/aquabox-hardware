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

    m_client.setTimeout(50);
}

void HermesIOTask::setup()
{
    CurrentState = DeviceState::ConnectingToNetwork;
}

void HermesIOTask::loop()
{
    CurrentState = DeviceState::ConnectingToAquabox;
    if (!m_client.connected()) {
      Serial.println(AQUABOX_IP);
      while(!m_client.connect(AQUABOX_IP, AQUABOX_PORT)) {
        CurrentState = DeviceState::ConnectionToAquaboxLost;
        delay(100);
      }
    }
    
    while(!Channels[m_channelId].Stepper.handshake()) {
      Serial.println("Handshake failed!");
      CurrentState = DeviceState::HandshakeFailed;
    }

    CurrentState = DeviceState::Idle;
    while(m_client.connected()) {
      if (m_client.available() >= sizeof(aquabox::proto::Message)) {
        Channels[m_channelId].processNextMessage();
        Serial.println("Processing incoming hermes message");
      } else {
        delay(100);
      }
    }
}