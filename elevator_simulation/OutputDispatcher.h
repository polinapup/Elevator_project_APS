#ifndef OUTPUTDISPATCHER_H
#define OUTPUTDISPATCHER_H

#include "Buffer.h"
#include "Device.h"
#include <vector>

class OutputDispatcher {
private:
    Buffer* buffer;
    std::vector<Device*> devices;

public:
    OutputDispatcher(Buffer* buffer);

    void addDevice(Device* device);
    void checkForService(double currentTime);

    Request* applyBufferSelection(); // 򰮻
    Device* applyDeviceSelection(); // 򰱆

    void startService(Device* device, Request* request, double currentTime);

    void displayState(double currentTime) const;
};

#endif
