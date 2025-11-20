#include "InputDispatcher.h"
#include <iostream>

InputDispatcher::InputDispatcher(Buffer* buffer)
    : buffer(buffer), rejectedRequests(0), totalRequests(0) {
}

bool InputDispatcher::handleNewRequest(Request* request) {
    totalRequests++;

    if (!buffer->isFull()) {
        if (buffer->addRequest(request)) {
            std::cout << "Заявка " << request->toString() << " добавлена в буфер" << std::endl;
            return true;
        }
    }
    else {
        //Буфер полон - вытеснение
        int indexToReplace = buffer->findNewestRequest();
        if (indexToReplace != -1) {
            Request* rejected = buffer->getRequests()[indexToReplace];
            std::cout << "ВЫТЕСНЕНИЕ: Заявка " << rejected->toString()
                << " заменена на " << request->toString() << std::endl;

            buffer->removeRequest(indexToReplace);
            buffer->addRequest(request);
            rejectedRequests++;
            return true;
        }
    }
    std::cout << "ОТКАЗ: Заявка " << request->toString() << " отклонена" << std::endl;
    rejectedRequests++;
    delete request;
    return false;
}

int InputDispatcher::applyBufferingDiscipline(Request* request) {
    //Д1ОЗ3: поиск первого свободного места
    return buffer->findFirstFreeSlot();
}


double InputDispatcher::getRejectionRate() const {
    if (totalRequests == 0) return 0.0;
    return static_cast<double>(rejectedRequests) / totalRequests;
}

int InputDispatcher::getTotalRequests() const {
    return totalRequests;
}

int InputDispatcher::getRejectedRequests() const {
    return rejectedRequests;
}

void InputDispatcher::displayStats() const {
    std::cout << "Статистика входящих заявок:" << std::endl;
    std::cout << "  Всего заявок: " << totalRequests << std::endl;
    std::cout << "  Отклонено: " << rejectedRequests << std::endl;
    std::cout << "  Процент отказов: " << (getRejectionRate() * 100) << "%" << std::endl;
}