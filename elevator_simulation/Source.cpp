#include "Source.h"
#include <random>
#include <iostream>

int Source::nextId = 1;

Source::Source(int floors, double requestRate)
    : sourceId(nextId++), numFloors(floors), requestRate(requestRate) {
    generator.seed(std::random_device{}());
}

Request* Source::generateRequest(double currentTime) {
    std::uniform_int_distribution<int> floorDist(1, numFloors);
    int targetFloor = floorDist(generator);

    //Равномерное распределение для времени между заявками
    std::exponential_distribution<double> timeDist(requestRate);
    double arrivalTime = currentTime + timeDist(generator);

    return new Request(sourceId, targetFloor, arrivalTime);
}

int Source::getSourceId() const {
    return sourceId;
}

double Source::getNextArrivalTime(double currentTime) {
    std::exponential_distribution<double> timeDist(requestRate);
    return currentTime + timeDist(generator);
}