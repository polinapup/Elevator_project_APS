#ifndef DEVICE_H
#define DEVICE_H

#include "Request.h"
#include <random>

class Device {
private:
    int deviceId;
    bool isBusy;
    Request* currentRequest;
    double serviceStartTime;
    double serviceCompletionTime;
    int currentTargetFloor;

    std::exponential_distribution<double> expDist;
    std::mt19937 generator;

public:
    Device(int id, double serviceRate = 1.0);
    ~Device();

    void startService(Request* request, double currentTime);
    void completeService();
    bool isAvailable() const;
    bool checkServiceCompletion(double currentTime);

    int getDeviceId() const;
    Request* getCurrentRequest() const;
    int getCurrentTargetFloor() const;
    double getServiceStartTime() const;
    double getRemainingTime(double currentTime) const;

    void displayState(double currentTime) const;
};

#endif