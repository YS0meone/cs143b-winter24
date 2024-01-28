//
// Created by yuant on 1/26/2024.
//

#include "../include/rcb.h"

RCB::RCB()
    : _inventory(0), _state(0), _waitList({}){
}

void RCB::addToWaitList(PID pid) {
    _waitList.push_back(pid);
}

RC RCB::removeFromWaitList(PID pid) {
    auto it = std::find(_waitList.begin(), _waitList.end(), pid);
    if (it != _waitList.end()) {
        _waitList.erase(it);
    }
    else {
        std::cerr << "Process not found in the wait list!" << std::endl;
        return -1;
    }
    return 0;
}


PID RCB::peekWaitList() {
    return _waitList.front();
}

bool RCB::isWaitListEmpty() {
    return _waitList.empty();
}

void RCB::setInventory(int units) {
    _inventory = units;
}

void RCB::initializeState() {
    _state = _inventory;
}

void RCB::printRCB() {
    std::cout << "Inventory: " << _inventory  << std::endl;
    std::cout << "Units left: " << _state << std::endl;
    std::cout << "Wait List PIDs: ";
    printList(_waitList);
    std::cout << std::endl;
}
