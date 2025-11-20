#ifndef INPUTDISPATCHER_H
#define INPUTDISPATCHER_H

#include "Buffer.h"
#include "Request.h"

class InputDispatcher {
private:
    Buffer* buffer;
    int rejectedRequests;
    int totalRequests;

public:
    InputDispatcher(Buffer* buffer);

    bool handleNewRequest(Request* request);

    int applyBufferingDiscipline(Request* request); // д1нг3

    double getRejectionRate() const;
    int getTotalRequests() const;
    int getRejectedRequests() const;

    void displayStats() const;
};

#endif
