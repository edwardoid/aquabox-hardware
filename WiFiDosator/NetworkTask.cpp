#include "NetworkTask.h"


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "GlobalConfigs.h"
#include "Channel.h"
#include "Routines.h"

void NetworkTask::setup()
{
    CurrentState = DeviceState::Starting;
    pinMode(D5, OUTPUT);
    WiFi.mode(WIFI_STA);
    WiFi.hostname("HermesFeeder");

    CurrentState = DeviceState::ConnectingToNetwork;
}

bool NetworkTask::shouldRun()
{
    return CurrentState < DeviceState::ConnectingToAquabox && Task::shouldRun();
}

void NetworkTask::loop()
{
    if(WiFi.status() != WL_CONNECTED) {
      UI.markDirty();
      WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

      Serial.println("Connecting to WiFi");
      int it = 0;
      while (WiFi.status() != WL_CONNECTED)
      {
          yield();
      }

      Serial.println("");
      Serial.print("Connected to ");
      Serial.println(WIFI_NETWORK);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      UI.markDirty();
      CurrentState = DeviceState::ConnectingToAquabox;
    }
}