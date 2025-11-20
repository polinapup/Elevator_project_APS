#include "SimulationController.h"
#include <iostream>
#include <iomanip>
#include <random>

SimulationController::SimulationController(int bufferCapacity, int numDevices)
    : currentTime(0), stepByStepMode(true), totalProcessedRequests(0),
    totalServiceTime(0), totalWaitingTime(0) {

    buffer = new Buffer(bufferCapacity);
    source = new Source(10, 0.5);
    inputDispatcher = new InputDispatcher(buffer);
    outputDispatcher = new OutputDispatcher(buffer);

    for (int i = 0; i < numDevices; i++) {
        Device* device = new Device(i + 1, 1.0);
        devices.push_back(device);
        outputDispatcher->addDevice(device);
    }

    generateInitialEvents();
}


SimulationController::~SimulationController() {
    delete source;
    delete inputDispatcher;
    delete outputDispatcher;
    delete buffer;
    for (auto device : devices) {
        delete device;
    }
}

void SimulationController::runStepByStep() {
    stepByStepMode = true;

    std::cout << "\n    ПОШАГОВЫЙ РЕЖИМ" << std::endl;

    int step = 0;
    while (!eventCalendar.empty() && step < 50) {
        std::cout << "\n--- Шаг " << ++step << " ---" << std::endl;
        std::cout << "Текущее время: " << currentTime << std::endl;

        displaySystemState();
        displayEventCalendar();

        Event nextEvent = eventCalendar.top();
        eventCalendar.pop();
        currentTime = nextEvent.time;

        std::cout << "ОБРАБОТКА: " << nextEvent.getTypeString()
            << " во время " << currentTime << std::endl;

        if (nextEvent.action) {
            nextEvent.action();
        }

        for (auto device : devices) {
            if (device->checkServiceCompletion(currentTime)) {
                processServiceCompletion(device);
            }
        }

        outputDispatcher->checkForService(currentTime);

        std::cout << "Enter чтобы перейти на следующий шаг";
        std::cin.get();
    }

    displayStatistics();
}

void SimulationController::displaySystemState() {
    std::cout << "\n    СОСТОЯНИЕ СИСТЕМЫ" << std::endl;

    buffer->displayState();

    outputDispatcher->displayState(currentTime);

    inputDispatcher->displayStats();
}

void SimulationController::displayEventCalendar() {
    std::cout << "\n--- Календарь событий (ближайшие 5) ---" << std::endl;

    if (eventCalendar.empty()) {
        std::cout << "  Календарь пуст" << std::endl;
        return;
    }

    auto tempQueue = eventCalendar;
    int count = 0;
    while (!tempQueue.empty() && count < 5) {
        Event event = tempQueue.top();
        tempQueue.pop();
        std::cout << "  " << std::fixed << std::setprecision(2) << event.time
            << ": " << event.getTypeString() << std::endl;
        count++;
    }
}

void SimulationController::displayStatistics() {
    std::cout << "\n    СТАТИСТИКА СИМУЛЯЦИИ " << std::endl;
    std::cout << "Общее время: " << currentTime << std::endl;
    std::cout << "Обработано заявок: " << totalProcessedRequests << std::endl;

    if (totalProcessedRequests > 0) {
        std::cout << "Среднее время обслуживания: "
            << (totalServiceTime / totalProcessedRequests) << std::endl;
        std::cout << "Среднее время ожидания: "
            << (totalWaitingTime / totalProcessedRequests) << std::endl;
    }

    inputDispatcher->displayStats();
}

void SimulationController::generateInitialEvents() {
    //Генерируем несколько начальных событий
    std::random_device rd;
    std::mt19937 gen(rd());
    std::exponential_distribution<double> dist(0.5);

    for (int i = 0; i < 5; i++) {
        double time = currentTime + dist(gen);
        eventCalendar.push(Event(time, EventType::REQUEST_GENERATED, [this]() {
            processRequestGeneration();
            }));
    }
}

void SimulationController::processRequestGeneration() {
    Request* newRequest = source->generateRequest(currentTime);

    std::cout << "СГЕНЕРИРОВАНА: " << newRequest->toString() << std::endl;

    //Обрабатываем заявку через входной диспетчер
    bool accepted = inputDispatcher->handleNewRequest(newRequest);

    if (accepted) {
        eventCalendar.push(Event(currentTime, EventType::REQUEST_ADDED_TO_BUFFER));
    }
    else {
        eventCalendar.push(Event(currentTime, EventType::REQUEST_REJECTED));
    }

    double nextTime = source->getNextArrivalTime(currentTime);
    eventCalendar.push(Event(nextTime, EventType::REQUEST_GENERATED, [this]() {
        processRequestGeneration();
        }));
}

void SimulationController::processServiceCompletion(Device* device) {
    Request* completedRequest = device->getCurrentRequest();

    if (completedRequest) {
        std::cout << "ЗАВЕРШЕНО: " << completedRequest->toString()
            << " на лифте " << device->getDeviceId() << std::endl;

        totalProcessedRequests++;
        totalServiceTime += (currentTime - device->getServiceStartTime());

        delete completedRequest;

        device->completeService();
        eventCalendar.push(Event(currentTime, EventType::SERVICE_COMPLETED));
    }
}