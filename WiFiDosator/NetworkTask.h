#ifndef NETWORK_TASK_H
#define NETWORK_TASK_H

#include "GlobalConfigs.h"

class NetworkTask : public Task {
protected:
    virtual bool shouldRun() override;
    virtual void setup() override;
    virtual void loop() override;
};

#endif // NETWORK_TASK_H
