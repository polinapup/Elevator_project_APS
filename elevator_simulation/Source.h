#ifndef SOURCE_H
#define SOURCE_H
#include "Request.h"
#include <random>

class Source {
private:
    int sourceId;
    int numFloors;
    double requestRate;
    std::mt19937 generator;
    static int nextId;

public:
    Source(int floors = 10, double requestRate = 0.5);
    Request* generateRequest(double currentTime);
    int getSourceId() const;
    double getNextArrivalTime(double currentTime);
};

#endif
