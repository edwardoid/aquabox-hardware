#ifndef HERMES_IO_TASK_H
#define HERMES_IO_TASK_H

#include "GlobalConfigs.h"
#include <ESP8266WiFi.h>

class HermesIOTask : public Task {
public:
    HermesIOTask(int channelId);
    inline virtual bool shouldRun() override { return Task::shouldRun() && WiFi.status() == WL_CONNECTED;  }
protected:
    virtual void setup() override;
    virtual void loop() override;
private:
    int m_channelId;
    WiFiClient m_client;
};

#endif // HERMES_IO_TASK_H
