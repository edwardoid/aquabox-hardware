#include "HermesIOTask.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "GlobalConfigs.h"
#include "Channel.h"

HermesIOTask::HermesIOTask(int channelId)
  : Task()
  , m_channelId(channelId)
{}

void HermesIOTask::setup()
{
    CurrentState = DeviceState::Starting;
    Serial.begin(115200);
    pinMode(D5, OUTPUT);
    WiFi.mode(WIFI_STA);
    CurrentState = DeviceState::ConnectingToNetwork;
    WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);
    WiFi.hostname("HermesDoser");
}

void HermesIOTask::loop()
{
    while(WiFi.status() != WL_CONNECTED) {
      yield();
    }
    WiFiClient client;
    CurrentState = DeviceState::ConnectingToAquabox;
    //yield();
    while(!client.connect(AQUABOX_IP, AQUABOX_PORT)) {
        delay(1000);
        
        CurrentState = DeviceState::ConnectionToAquaboxLost;
        yield();
    }
    Channels[m_channelId].HermesIO.init(&client);
    if(!Channels[m_channelId].Feeder.handshake()) {
      CurrentState = DeviceState::HandshakeFailed;
    }

    CurrentState = DeviceState::Idle;
    while(client.connected()) {
      Channels[m_channelId].processNextMessage();
    }

    client.stop();
}