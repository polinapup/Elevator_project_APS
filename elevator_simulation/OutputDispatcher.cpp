#include "OutputDispatcher.h"
#include <iostream>

OutputDispatcher::OutputDispatcher(Buffer* buffer)
    : buffer(buffer) {
}

void OutputDispatcher::addDevice(Device* device) {
    devices.push_back(device);
}

void OutputDispatcher::checkForService(double currentTime) {
    //Ищем свободный прибор
    Device* freeDevice = applyDeviceSelection();
    if (freeDevice == nullptr) return;

    //Ищем заявку для обработки
    Request* nextRequest = applyBufferSelection();
    if (nextRequest == nullptr) return;

    //Начало обслуживания
    startService(freeDevice, nextRequest, currentTime);
}

Request* OutputDispatcher::applyBufferSelection() {
    Request* request = buffer->getNextRequest();
    if (request) {
        std::cout << "ВЗЯТА ЗАЯВКА: " << request->toString() << " из буфера" << std::endl;
    }
    return request;
}

Device* OutputDispatcher::applyDeviceSelection() {
    for (auto device : devices) {
        if (device->isAvailable()) {
            return device;
        }
    }
    return nullptr;
}

void OutputDispatcher::startService(Device* device, Request* request, double currentTime) {
    device->startService(request, currentTime);
    std::cout << "ОБСЛУЖИВАНИЕ: " << request->toString()
        << " назначена на лифт " << device->getDeviceId() << std::endl;
}

void OutputDispatcher::displayState(double currentTime) const {
    std::cout << "  Состояние системы обслуживания" << std::endl;
    for (auto device : devices) {
        device->displayState(currentTime);
    }
    std::cout << "Заявок в буфере: " << buffer->getSize() << "/" << buffer->capacity << std::endl;
}