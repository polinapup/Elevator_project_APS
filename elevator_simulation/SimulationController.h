#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H

#include "Source.h"
#include "InputDispatcher.h"
#include "OutputDispatcher.h"
#include "Device.h"
#include "Event.h"
#include <vector>
#include <queue>

class SimulationController {
private:
    Source* source;
    InputDispatcher* inputDispatcher;
    OutputDispatcher* outputDispatcher;
    std::vector<Device*> devices;
    Buffer* buffer;

    double currentTime;
    bool stepByStepMode;
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> eventCalendar;
    int totalProcessedRequests;
    double totalServiceTime;
    double totalWaitingTime;

public:
    SimulationController(int bufferCapacity, int numDevices);
    ~SimulationController();

    void runStepByStep();
    void displaySystemState();
    void displayStatistics();
    void displayEventCalendar();

private:
    void generateInitialEvents();
    void processRequestGeneration();
    void processServiceCompletion(Device* device);
};

#endif
