//
// Created by yuant on 1/26/2024.
//

#include "../include/rcb.h"

RCB::RCB()
    : _inventory(0), _state(0), _waitList({}){
}

void RCB::addRequest(PID pid, unsigned int units) {
    PRP newRequest(pid, units);
    _waitList.push_back(newRequest);
}

RC RCB::removeFromWaitList(PID pid) {
    for (auto it = _waitList.begin(); it != _waitList.end(); ++it) {
        if (it->first == pid) {
            _waitList.erase(it);
            return 0;
        }
    }
    std::cerr << "Process not found in the wait list!" << std::endl;
    return -1;
}


PID RCB::getNextWaitingProcess() {
    return _waitList.front().first;
}

bool RCB::isWaitListEmpty() {
    return _waitList.empty();
}

void RCB::setInventory(unsigned int units) {
    _inventory = units;
}

void RCB::initializeState() {
    _state = _inventory;
}

void RCB::printRCB() {
    std::cout << "Inventory: " << _inventory  << std::endl;
    std::cout << "Units left: " << _state << std::endl;
    std::cout << "Wait List PIDs: ";
    printPairList(_waitList);
    std::cout << std::endl;
}

bool RCB::canHandle(unsigned int units) {
    return _state >= units;
}

void RCB::allocateUnits(unsigned int units) {
    _state -= units;
}


unsigned RCB::getInventory() {
    return _inventory;
}
