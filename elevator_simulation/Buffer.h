#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include "Request.h"

class Buffer {
private:
    std::vector<Request*> slots;
    int pointer;

public:
    const int capacity;

    Buffer(int capacity);
    ~Buffer();

    bool addRequest(Request* request);
    bool removeRequest(int index);
    Request* getNextRequest();
    int findFirstFreeSlot();
    int findNewestRequest();
    bool isFull() const;
    bool isEmpty() const;
    int getSize() const;
    void displayState() const;
    int getPointer() const;
    std::vector<Request*> getRequests() const;
};

#endif