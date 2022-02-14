#include "NetworkTask.h"


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "GlobalConfigs.h"
#include "Channel.h"
#include "Routines.h"

void NetworkTask::setup()
{
    CurrentState = DeviceState::Starting;
    WiFi.mode(WIFI_STA);
    WiFi.hostname("HermesDosator");

    CurrentState = DeviceState::ConnectingToNetwork;
}

bool NetworkTask::shouldRun()
{
    return CurrentState < DeviceState::ConnectingToAquabox && WiFi.status() != WL_CONNECTED && Task::shouldRun();
}

void NetworkTask::loop()
{
    UI.markDirty();
    WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
      UI.markDirty();
      yield();
    }

    Serial.print("Connected to ");
    Serial.println(WIFI_NETWORK);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    UI.markDirty();
    setState(DeviceState::ConnectingToAquabox);
}