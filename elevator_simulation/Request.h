#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request {
private:
    int requestId;
    int sourceId;
    int targetFloor;
    double timestamp;
    static int nextId;

public:
    Request(int sourceId, int targetFloor, double timestamp);

    int getRequestId() const;
    int getSourceId() const;
    int getTargetFloor() const;
    double getTimestamp() const;
    std::string toString() const;
};

#endif