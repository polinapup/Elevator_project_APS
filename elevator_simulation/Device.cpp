#include "Device.h"
#include <iostream>
#include <cmath>

Device::Device(int id, double serviceRate)
    : deviceId(id), isBusy(false), currentRequest(nullptr),
    serviceStartTime(0), serviceCompletionTime(0), currentTargetFloor(-1),
    expDist(serviceRate), generator(std::random_device{}()) {
}

Device::~Device() {
}

void Device::startService(Request* request, double currentTime) {
    currentRequest = request;
    currentTargetFloor = request->getTargetFloor();
    isBusy = true;
    serviceStartTime = currentTime;

    double serviceTime = expDist(generator);
    serviceCompletionTime = currentTime + serviceTime;

    std::cout << "Лифт " << deviceId << " начал движение на этаж "
        << currentTargetFloor << ". Время обслуживания: "
        << serviceTime << std::endl;
}

void Device::completeService() {
    isBusy = false;
    currentRequest = nullptr;
    currentTargetFloor = -1;
}

bool Device::isAvailable() const {
    return !isBusy;
}

bool Device::checkServiceCompletion(double currentTime) {
    return isBusy && currentTime >= serviceCompletionTime;
}

int Device::getDeviceId() const { return deviceId; }
Request* Device::getCurrentRequest() const { return currentRequest; }
int Device::getCurrentTargetFloor() const { return currentTargetFloor; }
double Device::getServiceStartTime() const { return serviceStartTime; }

double Device::getRemainingTime(double currentTime) const {
    if (!isBusy) return 0;
    return std::max(0.0, serviceCompletionTime - currentTime);
}

void Device::displayState(double currentTime) const {
    std::cout << "Лифт " << deviceId << ": ";
    if (isBusy) {
        std::cout << "едет на этаж " << currentTargetFloor
            << " (осталось: " << getRemainingTime(currentTime) << ")";
    }
    else {
        std::cout << "свободен";
    }
    std::cout << std::endl;
}