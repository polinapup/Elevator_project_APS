#include "Request.h"
#include <sstream>

int Request::nextId = 1;

Request::Request(int sourceId, int targetFloor, double timestamp)
    : requestId(nextId++), sourceId(sourceId), targetFloor(targetFloor),
    timestamp(timestamp) {
}

int Request::getRequestId() const { return requestId; }
int Request::getSourceId() const { return sourceId; }
int Request::getTargetFloor() const { return targetFloor; }
double Request::getTimestamp() const { return timestamp; }

std::string Request::toString() const {
    std::stringstream ss;
    ss << "Req. " << requestId << " из Источника: " << sourceId << " на Этаж: " << targetFloor;
    return ss.str();
}