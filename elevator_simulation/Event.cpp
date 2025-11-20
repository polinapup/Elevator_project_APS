#include "Event.h"
#include <string>

Event::Event(double t, EventType ty, std::function<void()> act)
    : time(t), type(ty), action(act) {
}

bool Event::operator>(const Event& other) const {
    return time > other.time;
}

std::string Event::getTypeString() const {
    switch (type) {
    case EventType::REQUEST_GENERATED: return "Заявка сгенерирована";
    case EventType::REQUEST_ADDED_TO_BUFFER: return "Заявка добавлена в буфер";
    case EventType::REQUEST_REMOVED_FROM_BUFFER: return "Заявка удалена из буфера";
    case EventType::SERVICE_STARTED: return "Обслуживание начато";
    case EventType::SERVICE_COMPLETED: return "Обслуживание завершено";
    case EventType::REQUEST_REJECTED: return "Заявка отклонена";
    default: return "Неизвестное событие";
    }
}