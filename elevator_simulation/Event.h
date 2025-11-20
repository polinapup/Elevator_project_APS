#ifndef EVENT_H
#define EVENT_H

#include <functional>
#include <string>

enum class EventType {
    REQUEST_GENERATED,
    REQUEST_ADDED_TO_BUFFER,
    REQUEST_REMOVED_FROM_BUFFER,
    SERVICE_STARTED,
    SERVICE_COMPLETED,
    REQUEST_REJECTED
};

class Event {
public:
    double time;
    EventType type;
    std::function<void()> action;

    Event(double t, EventType ty, std::function<void()> act = nullptr);

    bool operator>(const Event& other) const;
    std::string getTypeString() const;
};

#endif