#include "Buffer.h"
#include <iostream>
#include <algorithm>

Buffer::Buffer(int capacity)
    : capacity(capacity), pointer(0) {
    slots.resize(capacity, nullptr);
}

Buffer::~Buffer() {
    
}

bool Buffer::addRequest(Request* request) {
    int index = findFirstFreeSlot();
    if (index != -1) {
        slots[index] = request;
        return true;
    }
    return false;
}

bool Buffer::removeRequest(int index) {
    if (index >= 0 && index < capacity && slots[index] != nullptr) {
        delete slots[index];
        slots[index] = nullptr;
        return true;
    }
    return false;
}

Request* Buffer::getNextRequest() {
    for (int i = 0; i < capacity; i++) {
        int index = (pointer + i) % capacity;
        if (slots[index] != nullptr) {
            Request* request = slots[index];
            slots[index] = nullptr;
            pointer = (index + 1) % capacity;
            std::cout << "УДАЛЕНИЕ: " << request->toString() << " из буфера" << std::endl;
            return request;
        }
    }
    return nullptr;
}

int Buffer::findFirstFreeSlot() {
    for (int i = 0; i < capacity; i++) {
        if (slots[i] == nullptr) {
            return i;
        }
    }
    return -1;
}

int Buffer::findNewestRequest() {
    if (isEmpty()) return -1;

    int newestIndex = -1;
    double newestTime = -1;

    for (int i = 0; i < capacity; i++) {
        if (slots[i] != nullptr && slots[i]->getTimestamp() > newestTime) {
            newestTime = slots[i]->getTimestamp();
            newestIndex = i;
        }
    }
    return newestIndex;
}

bool Buffer::isFull() const {
    for (int i = 0; i < capacity; i++) {
        if (slots[i] == nullptr) {
            return false;
        }
    }
    return true;
}

bool Buffer::isEmpty() const {
    for (auto request : slots) {
        if (request != nullptr) return false;
    }
    return true;
}

int Buffer::getSize() const {
    int count = 0;
    for (auto request : slots) {
        if (request != nullptr) count++;
    }
    return count;
}



void Buffer::displayState() const {
    std::cout << "Буфер [";
    for (int i = 0; i < capacity; i++) {
        if (slots[i] != nullptr) {
            std::cout << slots[i]->getTargetFloor();
        }
        else {
            std::cout << "_";
        }
        if (i < capacity - 1) std::cout << " ";
    }
    std::cout << "] Указатель: " << pointer << std::endl;
}

std::vector<Request*> Buffer::getRequests() const {
    std::vector<Request*> requests;
    for (auto request : slots) {
        if (request != nullptr) {
            requests.push_back(request);
        }
    }
    return requests;
}

int Buffer::getPointer() const {
    return pointer;
}